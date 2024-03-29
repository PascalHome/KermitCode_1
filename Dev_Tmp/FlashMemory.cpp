#include "FlashMemory.h"

DueFlashStorage FlashStorage;
Bin_Type Bin_[NumberOfBin];        // Set the array of bins
boolean FS = true;

bool CheckFlashInit(void) {
byte CodeRuningFirstTime = FlashStorage.read(0); // FF blanked flash
if (CodeRuningFirstTime){
  Serial.println("Code running First Time");
  delay(100); // time to check
  return true;}else{
 Serial.println("Code Not running First Time");
  delay(100); // time to check
 return false;}
}

byte WriteFlashInit(void){
  Bin_[0].Active = true;
  Bin_[0].Colour = Green;
  Bin_[0].CollectionDay = 1;
  Bin_[0].CoollectionStartWeek = 1;
  Bin_[0].CollectionFrequency = 2;
  Bin_[0].AlarmStartHour   = 16;
  Bin_[0].AlarmStartMinute = 0;
  Bin_[0].AlarmStopHour   = 20;
  Bin_[0].AlarmStopMinute = 0;
  Bin_[0].CollectionMonth = 0b00111111111111111111;
///-----------------------------------------------------
  Bin_[1].Active = true;
  Bin_[1].Colour = Blue;
  Bin_[1].CollectionDay = 1;
  Bin_[1].CoollectionStartWeek = 2;
  Bin_[1].CollectionFrequency = 2;
  Bin_[1].AlarmStartHour  = 16;
  Bin_[1].AlarmStartMinute = 0;
  Bin_[1].AlarmStopHour   = 20;
  Bin_[1].AlarmStopMinute = 0;
  Bin_[1].CollectionMonth = 0b00111111111111111111;
///-----------------------------------------------------
  Bin_[2].Active = true;
  Bin_[2].Colour = Brown;
  Bin_[2].CollectionDay = 4;
  Bin_[2].CoollectionStartWeek = 2;
  Bin_[2].CollectionFrequency = 2;
  Bin_[2].AlarmStartHour   = 16;
  Bin_[2].AlarmStartMinute = 0;
  Bin_[2].AlarmStopHour   = 20;
  Bin_[2].AlarmStopMinute = 0;
  Bin_[2].CollectionMonth = 0b00000011111111111100;
///-----------------------------------------------------


  byte FlashArray[sizeof(Bin_)];
  memcpy(FlashArray, &Bin_, sizeof(Bin_));
  FlashStorage.write(FlashAddress,FlashArray, sizeof(Bin_));
  FlashStorage.write(0,0);
  Serial.println("Values wrote into Flash Memory");
  delay(1000);
}

int ReadFlash(void){
if (FS == true){
 byte* b1 = FlashStorage.readAddress(FlashAddress);
 Bin_Type Tmp1[NumberOfBin];              // Set the array of bins
 memcpy(&Bin_, b1, sizeof(Bin_));
 Serial.println("Read from Flash");
  for(int a=0; a< NumberOfBin; a++){
  // Serial.println(Bin_[a].Active);
  // Serial.println(Bin_[a].Colour);
  // Serial.println(Bin_[a].CollectionDay);
  // Serial.println(Bin_[a].CoollectionStartWeek);
  // Serial.println(Bin_[a].CollectionFrequency);
  // Serial.println(Bin_[a].CollectionMonth);
  // Serial.println(Bin_[a].AlarmStartHour);
  // Serial.println(Bin_[a].AlarmStartMinute);
  // Serial.println(Bin_[a].AlarmDuration);
  // Serial.println("--------------------");  
    }
   FS = false; } else
   {
   byte* b1 = FlashStorage.readAddress(FlashAddress);
   Bin_Type Tmp1[NumberOfBin];              // Set the array of bins
   memcpy(&Bin_, b1, sizeof(Bin_));
   Serial.println("Read from Flash");
  for(int a=0; a< NumberOfBin; a++){
  // Serial.println(Bin_[a].Active);
  // Serial.println(Bin_[a].Colour);
  // Serial.println(Bin_[a].CollectionDay);
  // Serial.println(Bin_[a].CoollectionStartWeek);
  // Serial.println(Bin_[a].CollectionFrequency);
  // Serial.println(Bin_[a].CollectionMonth);
  // Serial.println(Bin_[a].AlarmStartHour);
  // Serial.println(Bin_[a].AlarmStartMinute);
  // Serial.println(Bin_[a].AlarmDuration);
  // Serial.println("--------------------");
     }
    }
  }