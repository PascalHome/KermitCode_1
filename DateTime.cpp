#include "DateTime.h"

struct tm tm = {0};
tmElements_t te;        //Time elements structure
unsigned long t_unix_date;

byte NoWeeksInYear (int _Year){
  if(_Year==2026 || _Year==2032 ||_Year==2037 || _Year==2043 || _Year==2048 || _Year==2054 || _Year==2060){
    return 53;
  } else {
    return 52;
  }
}


unsigned long OffsetDateTime(int Offset, int &Day, int &Month, int &Year,int &Hour, int &Minute,int &Second ){
 te.Year = Year - 1970;
 te.Month = Month;
 te.Day =  Day;
 te.Hour = Hour;
 te.Minute = Minute;
 te.Second = Second;
 t_unix_date = makeTime(te)+Offset;
 Year = year(t_unix_date);
 Month = month(t_unix_date);
 Day =  day(t_unix_date);
 Hour = hour(t_unix_date);
 Minute = minute(t_unix_date);
 Second = second(t_unix_date);
 return t_unix_date;
}

void Set_tm (void){
  tm.tm_year = 2009-1900; //2021-1970 ! Start in 2000 finish 2136
  tm.tm_mon = 12-1;  // 0 to 11 (December)
  tm.tm_mday = 28; // 3 => W53 / 4 => W1
  tm.tm_isdst = -1;
}
void getDate (const char *_Date, int &Day, int &Month, int &Year){
char StrMonth[3];
static const char month_names[] = "JanFebMarAprMayJunJulAugSepOctNovDec";
sscanf(_Date,"%s %d %d",StrMonth,&Day,&Year);
Month = (strstr(month_names,StrMonth)-month_names)/3+1;
}
bool getTime (const char *_Time, int &Hour, int &Minute,int &Second){
  if(sscanf(_Time, "%d:%d:%d",&Hour, &Minute, &Second) !=3) return false; 
  return true;
}

int calcWeekNumber(int Day, int Month, int Year){
  int y = 0, w = 0;
  tm.tm_year = Year-1900;  //2021-1970 ! Start in 2000 finish 2136
  tm.tm_mon = Month-1;     // 0 to 11 (December)
  tm.tm_mday = Day;        
  tm.tm_isdst = -1;
  int err = tm_YearWeek(&tm, &y, &w);
  return err;
}

//---------------------------------------------------------------
int tm_YearWeek(const struct tm *tmptr, int *year, int *week) {
  struct tm tm = *tmptr;
  if (mktime(&tm) == -1) 
  {
    return 1;
  }

  // Find day-of-the-week: 0 to 6.
  // Week starts on Monday per ISO 8601
  // 0 <= DayOfTheWeek <= 6, Monday, Tuesday ... Sunday
int DayOfTheWeek = (tm.tm_wday + (7 - 1)) % 7;

  // Offset the month day to the Monday of the week.
  tm.tm_mday -= DayOfTheWeek;
  // Offset the month day to the mid-week (Thursday) of the week, 3 days later.
  tm.tm_mday += 3;
  // Re-evaluate tm_year and tm_yday  (local time)
  if (mktime(&tm) == -1) {
    return 1;
  }

  *year = tm.tm_year + 1900;
  // Convert yday to week of the year, stating with 1.
  *week = tm.tm_yday / 7 + 1;
  return *week;
}

int calculateDayOfYear(int day, int month, int year) {
  
  // Given a day, month, and year (4 digit), returns 
  // the day of year. Errors return 999.
  
  int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};
  
  // Verify we got a 4-digit year
  if (year < 1000) {
    return 999;
  }
  
  if (year%4  == 0) {
    if (year%100 != 0) {
      daysInMonth[1] = 29;
    }
    else {
      if (year%400 == 0) {
        daysInMonth[1] = 29;
      }
    }
   }

  // Make sure we are on a valid day of the month
  if (day < 1) 
  {
    return 999;
  } else if (day > daysInMonth[month-1]) {
    return 999;
  }
  
  int doy = 0;
  for (int i = 0; i < month - 1; i++) {
    doy += daysInMonth[i];
  }
  
  doy += day;
  return doy;
}

byte   calcDayOfWeek(int d, int m, int y)                                    
    {                                                                        
      int CalculatedDOW =0;
        static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
        y -= m < 3;
        CalculatedDOW = (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7  ;// Sun=0, Mon=1, Tue=2, Wed=3, Thu=4, Fri=5, Sat=6
        if (CalculatedDOW == 0){
          return (7);
        } else {
          return (CalculatedDOW); 
        }
                 
    }
