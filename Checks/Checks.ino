int StartingWeek        = 1; 
int Frequency           = 2; 
int CurrentWeekNumber   = 51; // returns 1
// CurrentWeekNumber       = 51; // returns 1
// CurrentWeekNumber       = 29; // returns 1
int ValideMonths        = 0b0000000000000011; // here we have January and February
int CurrentMonth        = 1;                  // January 
//-----------------------------------------------
byte StartAlarmHours     = 17;   
byte StartAlarmMinutes   = 1;     
byte AlarmDuration       = 2*60; // 120 minutes = 2 hours
byte CurrentHours        = 19;
byte CurrentMinutes      = 2;
//------------------------------------------------
void setup(){
  Serial.begin(9600);
}

void loop() {
  delay(1000);
  Serial.print("Week is valide: ");
  Serial.println(CheckWeek(StartingWeek,Frequency,CurrentWeekNumber));
  Serial.print("Month is valide: ");
  Serial.println(CheckMonth(ValideMonths, CurrentMonth));
  Serial.print("Alarm is valide: ");
  Serial.println(CheckAlarm(StartAlarmHours, StartAlarmMinutes, AlarmDuration, CurrentHours, CurrentMinutes));
}

bool CheckAlarm(byte _StartAlarmHours, byte _StartAlarmMinutes, byte _AlarmDuration, byte _CurrentHours, byte _CurrentMinutes ){
  int AlarmStart = (_StartAlarmHours*60) + _StartAlarmMinutes;
  int AlarmStop = AlarmStart + _AlarmDuration;
  int CurrentTime = (_CurrentHours *60) + _CurrentMinutes;  
  if (CurrentTime >= AlarmStart && CurrentTime <= AlarmStop ){ 
    return(true);
    } else {
    return(false);
  }
}

bool CheckWeek (byte _StartingWeek,byte _Frequency, byte _CurrentWeekNumber ){
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

bool CheckMonth(int _ValideMonths, byte _CurrentMonth){
 return (bitRead(_ValideMonths, _CurrentMonth-1)) ; // array commence by 0 so Month -1
}

