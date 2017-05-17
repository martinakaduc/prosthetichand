/*	Open Bionics - Artichoke
	Author - Olly McBride
	Date - December 2015

	This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License.
	To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/.

	Website - http://www.openbionics.com/
	GitHub - https://github.com/Open-Bionics
	Email - ollymcbride@openbionics.com

	PinManagement.cpp

*/

#include <Arduino.h>			// for type definitions

#include "Globals.h"

#include "EMGControl.h"
#include "PinManagement.h"

void servoPinAssignment(void)
{
  if (advancedSettings.handFlag == RIGHT)
  {
    finger[0].attach(6);        // attach the direction pins and the analog sense pins for each motor
    finger[1].attach(11);      // attach the direction pins and the analog sense pins for each motor
    finger[2].attach(10);     // attach the direction pins and the analog sense pins for each motor
    finger[3].attach(9);        // attach the direction pins and the analog sense pins for each motor
    finger[4].attach(3);       // attach the direction pins and the analog sense pins for each motor
  }
  else if (advancedSettings.handFlag == LEFT)
  {
    finger[0].attach(5);      // attach the direction pins and the analog sense pins for each motor
    finger[1].attach(11);       // attach the direction pins and the analog sense pins for each motor
    finger[2].attach(10);        // attach the direction pins and the analog sense pins for each motor
    finger[3].attach(9);      // attach the direction pins and the analog sense pins for each motor
    finger[4].attach(3);      // attach the direction pins and the analog sense pins for each motor
  }
}

void IOconfig(void)   // assign pins for each finger, store pins within list and set as INPUT/OUTPUT
{
  // assign/attach finger and muscle pins
  EMG[0].pin = EMG_PIN_0;
#if (NUM_EMG_CHANNELS > 1)
  EMG[1].pin = EMG_PIN_1;
#endif

  // enable/disable motors
  if (!advancedSettings.motorEnable)
    for (int i = 0; i < NUM_FINGERS; i++)
    {
      finger[i].detach();
    }
  else servoPinAssignment();
  //Declare EMG sensor pins
  pinMode(EMG[0].pin, INPUT);
#if (NUM_EMG_CHANNELS > 1)
  pinMode(EMG[1].pin, INPUT);
#endif
  pinMode(LED_BUILTIN, OUTPUT);
}


