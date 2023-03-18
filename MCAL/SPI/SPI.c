/*
 * SPI.c
 *
 *  Created on: Mar 4, 2023
 *      Author: dell
 */
#include "SPI.h"

void SPI_Init()
{
	switch(SPI_DOUBLE_SPEED_MODE)
	{
		case DOUBLE_SPEED_MODE_DIS:clearbit(SPSR,SPI2X); break;
		case DOUBLE_SPEED_MODE_EN: setbit(SPSR,SPI2X);   break;
	}
	switch(DATA_ORDER)
	{
		case MSB:clearbit(SPCR,DORD); break;
		case LSB: setbit(SPCR,DORD);  break;
	}
	switch(CLK_POLARITY)
	{
		case RISING_LEADING:clearbit(SPCR,CPOL); break;
		case FALLING_LEADING: setbit(SPCR,CPOL); break;
	}
	switch(CLK_PHASE)
	{
		case SAMPLE_LEADING: clearbit(SPCR,CPHA); break;
		case SETUP_LEADING: setbit(SPCR,CPHA);	  break;
	}
	switch(SPI_INT_ENABLE)
	{
		case SPI_INT_DIS:clearbit(SPCR,SPIE); break;
		case SPI_INT_EN: setbit(SPCR,SPIE);   break;
	}
	switch(SPI_ENABLE)
	{
		case SPI_DIS:clearbit(SPCR,SPE);  break;
		case SPI_EN: setbit(SPCR,SPE);    break;
	}
	switch(IS_MSTR)
		{
			case SLAVE:	clearbit(DDRB_R,MOSI); clearbit(DDRB_R,SCK); clearbit(DDRB_R,SS); setbit(DDRB_R,MISO); clearbit(SPCR,MSTR); break;
			case MASTER:setbit(DDRB_R,MOSI); setbit(DDRB_R,SCK); setbit(DDRB_R,SS); clearbit(DDRB_R,MISO); setbit(PORTB_R,SS); setbit(SPCR,MSTR);  break;
		}
	setbit(SPCR,SPR0);
	clearbit(SPCR,SPR1);
}
uint8 SPI_DATA_RW(uint8 Copy_u8data)
{
	SPDR = Copy_u8data;
	while (!getbit(SPSR,SPIF));
	return SPDR;
}
