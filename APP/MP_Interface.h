#ifndef MEGA_PROJECT_H
#define MEGA_PROJECT_H

#include "../LIB/Datatypes.h"
typedef struct MP_SYS_STATE
{
    /* data */
    uint16 temprature;
    uint8 n_person_in_house;
} MP_Sys_State_t;

void MP_vInit();
void MP_vStart();
void MP_vMonitor_temprature(void);
void MP_vUltrasonic_Count();
uint8 MP_vUltrasonic_Person_State();
void MP_vUpdate_count_state();

#endif