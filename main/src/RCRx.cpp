// RCRx.cpp
//
// Remote Control Receiver module for RCOIP protocol
/// \author  Mike McCauley (mikem@open.com.au)
///
// Copyright (C) 2010 Mike McCauley
// $Id: RCRx.cpp,v 1.3 2010/06/28 00:56:10 mikem Exp $

#include <Arduino.h>
#include "RCRx.h"
#include "Setter.h"				// needed?
#include "RCOIP.h"
#include <HardwareSerial.h>		// needed?
#include <RedFly.h>				// Needed to work with the RedFly-Shield
#include "NetworkConfig.h"

//#define DEBUG	// adds more debug-information at the serial port

// There is precisely one RCRx instance
static RCRx* rcrx;

//unsigned char ssid_len;
//unsigned char security_passphrase_len;
//uint16_t port = RCOIP_DEFAULT_RECEIVER_UDP_PORT;

/////////////////////////////////////////////////////////////////////
RCRx::RCRx()
{
    // init private members
	_analogOutputs = 0;
    _numAnalogOutputs = 0;
    _batteryVoltageAnalogPin = 0;
    _replyInterval = RCOIP_DEFAULT_REPLY_INTERVAL;
    _failInterval = RCOIP_DEFAULT_FAIL_INTERVAL;
    _lastRequestTime = 0;
    _lastReplyTime = 0;
    _connected = 0;

    // record this as the singleton
    rcrx = this;
}

/////////////////////////////////////////////////////////////////////
void RCRx::setOutputs(Setter** analogOutputs, uint8_t numAnalogOutputs)
{
    _analogOutputs = analogOutputs;
    _numAnalogOutputs = numAnalogOutputs;
}

/////////////////////////////////////////////////////////////////////
void RCRx::setAnalogOutput(uint8_t channel, int value)
{
    if (channel < _numAnalogOutputs && _analogOutputs[channel])
	_analogOutputs[channel]->input(value);
}

