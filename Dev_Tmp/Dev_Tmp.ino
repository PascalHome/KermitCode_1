// 15/Feb/2024 - KermitCode_1-Dev01 to GitHub
// 15/Feb/2024 - KermitCode_1-Dev02 Arduino IDE From 2.3.0 to 2.3.1
// 15/Feb/2024 - KermitCode_1-Dev03 implementation of check
// 16/Feb/2024 - KermitCode_1-Dev04 Refactoring of function Check_Day()
// 16/Feb/2024 - KermitCode_1-Dev05 Integration Hr/Min to Bin structure + record to Flashmemory
// 21/Feb/2024 - KermitCode_1-Dev06 Code stable !
// 21/Feb/2024 - KermitCode_1-Dev07 Code refactoring Version 1.A
//                                  Arduino IDE From 2.3.1 to 2.3.2
// 26/Feb/2024 - KermitCode_1-Dev08 Issue with date/Time code refactoring 1.C


//-------------------- Included files ----------------------
#include "DueHardware.h"
#include "Setup.h"
#include "Structures.h"
#include "FlashMemory.h"
#include "DateTime.h"
#include "DS3231.h"
#include "BinChecks.h"
#include "LCD_I2C.h"
#include <Wire.h>
// ---------------------- Timer1 ---------------------------
unsigned long Timer1_CurrentMillis  = 0;
unsigned long Timer1_PrevoiusMillis = 0;
unsigned long Timer1_Interval       = 1000;
#define Delay2Second 2
#define Delay3Second 3 
#define Delay5Second 5
#define Delay10Second 10
unsigned long SecondCount = 0;
//------------------------ Timer2 --------------------------
unsigned long Timer2_CurrentMillis  = 0;
unsigned long Timer2_PrevoiusMillis = 0;
unsigned long Timer2_Interval       = 3000;
unsigned long IndexCount = 0;
//----------------------- State machine --------------------
#define InitialStep 0
byte CurrentState = 0;
#define GoToStep(a) CurrentState = a;  // Textual substitution 
//--------------------- Global variable --------------
int Day,Month, Year, Hour, Minute,Second,DoW;
int DoY, DiY, WeekNo, WeekInYear;
DS3231 SysClock;                // I2C Realtime clock
//-----------------------------------------------------
void setup() {
  ResetUART();
  Serial.begin(9600);
  Wire.begin();
  Wire.setClock(400000); // I2C at 400 kHz  
  SysClock.begin();      // Init RTC

  // Check flash memory on boot and download if necessary 
  if (CheckFlashInit()){  WriteFlashInit();
  ReadFlash();                                          // Read falash content and write Bin_[X] values
  // ------------- Get GDH from compilation ----------
  getDate(__DATE__,Day,Month,Year);
  getTime(__TIME__,Hour,Minute,Second);
  //-------------- Offset GDHn -----------------------
  OffsetDateTime(5,Day,Month,Year,Hour,Minute,Second); // Estimated offset 18 seconds
  //-------------- Set DS3231 DateTime----------------
  SysClock.fillByYMD(Year,Month,Day); 
  SysClock.fillByHMS(Hour,Minute,Second);
  SysClock.fillDayOfWeek((calcDayOfWeek(Day, Month, Year)));
  SysClock.setTime();
  //-------------------------------------------------- 
   } else {
  Display_Init(); 
  ReadFlash();
  }
  //------------------Display result -----------------
  // Serial.print("Day of the year: ");
  // Serial.println(calculateDayOfYear(Day, Month, Year));  //Serial.println(calculateDayOfYear(28, 11, 2023));
  // Serial.print("Day of the week: ");  
  // Serial.println(calcDayOfWeek(Day, Month, Year));      //Serial.println(calcDayOfWeek(28, 11, 2023));
  // Serial.print("Week Number: ");
  // Serial.println(calcWeekNumber(Day,Month,Year));      //Serial.println(calcWeekNumber(28,11,2023));
  //----------------------------------------------------
   CurrentState = InitialStep; // initialise state machine
   //---------------------------------------------------
  }
