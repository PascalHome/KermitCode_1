#include"DueHardware.h"

void ResetUART(void){
  UART->UART_CR = UART_CR_RSTRX | UART_CR_RSTTX | UART_CR_RSTSTA;
}

void FlushUART(void){
 Serial.flush();
 Serial.end();
 __DSB;
 __DMB;
 __ISB;
}
void DueSoftwareReset(void){
 __DSB;
 SCB->AIRCR = ((0x5FA << SCB_AIRCR_VECTKEY_Pos) | SCB_AIRCR_SYSRESETREQ_Msk);
}