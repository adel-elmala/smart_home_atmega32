#ifndef OLED_INTERFACE_H
#define OLED_INTERFACE_H

#include "../../LIB/Datatypes.h"

#define OLED_MAX_WIDTH 128
#define OLED_MAX_HEIGHT 64

uint8 OLED_Write_Col(uint8 byte, uint8 col, uint8 page);

#endif
