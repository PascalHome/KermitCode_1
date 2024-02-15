#include <Arduino.h>
#include "LCD_I2C.h"
#include "DFRobot_RGBLCD.h"

DFRobot_RGBLCD Lcd(16,2);  //16 characters and 2 lines of show
char buf[21];  // Buffer for sprintf
void Display_Clear(void){
 Lcd.clear();
}

void Display_CurrentBin(byte _Index, byte _DoW, byte _Day, byte _Month, byte _Year){
   Display_SetColor(_Index);
  Lcd.setCursor(0,0); 
  sprintf(buf,"%s %02d %s %d",ShortDayString[_DoW],_Day,ShortMonthString[_Month],_Year+2000 );
  Lcd.print(buf);
  Lcd.setCursor(0,1); 
  // Calculate to center test onto the display !!
  // Clear the line 1 before !!
  sprintf(buf,"%s", BinColour[_Index]);
  Lcd.print(buf);

}

void Display_DateTimePage_1(byte Colour, byte _Year, byte _Month, byte _Day, byte _Hour, byte _Minute, byte _Second, byte _DoW){
Display_SetColor(Colour);
Lcd.setCursor(0,0); 
sprintf(buf,"%s %02d/%s/%d",ShortDayString[_DoW],_Day,ShortMonthString[_Month],_Year+2000);
Lcd.print(buf);
Lcd.setCursor(0,1); 
sprintf(buf,"    %02d:%02d:%02d", _Hour,_Minute,_Second);
Lcd.print(buf);
}


 //  DoY =    calculateDayOfYear(Day,Month,Year);  // Current day in the year
 //  DiY =    calculateDayOfYear(31,12,Year);      // Number of day in the year
 //  WeekNo = calcWeekNumber(Day,Month,Year);      // Week number
 //  WeekInYear = calcWeekNumber (31,12,Year);;    // number of week in the year
void Display_DateTimePage_2(byte Colour, int _DoY, int _DiY, int _WeekNo, int _WeekInYear){
 Display_SetColor(Colour);
 Lcd.setCursor(0,0); 
 sprintf(buf,"Dy %03d/%03d >%03d",_DoY,_DiY, (_DiY-_DoY));
 Lcd.print(buf);
 Lcd.setCursor(0,1); 
 sprintf(buf,"Wk %02d/%02d", _WeekNo, _WeekInYear);
 Lcd.print(buf);
} 




void Display_Init(void)
{
  // use low level functions provided by "DFRobot_RGBLCD.h"
  Lcd.init();
  Lcd.display();       // option turn on display txt and RGB
  Lcd.noBlinkLED();
  Lcd.stopBlink();
  Lcd.noCursor();
  Lcd.clear();
}

void Display_StartPage(byte Colour, int Second)
{
Display_SetColor(Colour);
Lcd.setCursor(0,0); 
sprintf(buf,"%s %s" ,SoftwareName, SoftwareVersion);
Lcd.print(buf); 
Lcd.setCursor(0,1); 
sprintf(buf,"%s" ,DevelopperNickName);
Lcd.print(buf);
delay(Second * 1000); 
Lcd.clear();
}
void Display_SetColor(byte _Colour)
{
   // enum {NoColour = 0, White, Green, Blue, Brown, Yellow, Red, Gray} colour;
   switch(_Colour)
  {
    case 0:
     Lcd.setRGB(0, 0, 0);       // No colour
     break;
    case 1:
     Lcd.setRGB(124, 124, 124);    // white
     break;
    case 2: 
     Lcd.setRGB(0, 124, 0);     // Green    
     break;
    case 3:
     Lcd.setRGB(0, 0, 124);     // Blue     
     break;
    case 4:
     Lcd.setRGB(121, 63, 13);   // Brown 
     break;
    case 5:
     Lcd.setRGB(124,125,124);   // Yellow
     break;
    case 6:
     Lcd.setRGB(124,0,0);       // Red
     break;
    case 7:
     Lcd.setRGB(220,220,220);    // Gray
     break;
   }
}
