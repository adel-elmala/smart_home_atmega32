#ifndef EXTERNAL_INT_REG_H
#define EXTERNAL_INT_REG_H

#include "../../LIB/Datatypes.h"

#define MCUCR (*(volatile uint8 *)(0x55))
#define MCUCSR (*(volatile uint8 *)(0x54))
#define GICR (*(volatile uint8 *)(0x5B))
#define GIFR (*(volatile uint8 *)(0x5A))

#define SREG (*(volatile uint8 *)(0x5F))

#endif