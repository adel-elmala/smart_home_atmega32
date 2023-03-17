#ifndef EEPROM_INTERFACE_H
#define EEPROM_INTERFACE_H

#include "../../LIB/Datatypes.h"

void EEPROM_Write_Byte(uint8 byte, uint16 eeprom_address);
void EEPROM_Write_Buffer(uint8 *buffer, uint16 buffer_size, uint16 eeprom_address);

uint8 EEPROM_Read_Byte(uint16 eeprom_address);
void EEPROM_Read_Buffer(uint8 *buffer, uint16 buffer_size, uint16 eeprom_address);

#endif