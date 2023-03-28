#ifndef MEGA_PROJECT_H
#define MEGA_PROJECT_H

#include "../../LIB/Datatypes.h"
typedef struct MP_SYS_STATE
{
    /* data */
    uint16 temprature;
    uint8 n_person_in_house;
    uint16 distance;
    char *fp_owner_name;
} MP_Sys_State_t;

void MP_vInit();
void MP_vStart();
void MP_vInit_FIRST_TIME();
void MP_vUltraSonic();

#endif