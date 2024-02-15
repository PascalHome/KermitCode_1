#ifndef __DATETIME__
#define __DATETIME__

#include <Arduino.h>
#include <TimeLib.h>

void Set_tm (void);
unsigned long OffsetDateTime(int Offset, int &Day, int &Month, int &Year,int &Hour, int &Minute,int &Second );
int tm_YearWeek(const struct tm *tmptr, int *year, int *week);
int calculateDayOfYear(int day, int month, int year);
byte calcDayOfWeek(int d, int m, int y);
int calcWeekNumber(int Day, int Month, int Year);
void getDate (const char *_Date, int &Day, int &Month, int &Year);
bool getTime (const char *_Time, int &Hour, int &Minute,int &Second);
byte NoWeeksInYear (int _Year);

#endif
