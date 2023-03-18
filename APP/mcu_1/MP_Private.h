#ifndef MP_PRIVATE_H
#define MP_PRIVATE_H

#include "../../MCAL/DIO/DIO_REG.h"

#define SYS_ENABLE_PORT PORTB
#define SYS_ENABLE_PIN PIN7

#define SYS_SHUTDOWN_PORT PORTC
#define SYS_SHUTDOWN_PIN PIN6

bool MP_vFingerPrint();
bool MP_vRFID();

#endif