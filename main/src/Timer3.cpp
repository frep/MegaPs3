/*
 * Timer3.cpp
 *
 *  Created on: 10.02.2012
 *      Author: frehnerp
 */

#include "Timer3.h"

TimerThree Timer3;              // preinstatiate

ISR(TIMER3_OVF_vect)          // interrupt service routine that wraps a user defined function supplied by attachInterrupt
{
	Timer3.restart();
	Timer3.isrCallback();
}

void TimerThree::setTimerValuesToInterval(long millisec)
{
	long cycles = 16000 * millisec;			// not a good name

	// choose appropiate prescaler
	if(cycles < RESOLUTION)					// no prescaler necessary
	{
		prescaler = 1;
		offset    = RESOLUTION - cycles;
	}
	else if((cycles / 8) < RESOLUTION)		// prescaler = 8
	{
		prescaler = 2;
		offset    = RESOLUTION - (cycles / 8);
	}
	else if((cycles / 64) < RESOLUTION)		// prescaler = 64
	{
		prescaler = 3;
		offset    = RESOLUTION - (cycles / 64);
	}
	else if((cycles / 256) < RESOLUTION)	// prescaler = 256
	{
		prescaler = 4;
		offset    = RESOLUTION - (cycles / 256);
	}
	else if((cycles / 1024) < RESOLUTION)	// prescaler = 1024
	{
		prescaler = 5;
		offset    = RESOLUTION - (cycles / 1024);
	}
	else
	{
		prescaler = 0;	// Timer can't be started
	}
}

void TimerThree::attachInterrupt(void (*isr)())
{
	isrCallback = isr;    // register the user's callback with the real ISR
}

void TimerThree::start()
{
	TIMSK3 = 0x01; 				// enabled global and timer overflow interrupt;
	TCCR3A = 0x00; 				// normal operation page 148 (mode0);
	restart();
	TCCR3B = prescaler;
}

void TimerThree::stop()
{
	TCCR3B = 0;
}

void TimerThree::restart()
{
	TCNT3 = offset;
}
