/*
 * UdpTerminal.cpp
 *
 *  Created on: 22.02.2012
 *      Author: frehnerp
 */

#include "Arduino.h"
#include "UdpTerminal.h"
#include "RCRx.h"

extern RCRx rcrx;

char digit2char(int digit)
{
	return (char)(digit + 48);
}

UdpData getValueData(uint16_t value)
{
	// convert value to string
	UdpData data;
	uint8_t val[5];	// max value of uint16_t is around 65K -> a maximum of 5 digits are used
	int index = 0;
	for(int i=4;i>=0;i--)
	{
		if((int(value / pow(10,i))%10) != 0)
		{
			val[index] = (uint8_t)digit2char((int(value / pow(10,i))%10));
			index++;
		}
	}
	if(index == 0)	// if every digit is zero, then the value was zero
	{
		val[0] = (uint8_t)digit2char(0);
		index = 1;
	}
	data.length = index;
	for(uint8_t i = 0;i<data.length;i++)
	{
		data.msg[i] = val[i];
	}
	return data;
}

UdpData getMsgData(char msg[64])
{
	UdpData data;
	data.length = 0;
	while(msg[data.length] != '\0' && data.length < 63)
	{
		data.msg[data.length] = (uint8_t)msg[data.length];
		data.length++;
	}
	return data;
}

void sendUDPData(UdpData data)
{
	rcrx.sendMessage(data.msg, data.length);
}

void sendUDPValue(uint16_t value)
{
	UdpData data = getValueData(value);
	sendUDPData(data);

}

void sendUDPMessage(char msg[64])
{
	UdpData data;
	data.length = 0;
	while(msg[data.length] != '\0' && data.length < 63)
	{
		data.msg[data.length] = (uint8_t)msg[data.length];
		data.length++;
	}
	sendUDPData(data);
}

void sendUDPMessageWithValue(char msg[64], uint16_t value)
{

	UdpData msgData = getMsgData(msg);
	UdpData valData = getValueData(value);
	UdpData result;
	result.length = (msgData.length + valData.length);
	for(int i=0;i<msgData.length;i++)
	{
		result.msg[i] = msgData.msg[i];
	}
	for(int j=msgData.length;j<result.length;j++)
	{
		result.msg[j] = valData.msg[j-msgData.length];
	}
	sendUDPData(result);
}