void loop(){
Timer1_CurrentMillis = millis();
  if ((Timer1_CurrentMillis - Timer1_PrevoiusMillis >=Timer1_Interval) && (CurrentState !=0) ){
   Timer1_PrevoiusMillis = Timer1_CurrentMillis;
   //*********************** Update from RTC **********************
   SysClock.getTime();
   Year=    SysClock.year; 
   Month =  SysClock.month;
   Day =    SysClock.dayOfMonth;
   Hour =   SysClock.hour;
   Minute = SysClock.minute;
   Second = SysClock.second;
   DoW =    SysClock.dayOfWeek;
   //*********************** Update Calculated *******************
   DoY =    calculateDayOfYear(Day,Month,Year+2000);  // Current day in the year
   DiY =    calculateDayOfYear(31,12,Year+2000);      // Number of day in the year
   WeekNo = calcWeekNumber(Day,Month,Year);           // Week number
   WeekInYear = NoWeeksInYear (Year);     
   SecondCount++;
}
switch(CurrentState){
 case 0: // initial step ---- Nag Screen
   Display_StartPage(White,Delay2Second); // White, Green, Blue, Brown, Yellow, Red, Gray
   Timer1_PrevoiusMillis= 0;
   SecondCount =- (Delay2Second); // adjust SecondCount to reflect reality of time elapsed second
   Display_Clear();
   GoToStep(1);
 break;
 case 1: //display dateTime from RTC
   Display_DateTimePage_1(White,Year,Month,Day,Hour,Minute,Second,DoW);
   delay(1000);
   if (SecondCount % Delay5Second == 1) {
    Display_Clear();
    Serial.println("In step 1");
    GoToStep(2);}  
  break;
 case 2: //
  Display_DateTimePage_2(White, DoY,DiY,WeekNo,WeekInYear);
   delay(1000);
   if (SecondCount % Delay5Second == 1) {
    Display_Clear();
     GoToStep(3);
    }  
 break;
 case 3: // Bin check *******************************************
    for(IndexCount=0;IndexCount<NumberOfBin;IndexCount++){
        if ((Check_BinActive(IndexCount)) 
          & (Check_Month(IndexCount, Month))
          & (Check_Week(IndexCount, WeekNo))
          & (Check_Day (IndexCount,DoW))
          & (Check_Month(IndexCount, Month))
          & (Check_Alarm (IndexCount,Hour, Minute)) == true) 
         {
          Display_CurrentBin(Bin_[IndexCount].Colour, DoW,Day,Month,Year);
          Serial.print("Time ");Serial.print(Hour);Serial.print(":");Serial.print(Minute);Serial.print(":");Serial.println(Second);
          Serial.print("IndexCount: "); Serial.print(IndexCount); Serial.print(" - "); 
          Serial.print("Active: "); Serial.print(Check_BinActive(IndexCount)); Serial.print(" - "); 
          Serial.print("Nonth: "); Serial.print(Check_Month(IndexCount, Month)); Serial.print(" - "); 
          Serial.print("WeekNo: "); Serial.print(Check_Week(IndexCount, WeekNo)); Serial.print(" - ");
          Serial.print("DOW: "); Serial.print(Check_Day (IndexCount,DoW)); Serial.print(" - ");
          Serial.print("Alarm: "); Serial.println(Check_Alarm (IndexCount,Hour, Minute)); 
          delay(5000);
         }
    } GoToStep(1);

 break;
 //**************************************************************
 case 4:
 Serial.println("In step 4");
   GoToStep(5);
 break;
 case 5: // spare
 Serial.println("In step 5");
   GoToStep(6);
 break;
 case 6: // Return to Step 1
  Serial.println("In step 6");
   GoToStep(1);
 break;
   }
}

