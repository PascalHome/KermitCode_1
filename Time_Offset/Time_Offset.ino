#include <TimeLib.h>

unsigned long offset_second = 60;    // 3 days
unsigned long t_unix_date1, t_unix_date2;
tmElements_t te;  //Time elements structure

char Buffer[40];

void setup() {
  Serial.begin(9600);
  t_unix_date1 = 1564398600;
  Serial.print("t_unix_date1: ");
  Serial.println(t_unix_date1);

  
  t_unix_date2 = 1564398600 + offset_second;
  Serial.print("t_unix_date2: ");
  Serial.println(t_unix_date2);

  sprintf(Buffer, "Date1: %4d-%02d-%02d %02d:%02d:%02d\n", year(t_unix_date1), month(t_unix_date1), day(t_unix_date1), hour(t_unix_date1), minute(t_unix_date1), second(t_unix_date1));
  Serial.println(Buffer);

  sprintf(Buffer,"Date2: %4d-%02d-%02d %02d:%02d:%02d\n", year(t_unix_date2), month(t_unix_date2), day(t_unix_date2), hour(t_unix_date2), minute(t_unix_date2), second(t_unix_date2));
   Serial.println(Buffer);
  te.Year = year(t_unix_date2) - 1970;
  te.Month = month(t_unix_date2);
  te.Day = day(t_unix_date2);
  te.Hour = hour(t_unix_date2);
  te.Minute = minute(t_unix_date2);
  te.Second = second(t_unix_date2);

  Serial.println(t_unix_date2 =  makeTime(te));

}

void loop() {

}