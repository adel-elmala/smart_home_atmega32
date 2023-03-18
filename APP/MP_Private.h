#ifndef MP_PRIVATE_H
#define MP_PRIVATE_H

#include "../MCAL/DIO/DIO_REG.h"

#define FAN_PORT PORTB
#define FAN_PIN PIN7

#define BUZZER_PORT PORTC
#define BUZZER_PIN PIN6

#define PERSON_ENTERING 0
#define PERSON_EXITING 1
#define PERSON_UNDEFINED 2

typedef enum finger_prints
{
    FP_Adel = 1,
    FP_Husseny,
    FP_Omar,
    FP_Youssef
} Finger_Prints_t;

void MP_vFingerPrint();
void MP_vMonitor_temprature(void);
void MP_vUltrasonic_Count();
uint8 MP_vUltrasonic_Person_State();
void MP_vUpdate_count_state();

#endif