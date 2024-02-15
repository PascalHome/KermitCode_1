#include "Setup.h"
#include "Structures.h"
#include "FlashMemory.h"

void setup() {
Serial.begin(9600);
 // Check flash memory on boot and download if necessary 
 if (CheckFlashInit()){
  WriteFlashInit();}
}

void loop() 
{
  ReadFlash(); // on FS 
 
}


