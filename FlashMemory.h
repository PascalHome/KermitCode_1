#include <arduino.h>
#include <DueFlashStorage.h>
#include "Structures.h"

#ifndef _FlashMemory_h
#define _FlashMemory_h

extern Bin_Type Bin_[NumberOfBin];  // Set the array of bins

byte CheckFlashInit(void); // Check if memory is blank
byte WriteFlashInit(void); // Write initial values
int WriteFlash(void);
int ReadFlash(void);
#endif