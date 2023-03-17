#ifndef OLED_PRIVATE_H
#define OLED_PRIVATE_H

#include "../../LIB/Datatypes.h"

uint8 OLED_Init();
uint8 OLED_Send_Command(uint8 command);
uint8 OLED_Send_Data(uint8 command);

#endif