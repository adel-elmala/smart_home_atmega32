/*
 * SPI.h
 *
 *  Created on: Mar 4, 2023
 *      Author: dell
 */

#ifndef MCAL_SPI_SPI_H_
#define MCAL_SPI_SPI_H_

#include "../../LIB/Calcbit.h"
#include "SPI_REG.h"

void SPI_Init(void);
uint8 SPI_DATA_RW(uint8 Copy_u8data);
void SPI_String_W(uint8 *str);

#define SPI_INT_ENABLE 0
#define SPI_INT_DIS 0
#define SPI_INT_EN 1

#define SPI_DOUBLE_SPEED_MODE 0
#define DOUBLE_SPEED_MODE_DIS 0
#define DOUBLE_SPEED_MODE_EN 1

#define SPI_ENABLE 1
#define SPI_DIS 0
#define SPI_EN 1

#define DATA_ORDER 0
#define MSB 0
#define LSB 1

#define IS_MSTR 1
#define SLAVE 0
#define MASTER 1

#define CLK_POLARITY 0
#define RISING_LEADING 0
#define FALLING_LEADING 1

#define CLK_PHASE 0
#define SAMPLE_LEADING 0
#define SETUP_LEADING 1

#endif /* MCAL_SPI_SPI_H_ */
