#include "BinChecks.h"
#include "Structures.h"
#include "Setup.h"

extern Bin_Type Bin_[NumberOfBin];  // Set the array of bins
byte Check = 0;

bool Check_Day(int _Index, byte _DoW){
  if(Bin_[_Index].CollectionDay == _DoW){
    return true;} 
    else{return false;}
}

bool Check_BinActive(int _Index){
  if(Bin_[_Index].Active == true){ bitSet(Check,0);} else {bitClear(Check,0);}
  return bitRead(Check,0);
}

bool Check_Alarm(int _Index, byte _CurrentHour, byte _CurrentMinute){
  int AlarmStart = (Bin_[_Index].AlarmStartHour*60) + Bin_[_Index].AlarmStartMinute;
  int AlarmStop = AlarmStart + Bin_[_Index].AlarmDuration;
  int CurrentTime = (_CurrentHour *60) + _CurrentMinute;  
  if (CurrentTime >= AlarmStart && CurrentTime <= AlarmStop ){ 
    return(true);
    } else {
    return(false);
  }
}

bool Check_Month(int _Index, int _CurrentMonth){
 return (bitRead(Bin_[_Index].CollectionMonth, _CurrentMonth-1)) ; // array commence by 0 so Month -1
}

// Actually we should just pass to the function the array index
bool Check_Week (int _Index, byte _CurrentWeekNumber ){

//(Bin_[IndexCount].CoollectionStartWeek,Bin_[IndexCount].CollectionFrequency

boolean CheckVal = false;
for (byte i=Bin_[_Index].CoollectionStartWeek;i<=53; i=i+Bin_[_Index].CollectionFrequency){
  if(i==_CurrentWeekNumber){
  CheckVal = true;
  break;
  } else {
   CheckVal = false;
   }
 }
return(CheckVal);
}