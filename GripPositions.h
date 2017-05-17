/*	Open Bionics - Artichoke
	Author - Olly McBride
	Date - December 2015

	This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License.
	To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/.

	Website - http://www.openbionics.com/
	GitHub - https://github.com/Open-Bionics
	Email - ollymcbride@openbionics.com

	GripPositions.h

*/

#define GRIP_COUNT_LOC    0
#define NUM_GRIP_STEPS    4
/* The following array is used to pause a finger at a particular position within a grip movement
   and is a replacement for a lookup table.

   COUNT    - counter value from 0-100 (where 0 is OPEN and 100 is CLOSED)
   F0 - F4  - max/min target positions for each finger

   The function gripMovement() maps an input position value (0-100) to a finger position relating
   to the gripPos[][][] array. This is used to allow for the fingers to pause at a position whilst
   performing a grip movement.

   For a more detailed explanation, have a look at our 'Grip Patterns' tutorial on www.openbionics.com/tutorials

*/

uint8_t gripPos[NUM_GRIPS][NUM_GRIP_STEPS][(NUM_FINGERS * 2) + 1] =	// 3D array holding gripPos sequences
{
  { // FIST
    //COUNT		F0				F1				F2				F3				F4
    {0,			FULLY_OPEN,		FULLY_OPEN,		FULLY_OPEN,		FULLY_OPEN,		FULLY_OPEN},	//OPEN
    {10,		750,			BLANK,			BLANK,			BLANK,			BLANK},			//MIDPOINTA
    {40,		750,			BLANK,			BLANK,			BLANK,			BLANK},			//MIDPOINTB
    {100,		FULLY_CLOSED,	FULLY_CLOSED,	FULLY_CLOSED,	FULLY_CLOSED,	FULLY_CLOSED},	//CLOSED
  },
  { // PALM
    //COUNT		F0				F1				F2				F3				F4
    {0,			FULLY_OPEN,		FULLY_OPEN,		FULLY_OPEN,		FULLY_OPEN,		FULLY_OPEN},	//OPEN
    {BLANK,		BLANK,			BLANK,			BLANK,			BLANK,			BLANK},			//MIDPOINTA
    {BLANK,		BLANK,			BLANK,			BLANK,			BLANK,			BLANK},			//MIDPOINTB
    {100,		FULLY_OPEN,		FULLY_CLOSED,	FULLY_CLOSED,	FULLY_CLOSED,	FULLY_CLOSED},	//CLOSED
  },
  { // THUMBS
    //COUNT		F0				F1				F2				F3				F4
    {0,			FULLY_OPEN,		FULLY_CLOSED,	FULLY_CLOSED,	FULLY_CLOSED,	FULLY_CLOSED},	//OPEN
    {BLANK,		BLANK,			BLANK,			BLANK,			BLANK,			BLANK},			//MIDPOINTA
    {BLANK,		BLANK,			BLANK,			BLANK,			BLANK,			BLANK},			//MIDPOINTB
    {100,		FULLY_CLOSED,	FULLY_CLOSED,	FULLY_CLOSED,	FULLY_CLOSED,	FULLY_CLOSED},	//CLOSED
  },
  { // POINT
    //COUNT		F0				F1				F2				F3				F4
    {0,			FULLY_CLOSED,	FULLY_OPEN,		FULLY_CLOSED,	FULLY_CLOSED,	FULLY_CLOSED},	//OPEN
    {BLANK,		BLANK,			BLANK,			BLANK,			BLANK,			BLANK},			//MIDPOINTA
    {BLANK,		BLANK,			BLANK,			BLANK,			BLANK,			BLANK},			//MIDPOINTB
    {100,		FULLY_CLOSED,	FULLY_CLOSED,	FULLY_CLOSED,	FULLY_CLOSED,	FULLY_CLOSED},	//CLOSED
  },
  { // PINCH
    //COUNT		F0				F1				F2				F3				F4
    {0,			FULLY_OPEN,		FULLY_OPEN,		FULLY_OPEN,		FULLY_OPEN,		FULLY_OPEN},	//OPEN
    {10,		750,			BLANK,			BLANK,			BLANK,			BLANK},			//MIDPOINTA
    {40,		750,			BLANK,			BLANK,			BLANK,			BLANK},			//MIDPOINTB
    {100,		850,			FULLY_CLOSED,	FULLY_OPEN,		FULLY_OPEN,		FULLY_OPEN},	//CLOSED
  },
  { // TRIPOD
    //COUNT		F0				F1				F2				F3				F4
    {0,			FULLY_OPEN,		FULLY_OPEN,		FULLY_OPEN,		FULLY_OPEN,		FULLY_OPEN},	//OPEN
    {10,		870,			  BLANK,			BLANK,			BLANK,			BLANK},			//MIDPOINTA
    {40,		870,			  BLANK,			BLANK,			BLANK,			BLANK},			//MIDPOINTB
    {100,		FULLY_CLOSED,		FULLY_CLOSED,	FULLY_CLOSED,	FULLY_OPEN,		FULLY_OPEN},	//CLOSED
  }
};
