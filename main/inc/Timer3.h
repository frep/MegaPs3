/*
 * Timer3.h
 *
 *  Created on: 10.02.2012
 *      Author: frehnerp
 */

#ifndef TIMER3_H_
#define TIMER3_H_

#include <avr/interrupt.h>

#define RESOLUTION 65536    // Timer3 is 16 bit

class TimerThree
{
  public:

    void setTimerValuesToInterval(long millisec);
    void attachInterrupt(void (*isr)());
    void start();
    void stop();
    void restart();
    void (*isrCallback)();	// function pointer to the attached isr

  private:
    uint8_t prescaler;	// not a good name
    long    offset;


};

extern TimerThree Timer3;

#endif /* TIMER3_H_ */
