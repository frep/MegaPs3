// RCRx.h
//
// Remote Control Receiver module for RCOIP protocol
///
/// \mainpage RCKit library for Arduino
///
/// This is the Arduino RCKit 1.1 library.
/// 
/// RCKit provides a kit of software objects that make it easy to build an
/// RCOIP  (Remote Control Over IP) receiver on Arduino. RCOIP protocol is used to
/// carry remote control commands from a transmitter to a receiver over an IP
/// transport such as Ethernet or Wi-Fi.
///
// Copyright (C) 2010 Mike McCauley
// $Id: RCRx.h,v 1.4 2010/06/30 02:48:59 mikem Exp mikem $

#ifndef RCRx_h
#define RCRx_h

//#include <WiShield.h>
#include <inttypes.h>

class Setter;

class RCRx
{
public:
    /// Constructor. After contruction and initialisation, call the init() and run() functions.
    RCRx();

    /// Specifies the Setters that will be used by this receiver to set its output values
    /// Whenever a RCOIP message is received with a new value for channel n, it will be passed
    /// to the Setter at index n by calling the Setters input() function.
    /// \param[in] analogOutputs Pointer to an array pointers to Setter objects.
    /// \param[in] numAnalogOutputs Number of elements in analogOutputs
    void setOutputs(Setter** analogOutputs, uint8_t numAnalogOutputs);

    /// Set the output for channel n. Calls the Setter at index n of the analogOutputs
    /// array. Not usuallly called exernally, this is usually only called
    /// from within RCRx. Subclasses can override this to get control
    /// when new analog output values become available
    /// \param[in] channel The analog channel number output to set
    /// \param[in] value The new value to set
    virtual void setAnalogOutput(uint8_t channel, int value);

    /// Initialises the wireless WiFi receiver
    /// Call once at startup time after addresses etc have been configured.
    void init();

    /// Call this to process pending Wireless events. Call this as often as possible in your
    /// main loop. Runs the wireless driver stack.
    void run();

    /// Call to handle an incoming UDP message containing an RCOIP command message.
    /// This is usually only called from within RCRx, but could be called externally 
    /// for testing purposes etc.
    /// \param[in] msg Pointer to the UDP message
    /// \param[in] len Length of the UDP mesage in bytes
    /// \param[in] rssi Receiver Signal Strength as reported by the WiFi receiver 
    /// when the message was received.
    void handleRequest(uint8_t *msg, uint16_t len, uint8_t *ip, uint16_t port, uint8_t sock);

    /// Called by RCRx when no RCOIP message has been received for more than failInterval miliseconds.
    /// Calls the failsafe function for all configured output Setters.
    void failsafe();

    /// Called by RCRx periodically (typically twice per second) to do period processing such as 
    /// detecting loss of messages
    void periodicTask();

    /// Returns whether the RCRx considers itself to be connected to the transmitter.
    /// Initialsed to false. Whenever an RCOIP request is receved, set to true. If no  RCOIP request 
    /// is receved for more than  failInterval miliseconds, set to false.
    /// \return true if the RCRx is still receiving messages from the transmitter.
    boolean connected();

    /// Sends an RCOIP reply message
    /// Usually called internally at most once every _replyInterval milliseconds.
    void sendReply(uint8_t* destIP, uint16_t destPORT, uint8_t sock);

    void sendMessage(uint8_t* msg, uint8_t length);

    void debugout(char *s);

    void debugoutln(char *s);

    void disconnect();

protected:

private:
    /// Array of output Setters
    Setter**      _analogOutputs;

    /// Number of Setters in _analogOutputs
    uint8_t       _numAnalogOutputs;

    /// Arduino analog input pin which yields the arduino battery voltage
    uint8_t       _batteryVoltageAnalogPin;

    /// Max time in milliseconds between RCOIP replies
    unsigned int  _replyInterval; 

    /// Max time in milliseconds between received request before RCRx is considered to be disconnected
    unsigned int  _failInterval; 

    /// The time we last got a RCOIP request from the transmitter
    unsigned long _lastRequestTime;

    /// The last time we sent a RCOIP reply to the transmitter
    unsigned long _lastReplyTime;

    /// Whether RCRx is considered to be connected to the transmitter
    boolean       _connected;

    /// The value of the RSSI (receiver signal strength indicator)
    /// in the last request received
    //uint16_t      _rssi;
};

#endif 
