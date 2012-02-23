/*
 * PS3BTExample.h
 *
 *  Created on: 02.02.2012
 *      Author: frehnerp
 */

#ifndef PS3BTEXAMPLE_H_
#define PS3BTEXAMPLE_H_

#define CMD_STOP     0
#define CMD_FORWARD  1
#define CMD_BACKWARD 2
#define CMD_LEFT     3
#define CMD_RIGHT    4

#define RoMeo        2

uint8_t leftHatXValue;
uint8_t leftHatYValue;

boolean deviceWasConnected = false;
boolean RCControlStarted = false;

// ISR for timer 3
void timer3ISR();


void ps3example();

void processData(uint8_t speed, uint8_t direction);

void sendI2cInt(int address, uint8_t cmd, uint8_t value);

#endif /* PS3BTEXAMPLE_H_ */
