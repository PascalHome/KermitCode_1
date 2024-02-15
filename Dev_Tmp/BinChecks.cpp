#include "BinChecks.h"
#include "Structures.h"
#include "Setup.h"

extern Bin_Type Bin_[NumberOfBin];  // Set the array of bins
byte Check = 0;

bool Check_BinActive(int _Index){
  if(Bin_[_Index].Active == true){ bitSet(Check,0);} else {bitClear(Check,0);}
  return bitRead(Check,0);
  //?????
  // integrer les test ici 
  // ou faire les tests separement

}



bool Check_Alarm(byte _StartAlarmHours, byte _StartAlarmMinutes, byte _AlarmDuration, byte _CurrentHours, byte _CurrentMinutes ){
  int AlarmStart = (_StartAlarmHours*60) + _StartAlarmMinutes;
  int AlarmStop = AlarmStart + _AlarmDuration;
  int CurrentTime = (_CurrentHours *60) + _CurrentMinutes;  
  if (CurrentTime >= AlarmStart && CurrentTime <= AlarmStop ){ 
    return(true);
    } else {
    return(false);
  }
}

bool Check_Month(int _Index, int _CurrentMonth){
 return (bitRead(Bin_[_Index].CollectionMonth, _CurrentMonth-1)) ; // array commence by 0 so Month -1
}

bool Check_Week (byte _StartingWeek,byte _Frequency, byte _CurrentWeekNumber ){
boolean CheckVal = false;
for (byte i=_StartingWeek;i<=53; i=i+_Frequency){
  if(i==_CurrentWeekNumber){
  CheckVal = true;
  break;
  } else {
   CheckVal = false;
   }
 }
return(CheckVal);
}