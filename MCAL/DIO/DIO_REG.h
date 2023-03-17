#ifndef DIO_REG_H
#define DIO_REG_H

#include "../../LIB/Datatypes.h"

typedef struct
{
    uint8 Pin;
    uint8 DDR;
    uint8 Port;
} DIO_Regs;

#define PORTA_BASE (*(volatile DIO_Regs *)0x39)
#define PORTB_BASE (*(volatile DIO_Regs *)0x36)
#define PORTC_BASE (*(volatile DIO_Regs *)0x33)
#define PORTD_BASE (*(volatile DIO_Regs *)0x30)

#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7

#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3

#define INPUT 0
#define OUTPUT 1

#define LOW 0
#define HIGH 1

#define HIGH_PORT 0xFF
#define LOW_PORT 0x00

#endif