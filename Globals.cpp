/*	Open Bionics - Artichoke
	Author - Olly McBride
	Date - December 2015

	This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License.
	To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/.

	Website - http://www.openbionics.com/
	GitHub - https://github.com/Open-Bionics
	Email - ollymcbride@openbionics.com

	Globals.cpp

*/

#include "Globals.h"

// initialise Finger class to array
Servo finger[NUM_FINGERS];

// ADVANCED SETTINGS
struct advancedSettingsType advancedSettings;

// USER SETTINGS
struct userSettingsType userSettings;

// FINGER & HAND INIT STATES
int currentGrip = FIST_GRIP;				// current grip pattern for muscle sense change
int currentDir = OPEN;

