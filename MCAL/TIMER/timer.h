#ifndef TIMER_H
#define TIMER_H

#include "../../LIB/Datatypes.h"

typedef struct
{
    uint8 Mode;
    uint8 Enable_Interrupt;

} Timer_Config;

void TIMER0_SetConfig();
// void TIMER0_Delay_with_Blocking(uint16 Milli_Seconds);
void stopTimer0();
void set_Timer0_Prescaler(uint16 prescaler);
// void TIMER0_Delay_Milli_Seconds_with_Blocking(uint16 Milli_Seconds);
// void TIMER0_Delay_MicroSeconds_with_Blocking(uint16 Micro_Seconds);
uint8 equal_with_tolerance(double num1, double num2);

// void TIMER0_Delay_Without_Blocking(uint16 Milli_Seconds);
void TIMER0_Delay_ms_with_Blocking(uint16 Milli_Seconds);
void TIMER0_Delay_us_with_Blocking(uint16 Milli_Seconds);

#endif