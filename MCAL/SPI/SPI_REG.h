#ifndef SPI_REG_H
#define SPI_REG_H

#include "../../LIB/Datatypes.h"
/*
SPI Control Register – SPCR
*/
#define SPCR (*((volatile uint8 *)(0x2D)))

#define SPIE 7
#define SPE 6
#define DORD 5
#define MSTR 4
#define CPOL 3
#define CPHA 2
#define SPR1 1
#define SPR0 0
/*
SPI Status Register – SPSR
*/
#define SPSR (*((volatile uint8 *)(0x2E)))

#define SPIF 7
#define WCOL 6
#define SPI2X 0
/*
SPI Data Register – SPDR
*/
#define SPDR (*((volatile uint8 *)(0x2F)))
#define SPI_PORT (*((volatile uint8 *)(0x38)))
#define SPI_DDR (*((volatile uint8 *)(0x37)))
#define SPI_SS 4
#define SPI_MOSI 5
#define SPI_MISO 6
#define SPI_SCK 7

#endif