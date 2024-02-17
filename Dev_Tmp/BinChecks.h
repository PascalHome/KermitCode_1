#include <arduino.h>

#ifndef _BinChecks_h
#define _BinChecks_h

bool Check_Alarm(int _Index, byte _CurrentHour, byte _CurrentMinute);
bool Check_Week (int _Index, byte _CurrentWeekNumber );
bool Check_Month(int _Index, int _CurrentMonth);
bool Check_BinActive(int _Index);
bool Check_Day(int _Index, byte _DoW);
#endif