// 15/Feb/2024 - KermitCode_1-Dev01 to GitHub 
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
#define Delay3Second 3 
#define Delay5Second 5
#define Delay10Second 10
unsigned long SecondCount = 0;
//------------------------ Timer2 --------------------------
unsigned long Timer2_CurrentMillis  = 0;
unsigned long Timer2_PrevoiusMillis = 0;
unsigned long Timer2_Interval       = 5000;
unsigned long IndexCount = 0;
//----------------------- State machine --------------------
#define InitialStep 3
byte CurrentState = 0;
#define GoToStep(a) CurrentState = a;  // Textual substitution 
//--------------------- Global variable --------------
int Day,Month, Year, Hour, Minute,Second,DoW;
int DoY, DiY, WeekNo, WeekInYear;
DS3231 SysClock;                // I2C Realtime clock
//char Buffer[21];              // Buffer for sprintf
//-----------------------------------------------------
void setup() {
  ResetUART();
  Serial.begin(9600);
  // Check flash memory on boot and download if necessary 
  if (CheckFlashInit()){  WriteFlashInit();}
  ReadFlash();                                          // Read falash content and write Bin_[X] values
  // ------------- Get GDH from compilation ----------
  getDate(__DATE__,Day,Month,Year);
  getTime(__TIME__,Hour,Minute,Second);
  //-------------- Offset GDHn -----------------------
  OffsetDateTime(21,Day,Month,Year,Hour,Minute,Second); // Estimated offset 18 seconds
  //------------------Display result -----------------
  Serial.print("Day of the year: ");
  Serial.println(calculateDayOfYear(Day, Month, Year));  //Serial.println(calculateDayOfYear(28, 11, 2023));
  Serial.print("Day of the week: ");  
  Serial.println(calcDayOfWeek(Day, Month, Year));      //Serial.println(calcDayOfWeek(28, 11, 2023));
  Serial.print("Week Number: ");
  Serial.println(calcWeekNumber(Day,Month,Year));      //Serial.println(calcWeekNumber(28,11,2023));
  //-------------- Set DS3231 DateTime----------------
  Wire.setClock(400000); // I2C at 400 kHz  
  Wire.begin();
  SysClock.begin();      // Init RTC
  SysClock.fillByYMD(Year,Month,Day); 
  SysClock.fillByHMS(Hour,Minute,Second);
  SysClock.fillDayOfWeek((calcDayOfWeek(Day, Month, Year)));
  SysClock.setTime();
  //-------------------------------------------------- 
   Display_Init(); 
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
//*************************** Check bin **************************
// unsigned long Timer2_CurrentMillis  = 0;
// unsigned long Timer2_PrevoiusMillis = 0;
// unsigned long Timer2_Interval       = 2000;
// unsigned long IndexCount = 0;

switch(CurrentState){
 case 0: // initial step ---- Nag Screen
   Display_StartPage(Green,Delay3Second); // White, Green, Blue, Brown, Yellow, Red, Gray
   Timer1_PrevoiusMillis= 0;
   SecondCount =- (Delay3Second+1); // adjust SecondCount to reflect reality of time elapsed second
   Display_Clear();
   GoToStep(1);
 break;
 case 1: //display dateTime from RTC
   Display_DateTimePage_1(White,Year,Month,Day,Hour,Minute,Second,DoW);
   delay(1000);
   if (SecondCount % Delay5Second == 1) {
    Display_Clear();
    GoToStep(2);}  
  break;
 case 2: //
    Display_DateTimePage_2(White, DoY,DiY,WeekNo,WeekInYear);
   delay(1000);
   if (SecondCount % Delay5Second == 1) {
    Display_Clear();
    GoToStep(3);}  
 break;
 case 3: // Bin check *******************************************
  Timer2_CurrentMillis = millis();
  if (Timer2_CurrentMillis - Timer2_PrevoiusMillis >=Timer2_Interval)
  {
   if ((Check_BinActive(IndexCount) == true) 
      &&  (Check_Month(IndexCount, 2)))
    {
     //------------------------- Debug ---------------------------
      Serial.print("Month active  : ");
      Serial.println(Check_Month(IndexCount, 2));
      Serial.print("index = "); 
      Serial.print(IndexCount); 
      Serial.print(" -> "); 
      Serial.println("Bin Active");
      //-----------------------------------------------------------
      Display_CurrentBin(Bin_[IndexCount].Colour, DoW,Day,Month,Year);
      


      IndexCount++; 
  if (IndexCount >= NumberOfBin ) {IndexCount = 0;}
   Timer2_PrevoiusMillis = Timer2_CurrentMillis;
  } else{
  IndexCount++; 
if (IndexCount >= NumberOfBin) {IndexCount = 0;}
  }
  } 
   
   // GoToStep(4);
 break;
 //**************************************************************
 case 4: // Check bins
   GoToStep(1);
 break;
 case 5: // spare
   GoToStep(6);
 break;
 case 6: // Return to Step 1
   GoToStep(1);
 break;
   }
}

