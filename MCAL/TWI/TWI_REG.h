#ifndef TWI_REG_H
#define TWI_REG_H

#include "../../LIB/Datatypes.h"

/* TWI Bit Rate Register – TWBR */
#define TWBR (*((volatile uint8 *)(0x20)))
// #define TWBR7 7
// #define TWBR6 6
// #define TWBR5 5
// #define TWBR4 4
// #define TWBR3 3
// #define TWBR2 2
// #define TWBR1 1
// #define TWBR0 0
/* TWI Control Register – TWCR */
#define TWCR (*((volatile uint8 *)(0x56)))
#define TWINT 7
#define TWEA 6
#define TWSTA 5
#define TWSTO 4
#define TWWC 3
#define TWEN 2
#define TWCR_RESERVED 1
#define TWIE 0
/* TWI Status Register – TWSR */
#define TWSR (*((volatile uint8 *)(0x21)))
#define TWS7 7
#define TWS6 6
#define TWS5 5
#define TWS4 4
#define TWS3 3
#define TWSR_RESERVED 4
#define TWPS1 1
#define TWPS0 0

/* TWI Data Register – TWDR */
#define TWDR (*((volatile uint8 *)(0x23)))

/* TWI (Slave) Address Register – TWAR */
#define TWAR (*((volatile uint8 *)(0x22)))
#define TWGCE 0

#endif