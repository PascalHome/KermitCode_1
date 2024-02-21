#include <arduino.h>
#include "Setup.h"
#ifndef _Structure_h
#define _Structure_h

enum {NoColour = 0, White, Green, Blue, Brown, Yellow, Red, Gray} colour;

// #define AlarmStartHour    16
// #define AlarmStartMinute  30
// #define AlarmStopHour     19   
// #define AlarmStopMinute   55

struct Bin_Type{
  bool Active;                    // 1 Active/ 0 inactive
  byte Colour;                    // from enum colour
  byte CollectionDay;             // Sunday = 0, Saturday =6
  byte CoollectionStartWeek;      // Start from week 1 to week n
  byte CollectionFrequency;       // Weeks Odd 1 or Even 2
  int AlarmStartHour;
  int AlarmStartMinute;
  int AlarmStopHour;
  int AlarmStopMinute;
  unsigned int CollectionMonth;   // b0011 1111 1111 1111 (12 months)

}; // Structure size 24 bytes

#endif
