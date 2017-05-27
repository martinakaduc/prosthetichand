/*	Open Bionics - Artichoke
	Author - Olly McBride
	Date - December 2015

	This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License.
	To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/.

	Website - http://www.openbionics.com/
	GitHub - https://github.com/Open-Bionics
	Email - ollymcbride@openbionics.com

	SerialControl.cpp

*/


#include <Arduino.h>			// for type definitions
#include "Globals.h"
#include "EMGControl.h"
#include "GripControl.h"
#include "PinManagement.h"
#include "SerialControl.h"
#include "TimerManagement.h"
#include "Utils.h"

struct serialCmdType serialCmd;

void setDefaults(void)
{
  // read EEPROM settings
  EEPROM_readStruct(USER_SETTINGS_LOC, userSettings);
  EEPROM_readStruct(ADVANCED_CTRL_LOC, advancedSettings);
  if (advancedSettings.initConfigFlag != true)
    initialEEPROMconfig();		// if running for the first time, write default values to EEPROM

  currentGrip = FIST_GRIP;

  clearAll();       // set all serial/command serialCmd.buff variables to -1

}

void clearAll(void)    //clear all input variables for the next string
{
  int i;
  for (i = 0; i < SERIAL_BUF_SIZE; i++)
  {
    serialCmd.cmdBuff[i] = 0;
  }

  serialCmd.fingerNum = BLANK;
  serialCmd.stopPos = BLANK;
  serialCmd.gripNum = BLANK;
  serialCmd.advancedFlag = BLANK;
  serialCmd.muscleCtrlFlag = BLANK;
  serialCmd.instructionsFlag = BLANK;
  serialCmd.handFlag = BLANK;
  serialCmd.sensitivityAdjust = BLANK;
  serialCmd.resetFlag = BLANK;
  serialCmd.holdTime = BLANK;
}

void initialEEPROMconfig(void)			// write default values to EEPROM
{
  //MYSERIAL_PRINT_PGM("Initialising EEPROM values...");

  advancedSettings.handFlag = LEFT;
  advancedSettings.instructionsFlag = OFF;
  advancedSettings.muscleCtrlFlag = PROP_MODE;
  advancedSettings.muscleGraphFlag = OFF;
  advancedSettings.gripFlag = ON;
  advancedSettings.motorEnable = ON;
  advancedSettings.initConfigFlag = true;  // set flag to signal config complete

  userSettings.sensitivityOffset = 500;
  userSettings.holdTime = 400;

  EEPROM_writeStruct(ADVANCED_CTRL_LOC, advancedSettings);
  EEPROM_writeStruct(USER_SETTINGS_LOC, userSettings);

  //MYSERIAL_PRINTLN_PGM("Complete write to EEPROM");
}


void startUpMessages(void)
{
  //MYSERIAL_PRINT_PGM("VnProsthetichand - By Duc And Khoa");
  //MYSERIAL_PRINTLN((float)VERSION);

  //MYSERIAL_PRINTLN_PGM("Intel Edison");
  //MYSERIAL_PRINTLN_PGM("Prosthetic Hand");

  if (advancedSettings.muscleCtrlFlag > 0)
  {
    // if muscle mode is on, print on
    switch (advancedSettings.muscleCtrlFlag)
    {
      case 1:             // standard muscle control
        //MYSERIAL_PRINTLN_PGM("Standard Muscle Control ON");
        digitalWrite(LED_BUILTIN, HIGH); // turn on muscle control LED in knuckle
        break;
      case 2:             // position muscle control
        //MYSERIAL_PRINTLN_PGM("Muscle Position Control ON");
        digitalWrite(LED_BUILTIN, HIGH);   // turn on muscle control LED in knuckle
        break;
      default:
        digitalWrite(LED_BUILTIN, LOW);
        break;
    }
  }

  if (advancedSettings.instructionsFlag)
    printInstructions();			// if instructions not turned off, print initial instructions

}