/////////////////////////////////////////////////////////////////////
void RCRx::init()
{
	uint8_t ret;

	//init the WiFi module on the shield:
	ret = RedFly.init();
	if(ret)
	{
		debugoutln("INIT ERR"); //there are problems with the communication between the Arduino and the RedFly
	}
	else
	{
		//scan for wireless networks (must be run before join command)
		RedFly.scan();

		//join network
#if defined (InfraJoin)
		ret = RedFly.join(ssid);
#elif defined (InfraPwJoin)
		ret = RedFly.join(ssid, pw, INFRASTRUCTURE);
#elif defined (AdhocJoin)
		ret = RedFly.join(ssid, IBSS_JOINER);
#elif defined (AdhocPwJoin)
		ret = RedFly.join(ssid, pw, IBSS_JOINER);
#elif defined (AdhocCreate)
		ret = RedFly.join(ssid, IBSS_CREATOR, channel);
#elif defined (AdhocPwCreate)
		ret = RedFly.join(ssid, pw, IBSS_CREATOR, channel);
#endif

		if(ret)
		{
			debugoutln("JOIN ERR");
			for(;;); //do nothing forevermore
		}
		else
		{
			//set ip config
			ret = RedFly.begin(ip, 0, 0, netmask);
			if(ret)
			{
				debugoutln("BEGIN ERR");
				RedFly.disconnect();
				for(;;); //do nothing forevermore
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////
void RCRx::run()
{
	uint8_t sock, buf[64], *ptr;
	uint16_t buf_len, rd, len;
	uint16_t port; //incomming UDP port
	uint8_t ip[4]; //incomming UDP ip

	//check if sockets are opened
	if(RedFly.socketClosed(hUDP) || (hUDP == 0xFF))
	{
		hUDP = RedFly.socketListen(PROTO_UDP, UDP_PORT); //open UDP socket
	}

	//get data
	sock    = 0xFF; //0xFF = return data from all open sockets
	ptr     = buf;
	buf_len = 0;
	do
	{
		rd = RedFly.socketRead(&sock, &len, ip, &port, ptr, sizeof(buf)-buf_len);
		if((rd != 0) && (rd != 0xFFFF)) //0xFFFF = connection closed
		{
			ptr     += rd;
			buf_len += rd;
		}
	}while(len != 0);  //len contains the data size from rx buffer

	// if datas received, then handle the request
	if(buf_len != 0)
	{
		if(destPORT != port)
		{
			destPORT = port;
			for(int i=0;i<4;i++)
			{
				destIP[i] = ip[i];
			}
		}
		handleRequest(buf, buf_len, ip, port, sock);
	}

	// check for lost connection
	periodicTask();

}

/////////////////////////////////////////////////////////////////////
// Sends a Reply message to the destination port at the destination IP
void RCRx::sendReply(uint8_t* destIP, uint16_t destPORT, uint8_t sock)
{
    RCOIPv1ReplyReceiverStatus reply;
    reply.version = RC_VERSION;
    reply.batteryVoltage = analogRead(_batteryVoltageAnalogPin) >> 2; // Arduino is 10 bits analog
    //udpSendReply((uint8_t*)&reply, sizeof(reply));
    if(sock == hUDP)
    {
    	RedFly.socketSend(hUDP, (uint8_t*)&reply, sizeof(reply), destIP, destPORT);
    }
    else
    {
    	debugoutln("SEND ERR");
    }
    _lastReplyTime = _lastRequestTime;
}

void RCRx::sendMessage(uint8_t* msg, uint8_t length)
{
	//check if sockets are opened
	if(RedFly.socketClosed(hUDP) || (hUDP == 0xFF))
	{
		hUDP = RedFly.socketListen(PROTO_UDP, UDP_PORT); //open UDP socket
	}
	if(destPORT != 0)
	{
		RedFly.socketSend(hUDP, msg, length, destIP, destPORT);
	}

}

/////////////////////////////////////////////////////////////////////
// This is called when a new UDP message is received in the RC port
// Caution: RSSI support requires mods to WiShield g2100.c as per 
// http://asynclabs.com/forums/viewtopic.php?f=10&t=385&start=0
void RCRx::handleRequest(uint8_t *msg, uint16_t len, uint8_t *ip, uint16_t port, uint8_t sock)
{
	RCOIPCmdSetAnalogChannels* setAnalogChannels = (RCOIPCmdSetAnalogChannels*)msg;
    if (len >= 1 && setAnalogChannels->version == RC_VERSION1)
    {
#ifdef DEBUG
    	debugoutln("msg recognized");
#endif
    	for (int i = 0; i < len-1; i++)
    	{
    		setAnalogOutput(i, setAnalogChannels->channels[i]);
#ifdef DEBUG
    		debugoutln("Channel is set");
#endif
    	}
	
    	// Only reply at most once per _replyInterval millis
    	// Transmitter will typically interpret gap in replies
    	// of 2 sec or more as bad connection
    	_lastRequestTime = millis();
    	if (_lastRequestTime > _lastReplyTime + _replyInterval)
    	{
    		sendReply(ip, port, sock);
    	}
    }
    else
    {
#ifdef DEBUG
    	debugoutln("msg not recognized");
#endif
    }
}

// function for debugging purpose: (serial format: 9600 Baud, 8N2)
void RCRx::debugout(char *s)
{
	RedFly.disable();
	Serial.print(s);
	RedFly.enable();
}

// function for debugging purpose: (serial format: 9600 Baud, 8N2)
void RCRx::debugoutln(char *s)
{
	RedFly.disable();
	Serial.println(s);
	RedFly.enable();
}

// disconnect the RedFly shield
void disconnect()
{
	RedFly.disconnect();
}

/////////////////////////////////////////////////////////////////////
boolean RCRx::connected()
{
    return _connected;
}

/////////////////////////////////////////////////////////////////////
// Call the failsafe functions of all outputs
void RCRx::failsafe()
{
    int i;
    for (i = 0; i < _numAnalogOutputs; i++)
    {
    	if (_analogOutputs[i])
    	{
    		_analogOutputs[i]->failsafe();
    	}
    }
}

/////////////////////////////////////////////////////////////////////
// This is called twice per second or so by the UDP code
// do some maintenance like looking for lost connections etc
void RCRx::periodicTask()
{
    boolean wasConnected = _connected;
    _connected = millis() < (_lastRequestTime + _failInterval);
    // If we just lost the connection, fail safe
    if (wasConnected && !_connected)
	failsafe();
}
