#include "Arduino.h"
#include <PS3BT.h>
#include <Wire.h>
#include "PS3BTExample.h"
#include "Timer3.h"		// Timer3 can only be used with ArduinoMega
#include <RedFly.h>
#include <RCRx.h>
#include "UdpTerminal.h"

#define ledPin 13

USB Usb;
PS3BT BT(&Usb);

boolean printTemperature;
boolean sendIntervalIsReached;

RCRx rcrx;

// attached timer isr
void timer3ISR()
{
	digitalWrite(ledPin, digitalRead(ledPin) ^ 1);
	sendIntervalIsReached = true;
}

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  pinMode(ledPin, OUTPUT);

  sendIntervalIsReached = false;
  Timer3.setTimerValuesToInterval(500);		// Interval in [ms]
  Timer3.attachInterrupt(timer3ISR);
  //Timer3.start();

  rcrx.init();

  if (Usb.Init() == -1) 
  {
    Notify(PSTR("\r\nOSC did not start"));
    while(1); //halt
  }
  Notify(PSTR("\r\nPS3 Bluetooth Library Started"));

}
void loop()
{
  Usb.Task();
  ps3example();
  rcrx.run();
}

void ps3example()
{
	  if(BT.PS3BTConnected || BT.PS3NavigationBTConnected)
	  {

		deviceWasConnected = true;

		leftHatXValue = 120;
		leftHatYValue = 120;

		if(BT.getAnalogHat(LeftHatX) > 137 || BT.getAnalogHat(LeftHatX) < 117)
	    {
	      //Notify(PSTR("\r\nLeftHatX: "));
	      //Serial.print(BT.getAnalogHat(LeftHatX), DEC);
	      leftHatXValue = BT.getAnalogHat(LeftHatX);
	    }
	    if(BT.getAnalogHat(LeftHatY) > 137 || BT.getAnalogHat(LeftHatY) < 117)
	    {
	      //Notify(PSTR("\r\nLeftHatY: "));
	      //Serial.print(BT.getAnalogHat(LeftHatY), DEC);
	      leftHatYValue = BT.getAnalogHat(LeftHatY);
	    }
	    if(BT.getAnalogHat(RightHatX) > 137 || BT.getAnalogHat(RightHatX) < 117)
	    {
	      Notify(PSTR("\r\nRightHatX: "));
	      //Serial.print(BT.getAnalogHat(RightHatX), DEC);
	    }
	    if(BT.getAnalogHat(RightHatY) > 137 || BT.getAnalogHat(RightHatY) < 117)
	    {
	      Notify(PSTR("\r\nRightHatY: "));
	      //Serial.print(BT.getAnalogHat(RightHatY), DEC);
	    }

	    //Analog button values can be read from almost all buttons
	    if(BT.getAnalogButton(L2_ANALOG) > 0)
	    {
	      Notify(PSTR("\r\nL2: "));
	      //Serial.print(BT.getAnalogButton(L2_ANALOG), DEC);
	    }
	    if(BT.getAnalogButton(R2_ANALOG) > 0)
	    {
	      Notify(PSTR("\r\nR2: "));
	      //Serial.print(BT.getAnalogButton(R2_ANALOG), DEC);
	    }

	    if(BT.ButtonPressed)
	    {
	      Notify(PSTR("\r\nPS3 Controller"));

	      if(BT.getButton(PS))
	      {
	        Notify(PSTR(" - PS"));
	        BT.disconnect();
	      }
	      else
	      {
	        if(BT.getButton(TRIANGLE))
	        {
	          Notify(PSTR(" - Triangle"));
	          sendUDPMessage("Triangle");
	        }
	        if(BT.getButton(CIRCLE))
	        {
	          Notify(PSTR(" - Circle"));
	          sendUDPMessage("Circle");
	        }
	        if(BT.getButton(CROSS))
	        {
	          Notify(PSTR(" - Cross"));
	          sendUDPMessage("Cross");
	        }
	        if(BT.getButton(SQUARE))
	        {
	          Notify(PSTR(" - Square"));
	          sendUDPMessage("Square");
	        }

	        if(BT.getButton(UP))
	        {
	          Notify(PSTR(" - Up"));
	          sendUDPMessage("Up");
	          BT.setAllOff();
	          BT.setLedOn(LED4);
	        }
	        if(BT.getButton(RIGHT))
	        {
	          Notify(PSTR(" - Right"));
	          sendUDPMessage("Right");
	          BT.setAllOff();
	          BT.setLedOn(LED1);
	        }
	        if(BT.getButton(DOWN))
	        {
	          Notify(PSTR(" - Down"));
	          sendUDPMessage("Down");
	          BT.setAllOff();
	          BT.setLedOn(LED2);
	        }
	        if(BT.getButton(LEFT))
	        {
	          Notify(PSTR(" - Left"));
	          sendUDPMessage("Left");
	          BT.setAllOff();
	          BT.setLedOn(LED3);
	        }

	        if(BT.getButton(L1))
	        {
	        	Notify(PSTR(" - L1"));
	        	sendUDPMessage("L1");
	        }
	        //if(BT.getButton(L2))
	          //Notify(PSTR(" - L2"));
	        if(BT.getButton(L3))
	        {
	        	Notify(PSTR(" - L3"));
	        	sendUDPMessage("L3");
	        }
	        if(BT.getButton(R1))
	        {
	        	Notify(PSTR(" - R1"));
	        	sendUDPMessage("R1");
	        }
	        //if(BT.getButton(R2))
	          //Notify(PSTR(" - R2"));
	        if(BT.getButton(R3))
	        {
	        	Notify(PSTR(" - R3"));
	        	sendUDPMessage("R3");
	        }
	        if(BT.getButton(SELECT))
	        {
	          Notify(PSTR(" - Select - "));
	          sendUDPMessage("Select");
	          //Serial.print(BT.getStatusString());
	        }
	        if(BT.getButton(START))
	        {
	        	Notify(PSTR(" - Start"));
	        	if(RCControlStarted)
	        	{
	        		// stop RCControl
	        		sendUDPMessage("Start: Stop RC-Control");
	        		RCControlStarted = false;
	        		Timer3.stop();
	        	}
	        	else
	        	{
	        		// start RCControl
	        		sendUDPMessage("Start: Start RC-Control");
	        		RCControlStarted = true;
	        		Timer3.start();
	        	}
	        }

	      }
	    }

		if(sendIntervalIsReached)
		{
			processData(leftHatYValue, leftHatXValue);
		}

	  }
	  else if(BT.PS3MoveBTConnected)
	  {
	    if(BT.getAnalogButton(T_MOVE_ANALOG) > 0)
	    {
	      Notify(PSTR("\r\nT: "));
	      Serial.print(BT.getAnalogButton(T_MOVE_ANALOG), DEC);
	    }
	    if(BT.ButtonPressed)
	    {
	      Notify(PSTR("\r\nPS3 Move Controller"));

	      if(BT.getButton(PS_MOVE))
	      {
	        Notify(PSTR(" - PS"));
	        BT.disconnect();
	      }
	      else
	      {
	        if(BT.getButton(SELECT_MOVE))
	        {
	          Notify(PSTR(" - Select"));
	          printTemperature = false;
	        }
	        if(BT.getButton(START_MOVE))
	        {
	          Notify(PSTR(" - Start"));
	          printTemperature = true;
	        }
	        if(BT.getButton(TRIANGLE_MOVE))
	        {
	          Notify(PSTR(" - Triangle"));
	          BT.moveSetBulb(Red);
	        }
	        if(BT.getButton(CIRCLE_MOVE))
	        {
	          Notify(PSTR(" - Circle"));
	          BT.moveSetBulb(Green);
	        }
	        if(BT.getButton(SQUARE_MOVE))
	        {
	          Notify(PSTR(" - Square"));
	          BT.moveSetBulb(Blue);
	        }
	        if(BT.getButton(CROSS_MOVE))
	        {
	          Notify(PSTR(" - Cross"));
	          BT.moveSetBulb(Yellow);
	        }
	        if(BT.getButton(MOVE_MOVE))
	        {
	          BT.moveSetBulb(Off);
	          Notify(PSTR(" - Move"));
	          Notify(PSTR(" - "));
	          Serial.print(BT.getStatusString());
	        }
	        //if(BT.getButton(T_MOVE))
	          //Notify(PSTR(" - T"));
	      }
	    }
	    if(printTemperature)
	    {
	      String templow;
	      String temphigh;
	      String input = String(BT.getSensor(tempMove), DEC);

	      if (input.length() > 3)
	      {
	        temphigh = input.substring(0, 2);
	        templow = input.substring(2);
	      }
	      else
	      {
	        temphigh = input.substring(0, 1);
	        templow = input.substring(1);
	      }
	      Notify(PSTR("\r\nTemperature: "));
	      Serial.print(temphigh);
	      Notify(PSTR("."));
	      Serial.print(templow);
	    }
	  }
	  else
	  {
		  // No device connected
		  if(sendIntervalIsReached && deviceWasConnected)
		  {
			deviceWasConnected = false;
			processData(120, 120);		// send a stop
		  }
	  }
}

