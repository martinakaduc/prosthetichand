/*	Open Bionics - Artichoke
	Author - Olly McBride
	Date - December 2015

	This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License.
	To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/.

	Website - http://www.openbionics.com/
	GitHub - https://github.com/Open-Bionics
	Email - ollymcbride@openbionics.com

	Utils.h

*/

#include <Arduino.h>  // for type definitions

// Architecture specific include
#include <EEPROM.h>
long map(long x, long in_min, long in_max, long out_min, long out_max);


//#define EEPROM_DEBUG

template <class T> int EEPROM_writeStruct(int ee, const T& value)
{
#ifdef EEPROM_DEBUG
  MYSERIAL_PRINTLN_PGM("EEPROM_writeStruct");
#endif
  const byte* p = (const byte*)(const void*)&value;
  unsigned int i;
  for (i = 0; i < sizeof(value); i++)
  {
#ifdef EEPROM_DEBUG
    MYSERIAL_PRINT_PGM("addr ee ");
    MYSERIAL_PRINT_PGM(ee);
    MYSERIAL_PRINT_PGM("     val *p ");
    MYSERIAL_PRINTLN_PGM(*p);
#endif
    EEPROM.write(ee++, *p++);
  }

  return i;
}

template <class T> int EEPROM_readStruct(int ee, T& value)
{
#ifdef EEPROM_DEBUG
  MYSERIAL_PRINTLN_PGM("EEPROM_readStruct");
#endif
  byte* p = (byte*)(void*)&value;
  unsigned int i;
  for (i = 0; i < sizeof(value); i++)
  {
    *p++ = EEPROM.read(ee++);
#ifdef EEPROM_DEBUG
    MYSERIAL_PRINT_PGM("addr ee ");
    MYSERIAL_PRINT_PGM(ee - 1);
    MYSERIAL_PRINT_PGM("     val *p ");
    MYSERIAL_PRINTLN_PGM(*(p - 1));
#endif
  }

  return i;
}

template <class T> int clearStruct(T& value, int newVal)
{
#ifdef EEPROM_DEBUG
  MYSERIAL_PRINTLN_PGM("clearStruct");
#endif
  byte* p = (byte*)(void*)&value;
  unsigned int i;
  for (i = 0; i < sizeof(value); i++)
  {
    *p++ = newVal;
#ifdef EEPROM_DEBUG
    MYSERIAL_PRINT_PGM("     val *p ");
    MYSERIAL_PRINTLN_PGM(*(p - 1));
#endif
  }

  return i;
}
