#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H

#include "../../LIB/Datatypes.h"

void DIO_vSetPinDirection(uint8 Copy_u8PORT, uint8 Copy_u8PinNumber, uint8 copy_u8state);
void DIO_vWritePin(uint8 Copy_u8PORT, uint8 Copy_u8PinNumber, uint8 Copy_u8value);
void DIO_vTogglePin(uint8 Copy_u8PORT, uint8 Copy_u8PinNumber);
uint8 DIO_u8GetPinValue(uint8 Copy_u8PORT, uint8 Copy_u8PinNumber);
void DIO_vSetPortDirection(uint8 Copy_u8PORT, uint8 copy_u8state);
void DIO_vWritePort(uint8 Copy_u8PORT, uint8 Copy_u8value);
void DIO_vTogglePort(uint8 Copy_u8PORT);
uint8 DIO_u8GetPortValue(uint8 Copy_u8PORT);
// void DIO_vWritePortValue(uint8 Copy_u8PORT, uint8 Copy_u8value);

#endif