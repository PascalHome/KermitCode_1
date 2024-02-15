#include "Arduino.h"
#include "Structures.h"
#include "Setup.h"

#ifndef LCD_I2C_h
#define LCD_I2C_h

void Display_Init(void);
void Display_SetColor(byte _Colour);
void Display_Clear(void);
void Display_StartPage(byte Colour, int Second);
void Display_DateTimePage_1(byte Colour, byte _Year, byte _Month, byte _Day, byte _Hour, byte _Minute, byte _Second, byte _DoW);
void Display_DateTimePage_2(byte Colour, int _DoY, int _DiY, int _WeekNo, int _WeekInYear);
void Display_CurrentBin(byte _Index, byte _DoW, byte _Day, byte _Month, byte _Year);


//void LCD_DisplayDateTimeInfo(void);
//void LCD_DisplayCalendarInfo(void);
//void LCD_DisplayBinInfo(void);
#endif
