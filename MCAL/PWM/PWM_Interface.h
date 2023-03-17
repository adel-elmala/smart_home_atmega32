#ifndef PWM_INTERFACE_H
#define PWM_INTERFACE_H
#include "../../LIB/Datatypes.h"

// #define FAST_PWM_MODE
#define CORRECT_PHASE_PWM_MODE
// #define INVERTING_POLARITY
#define NON_INVERTING_POLARITY

void PWM_Init();
void PWM_Generate_CHANNELA(uint8 Copy_u8DutyCycle, uint32 Copy_u32freq);
void PWM_Generate_CHANNELB(uint8 Copy_u8DutyCycle, uint32 Copy_u32freq);
#endif