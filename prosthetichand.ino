/*	Open Bionics - Artichoke
	Author - Olly McBride
	Date - December 2015
	This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License.
	To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/.
	Website - http://www.openbionics.com/
	GitHub - https://github.com/Open-Bionics
	Email - ollymcbride@openbionics.com
	OpenBionics_Artichoke.ino

  Rewrite by Nguyen Quang Duc
  Email - nguyenquangduc2000@gmail.com
*/
#include <Wire.h>
#include <EEPROM.h>

#include "Globals.h"
#include "GripControl.h"
#include "CircleBuff.h"
#include "EMGControl.h"
#include "PinManagement.h"
#include "SerialControl.h"
#include "TimerManagement.h"

void setup()
{
  Serial.begin(9600);		// start serial
  setDefaults();				// initialise serialCmd.buffs, finger positions and muscle control, read EEPROM presets
  IOconfig();					// config finger pins, initialise port expander
  //startUpMessages();			// print welcome message, current hand configuration/settings
}

void loop()
{
  if (advancedSettings.muscleCtrlFlag > 0)	// muscle/EMG control
    runEMG();
}
