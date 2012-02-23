/*
 * UdpTerminal.h
 *
 *  Created on: 22.02.2012
 *      Author: frehnerp
 */

#ifndef UDPTERMINAL_H_
#define UDPTERMINAL_H_

typedef struct
{
	uint8_t msg[64];
	uint16_t length;
} UdpData;

char digit2char(int digit);

UdpData getValueData(uint16_t value);
UdpData getMsgData(char msg[64]);

void sendUDPData(UdpData data);
void sendUDPValue(uint16_t value);
void sendUDPMessage(char msg[64]);
void sendUDPMessageWithValue(char msg[64], uint16_t value);

#endif /* UDPTERMINAL_H_ */