void sendI2cInt(int address, uint8_t cmd, uint8_t value)
{
	if(Wire.available())
	{
		//Serial.println("Still wire data available");
		sendUDPMessage("Still wire data available");
	}

	Wire.beginTransmission(address);
	Wire.write(cmd);
	Wire.write(value);
	Wire.endTransmission();

	sendIntervalIsReached = false;
}

void processData(uint8_t speed, uint8_t direction)
{

	uint8_t speedValue;
	uint8_t directionValue;
	bool forwards = false;
	bool left = false;

	// transform speed value
	if(speed < 117)
	{
		// forward
		forwards = true;
		speedValue = (116 - speed) * 2;
	}
	else if(speed > 137)
	{
		// backward
		speedValue = (speed - 137) * 2;
	}
	else
	{
		// stop
		speedValue = 0;
	}

	// transform direction value
	if(direction < 117)
	{
		// turn left
		left = true;
		directionValue = (116 - direction) * 2;
	}
	else if(direction > 137)
	{
		// turn right
		directionValue = (direction - 137) * 2;
	}
	else
	{
		// stop
		directionValue = 0;
	}



	if((speedValue == 0)&&(directionValue == 0))
	{
		// send stop command
		sendI2cInt(RoMeo, CMD_STOP, 0);
		sendUDPMessageWithValue("STOP mit ", 0);
	}
	else if(speedValue > directionValue)
	{
		if(forwards)
		{
			// drive forward
			sendI2cInt(RoMeo, CMD_FORWARD, speedValue);
			sendUDPMessageWithValue("VOR mit ", speedValue);
		}
		else
		{
			// drive backward
			sendI2cInt(RoMeo, CMD_BACKWARD, speedValue);
			sendUDPMessageWithValue("RUECK mit ", speedValue);
		}
	}
	else
	{
		if(left)
		{
			// turn left
			sendI2cInt(RoMeo, CMD_LEFT, directionValue);
			sendUDPMessageWithValue("LINKS mit ", directionValue);
		}
		else
		{
			// turn right
			sendI2cInt(RoMeo, CMD_RIGHT, directionValue);
			sendUDPMessageWithValue("RECHTS mit ", directionValue);
		}
	}
}


