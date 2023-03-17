#ifndef SPI_INTERFACE_H
#define SPI_INTERFACE_H

#include "../../LIB/Datatypes.h"

#define DORD_LSB_FIRST 0
#define DORD_MSB_FIRST 1

#define CLK_LOW_IDLE 0
#define CLK_HIGH_IDLE 1

#define SAMPLE_ON_FIRST 0
#define SETUP_ON_FIRST 1

#define CLK_DIV_4 0
#define CLK_DIV_16 1
#define CLK_DIV_64 2
#define CLK_DIV_128 3

typedef struct SPI_Config
{
    bool enable_interrupt;
    bool enable_spi;
    bool is_master;
    bool double_speed;
    uint8 clk_polarity;
    uint8 clk_phase;
    uint8 clk_divisor;
    uint8 data_order;
} SPI_Config_t;

void SPI_Init(SPI_Config_t *conf);
uint8 SPI_Transieve_Sync(uint8 data);

bool SPI_Transmit_Async(uint8 data);
uint8 SPI_Receive_Async(void);
void SPI_Transmit_Buffer_Async(uint8 *buff, uint16 buff_size, void (*f_ptr)(void));

#endif