void printInstructions(void)
{
  //MYSERIAL_PRINT_PGM("\n");
  //MYSERIAL_PRINTLN_PGM("         Open Bionics Serial Commands - Artichoke ");
  //MYSERIAL_PRINTLN_PGM("___________________________________________________________");
  //MYSERIAL_PRINT_PGM("\n");
  //MYSERIAL_PRINTLN_PGM("Grip Control (G#)");
  //MYSERIAL_PRINTLN_PGM("Command     Description");
  //MYSERIAL_PRINTLN_PGM("G0          Fist");
  //MYSERIAL_PRINTLN_PGM("G1          Palm");
  //MYSERIAL_PRINTLN_PGM("G2          Thumbs Up");
  //MYSERIAL_PRINTLN_PGM("G3          Point");
  //MYSERIAL_PRINTLN_PGM("G4          Pinch");
  //MYSERIAL_PRINTLN_PGM("G5          Tripod");
  //MYSERIAL_PRINT_PGM("\n");
  //MYSERIAL_PRINTLN_PGM("Finger Control (F#, P##, S##)");
  //MYSERIAL_PRINTLN_PGM("Command     Description");
  //MYSERIAL_PRINTLN_PGM("F#          Finger, where # is the finger number (F0 - F4)");
  //MYSERIAL_PRINTLN_PGM("F# P50      Finger # to position 50 (P0 - P100)");
  //MYSERIAL_PRINTLN_PGM("F# S255     Finger # at speed 255 (S0 - S255)");
  //MYSERIAL_PRINT_PGM("\n");
  //MYSERIAL_PRINTLN_PGM("Direction (O, C)");
  //MYSERIAL_PRINTLN_PGM("Command     Description");
  //MYSERIAL_PRINTLN_PGM("## O        Open, where ## is a Grip or Finger command");
  //MYSERIAL_PRINTLN_PGM("## C        Close, where ## is a Grip or Finger command");
  //MYSERIAL_PRINT_PGM("\n");
  //MYSERIAL_PRINTLN_PGM("Muscle Control (M#, U#, T#, N)");
  //MYSERIAL_PRINTLN_PGM("Command     Description");
  //MYSERIAL_PRINTLN_PGM("M0          Muscle control OFF");
  //MYSERIAL_PRINTLN_PGM("M1          Standard muscle control ON");
  //MYSERIAL_PRINTLN_PGM("M2          Muscle position control ON");
  //MYSERIAL_PRINTLN_PGM("M3          Toggle whether to display muscle readings");
  //MYSERIAL_PRINTLN_PGM("U###        Change muscle sensor sensitivity");
  //MYSERIAL_PRINTLN_PGM("T###        Change 'muscle hold' grip change duration");
  //MYSERIAL_PRINTLN_PGM("N           Calculate noise floor");
  //MYSERIAL_PRINT_PGM("\n");
  //MYSERIAL_PRINTLN_PGM("Advanced Settings (H#, A#, ?)");
  //MYSERIAL_PRINTLN_PGM("Command     Description");
  //MYSERIAL_PRINTLN_PGM("H           View hand configuration (LEFT or RIGHT)");
  //MYSERIAL_PRINTLN_PGM("H1          Set hand to be RIGHT");
  //MYSERIAL_PRINTLN_PGM("H2          Set hand to be LEFT");
  //MYSERIAL_PRINTLN_PGM("A0          Toggle 'Demo Mode' ON/OFF");
  //MYSERIAL_PRINTLN_PGM("A1          Toggle 'Serial Commands Instructions' ON/OFF");
  //MYSERIAL_PRINTLN_PGM("A2          Toggle 'Muscle Graph mode' ON/OFF");
  //MYSERIAL_PRINTLN_PGM("A3          Enable/Disable motors");
  //MYSERIAL_PRINTLN_PGM("A5          Emergency stop motors");
  //MYSERIAL_PRINTLN_PGM("A10         Research Mode 0, fast position control");
  //MYSERIAL_PRINTLN_PGM("A11         Research Mode 1, HANDle control (Nunchuck)");
  //MYSERIAL_PRINTLN_PGM("A12         Research Mode 1, HANDle  data dump");
  //MYSERIAL_PRINTLN_PGM("?           Display serial commands list");
  //MYSERIAL_PRINT_PGM("\n\n\n");
  //MYSERIAL_PRINTLN_PGM("Examples");
  //MYSERIAL_PRINTLN_PGM("G0 O        Fist Grip Open");
  //MYSERIAL_PRINTLN_PGM("G2 C        Thumbs Up Close");
  //MYSERIAL_PRINTLN_PGM("F0 O        Thumb Open");
  //MYSERIAL_PRINTLN_PGM("F0          Toggle thumb direction (open/close)");
  //MYSERIAL_PRINTLN_PGM("F4 P50      Pinky to position 50");
  //MYSERIAL_PRINTLN_PGM("F1 P50 S80  Index finger to position 50 at speed 80");
  //MYSERIAL_PRINTLN_PGM("F0 O S200   Thumb Open at speed 200");
  //MYSERIAL_PRINT_PGM("\n\n");




  // MODE ESCAPE TEXT
  //if (!advancedSettings.motorEnable)			// enable motors
    //MYSERIAL_PRINTLN_PGM("Motors disabled, enter 'A3' to re-enable them");
  //if (advancedSettings.muscleGraphFlag)		// print muscle data over serial
    //MYSERIAL_PRINTLN_PGM("Muscle graph mode, enter 'A2' to disable this mode");
  //if (advancedSettings.muscleCtrlFlag > 0)	// muscle/EMG control
    //MYSERIAL_PRINTLN_PGM("EMG/muscle control mode, enter 'M0' to disable this mode");
  // if researchFlag == 1, and no other command is recognised, use CSV string as target motor positions

  //MYSERIAL_PRINT_PGM("\n\n");
}
