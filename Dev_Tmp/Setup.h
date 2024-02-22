#include <arduino.h>
#include <string.h>
#ifndef _Setup_h
#define _Setup_h

#define NumberOfBin 3
#define FlashAddress 4
//---------------------------------------------
static char *ShortMonthString[13] ={ "---", "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
static char *ShortDayString[8]    ={"---","Mon","Tue","Wed","Thu","Fri","Sat","Sun"}; 
static char *BinColour[8]         ={"---","White", "Green", "Blue","Brown","Yellow","Red","Gray"};
// from enum {NoColour = 0, White, Green, Blue, Brown, Yellow, Red, Gray} colour;
//------------------Start page ----------------
const char SoftwareName[] =       "BinDeal"; 
const char SoftwareVersion[] =    " 1.A";
const char DevelopperNickName[] = "KermitCode";
//--------------------------------------------


#endif
