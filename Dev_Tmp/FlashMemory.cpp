#include "FlashMemory.h"

DueFlashStorage FlashStorage;
Bin_Type Bin_[NumberOfBin];        // Set the array of bins
boolean FS = true;

byte CheckFlashInit(void) {
byte CodeRuningFirstTime = FlashStorage.read(0); // FF blanked flash
if (CodeRuningFirstTime){
  Serial.println("Code running First Time");
  delay(5000);
  return 1;}else{
 Serial.println("Code Not running First Time");
  delay(1000);
 return 0;}
}

byte WriteFlashInit(void){
  Bin_[0].Active = true;
  Bin_[0].Colour = Green;
  Bin_[0].CollectionDay = 1;
  Bin_[0].CoollectionStartWeek = 1;
  Bin_[0].CollectionFrequency = 2;   
  Bin_[0].CollectionMonth = 0b00111111111111111111;
///-----------------------------------------------------
  Bin_[1].Active = true;
  Bin_[1].Colour = Blue;
  Bin_[1].CollectionDay = 1;
  Bin_[1].CoollectionStartWeek = 2;
  Bin_[1].CollectionFrequency = 2;   
  Bin_[1].CollectionMonth = 0b00111111111111111111;
///-----------------------------------------------------
  Bin_[2].Active = true;
  Bin_[2].Colour = Brown;
  Bin_[2].CollectionDay = 4;
  Bin_[2].CoollectionStartWeek = 2;
  Bin_[2].CollectionFrequency = 2;   
  Bin_[2].CollectionMonth = 0b00001111111111111000;
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
  Serial.println(Bin_[a].Active);
  Serial.println(Bin_[a].Colour);
  Serial.println(Bin_[a].CollectionDay);
  Serial.println(Bin_[a].CoollectionStartWeek);
  Serial.println(Bin_[a].CollectionFrequency);
  Serial.println(Bin_[a].CollectionMonth);
  Serial.println("--------------------");  }
   FS = false; } else
   {
   byte* b1 = FlashStorage.readAddress(FlashAddress);
   Bin_Type Tmp1[NumberOfBin];              // Set the array of bins
   memcpy(&Bin_, b1, sizeof(Bin_));
   Serial.println("Read from Flash");
  for(int a=0; a< NumberOfBin; a++){
  Serial.println(Bin_[a].Active);
  Serial.println(Bin_[a].Colour);
  Serial.println(Bin_[a].CollectionDay);
  Serial.println(Bin_[a].CoollectionStartWeek);
  Serial.println(Bin_[a].CollectionFrequency);
  Serial.println(Bin_[a].CollectionMonth);
  Serial.println("--------------------");  }
   }
   }