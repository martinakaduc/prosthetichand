/*	Open Bionics - Artichoke-
	Author - Olly McBride
	Date - December 2015

	This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License.
	To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/.

	Website - http://www.openbionics.com/
	GitHub - https://github.com/Open-Bionics
	Email - ollymcbride@openbionics.com

	Globals.h

*/

#ifndef _GLOBALS_h
#define _GLOBALS_h

#include <Arduino.h>	// data types (uint8_t...)
#include <Servo.h>

// Uncomment any of the following to enable various features
#define NUM_EMG_CHANNELS	1	// select the number of EMG channels to use (1 or 2)
#define EMG_PIN_0 A0
#if (NUM_EMG_CHANNELS > 1)
#define EMG_PIN_1 A1
#endif

// MACROS
#define IS_BETWEEN(x,a,b)     (((x>=a)&&(x<=b))?(1):(0))        // check if value x is between values a and b
//#define MYSERIAL Serial

// LIMITS
#define MAX_FINGERS     6     // maximum number of _fingers
#define MAX_FINGER_POS    170     // maximum motor position
#define MIN_FINGER_POS    10      // minimum motor position
#define POS_REACHED_TOLERANCE 5    // tolerance for posReached()
#define MAX_FINGER_SPEED  180
#define MIN_FINGER_SPEED  0

// DIRECTIONS
#define RIGHT		1	    // handIs
#define LEFT		2	    // handIs
#define OPEN		0	    // hand
#define CLOSE		1	    // hand
#define OFF			0	    // EEPROM flag
#define ON			1	    // EEPROM flag
#define PROP_MODE 2 //proportional mode control
#define BLANK		255

// FINGERS
#define NUM_FINGERS		5
#define FINGER0			0		// thumb
#define FINGER1			1		// index
#define FINGER2			2		// middle
#define FINGER3			3		// ring
#define FINGER4			4		// pinky

// GRIPS
#define NUM_GRIPS		6
#define FIST_GRIP		0
#define PALM_GRIP	    1
#define THUMBSUP_GRIP	2
#define POINT_GRIP		3
#define PINCH_GRIP		4
#define TRIPOD_GRIP		5

// EEPROM LOCATIONS
#define ADVANCED_CTRL_LOC	  20			// starting pos for advanced control flags
#define USER_SETTINGS_LOC	  30			// starting pos for stored user settings

// DEFAULTS
#define FULLY_OPEN		MIN_FINGER_POS		// fully open position for the hand, from FingerLib.h
#define FULLY_CLOSED	MAX_FINGER_POS		// fully closed position for the hand, from FingerLib.h

// FINGERLIB FINGER CLASS
extern Servo finger[NUM_FINGERS];			// instances of the Finger class, from FingerLib.h

// FINGER & HAND STATES
extern int currentGrip;						// current grip pattern for muscle sense change
extern int currentDir;						// current direction of the hand (Open/Closed)

// ADVANCED SETTINGS
struct advancedSettingsType					// these settings are stored in EEPROM and are used to enter different modes at startup
{
  // one time config flags
  uint8_t initConfigFlag = false;			// used to indicate whether EEPROM has been configured correctly
  uint8_t handFlag = LEFT;				// left or right hand
  // control flags
  uint8_t instructionsFlag = BLANK;		// display serial instructions on start up
  uint8_t muscleGraphFlag = BLANK;		// display muscle graph on startup
  uint8_t muscleCtrlFlag = BLANK;			// enable muscle control (standard or position) on startup
  uint8_t gripFlag = BLANK;				// enable/disable grip change
  uint8_t motorEnable = BLANK;			// enable/disable motors
};
extern struct advancedSettingsType advancedSettings;

// USER SETTINGS
struct userSettingsType						// these settings are also stored in EEPROM, and are custom to each user
{
  int sensitivityOffset = BLANK;			// the sensitivity of the EMG controller
  int holdTime = BLANK;					// time the muscle needs to be held tensed to perform a grip change
};
extern struct userSettingsType userSettings;



// STORES SERIAL STRINGS IN PROGMEM, SAVES 3KB RAM
/*#define  FORCE_INLINE __attribute__((always_inline)) inline

FORCE_INLINE void serialprintPGM(const char *str)
{
  char ch = pgm_read_byte(str);
  while (ch)
  {
    MYSERIAL.write(ch);
   ch = pgm_read_byte(++str);
  }
}*/

//#define MYSERIAL_PRINT(x) MYSERIAL.print(x);
//#define MYSERIAL_PRINT_F(x,y) MYSERIAL.print(x,y);
//#define MYSERIAL_PRINTLN(x) do {MYSERIAL.print(x);MYSERIAL.write('\n');} while(0)

//#define MYSERIAL_PRINT_PGM(x) serialprintPGM(PSTR(x));
//#define MYSERIAL_PRINTLN_PGM(x) do{serialprintPGM(PSTR(x));MYSERIAL.write('\n');} while(0)


// SOFTWARE VERSION NUMBER
//#define VERSION  1.0

#endif /*_GLOBALS_h*/
