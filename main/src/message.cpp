/* Copyright (C) 2011 Circuits At Home, LTD. All rights reserved.

This software may be distributed and modified under the terms of the GNU
General Public License version 2 (GPL2) as published by the Free Software
Foundation and appearing in the file GPL2.TXT included in the packaging of
this file. Please note that GPL2 Section 2[b] requires that all works based
on this software must also be made publicly available under the terms of
the GPL2 ("Copyleft").

Contact information
-------------------

Circuits At Home, LTD
Web      :  http://www.circuitsathome.com
e-mail   :  support@circuitsathome.com
*/
#include "message.h"
#include <RedFly.h>	//frepfrep

void Notify(char const * msg)
//void Notify(const char* msg)
{
	if(!msg) return;
	char c;

	RedFly.disable();

	while((c = pgm_read_byte(msg++)))
#if defined(ARDUINO) && ARDUINO >=100
  Serial.print(c);
#else  	
		Serial.print(c,BYTE);
#endif		

	RedFly.enable();

}
