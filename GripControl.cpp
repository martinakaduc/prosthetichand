/*	Open Bionics - Artichoke
	Author - Olly McBride
	Date - December 2015

	This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License.
	To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/.

	Website - http://www.openbionics.com/
	GitHub - https://github.com/Open-Bionics
	Email - ollymcbride@openbionics.com

	GripControl.cpp

*/

#include <Arduino.h>			// for type definitions
#include "Globals.h"

#include "GripControl.h"
#include "GripPositions.h"

/*
   Instead of using a lookup table, calculate the position of the finger by mapping the target input pos (inPos) to
   the values within the gripPos array. This also allows for the finger to remain at a set position for a period
   of time and then continue the grip pattern.

   The function looks through the array of positions for the specific grip and maps inPos to the grip position
   values within the array for each finger.

   How it works:
   - A target position (0-100) is input to the function along with the desired grip number
   - If the target position is between two count values, the output target position of the finger is mapped
   between the grip position values within the array that correspond to the count values
   - If a BLANK (-1) is encountered, the function looks at the next value within the array that isn't
   a BLANK (-1)
   For a more detailed explanation, have a look at our 'Grip Patterns' tutorial on www.openbionics.com/tutorials
*/
void gripMovement(int gripNum, int inPos, int dir, int speed)
{
  int i;

  if (inPos == BLANK)
  {
    if (dir == OPEN)
      inPos = 0;
    if (dir == CLOSE)
      inPos = 100;
  }

  if (dir != BLANK)
    currentDir = dir;

  if (speed != BLANK)
  {
    for (i = 0; i < NUM_FINGERS; i++)
    {
      //inPos = inPos + speed * POS_REACHED_TOLERANCE / (MAX_FINGER_SPEED - MIN_FINGER_SPEED);
    }
  }
  gripMovement(gripNum, inPos);
}

void gripMovement(int gripNum, int inPos)
{
  int fingerNum;
  int stepNum;
  int posA, posB;
  int countA, countB;
  int stepModA = 0, stepModB = 0;
  int currentCountVal, nextCountVal;

  inPos = constrain(inPos, 0, 100);

  for (stepNum = 0; stepNum < NUM_GRIP_STEPS; stepNum++)
  {
    currentCountVal = gripPos[gripNum][stepNum][GRIP_COUNT_LOC];
    nextCountVal = gripPos[gripNum][stepNum + 1][GRIP_COUNT_LOC];

    if (IS_BETWEEN(inPos, currentCountVal, nextCountVal))
    {
      for (fingerNum = 0; fingerNum < NUM_FINGERS; fingerNum++)
      {
        do
        {
          posA = gripPos[gripNum][(stepNum - stepModA)][fingerNum + 1];
          if (posA == BLANK)
            stepModA ++;
        } while (posA == BLANK);

        do
        {
          posB = gripPos[gripNum][(stepNum + 1 + stepModB)][fingerNum + 1];
          if (posB == BLANK)
            stepModB ++;
        } while (posB == BLANK);

        countA = gripPos[gripNum][(stepNum - stepModA)][GRIP_COUNT_LOC];
        countB = gripPos[gripNum][(stepNum + 1 + stepModB)][GRIP_COUNT_LOC];

        finger[fingerNum].write(map(inPos, countA, countB, posA, posB));
        Serial.print("  Servo: ");
        Serial.print(map(inPos, countA, countB, posA, posB));
        stepModA = 0;
        stepModB = 0;
      }
      break;
    }
  }
  Serial.println();
}
