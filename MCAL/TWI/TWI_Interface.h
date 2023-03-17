#ifndef TWI_INTERFACE_H
#define TWI_INTERFACE_H
#include "../../LIB/Datatypes.h"

#define TWI_MAX_SCL 400000UL
typedef struct TWI_Config
{
    /* data */
    uint32 scl_freq;     // shouldn't exceed twi_max_scl supported
    uint8 scl_prescaler; // shouldn't exceed twi_max_scl supported
    bool enable_ack;
    bool enable_twi;
    bool enable_interrupt;
    uint8 own_slave_address;
    bool enable_general_call;
} TWI_Config_t;

#define TWI_prescaler_1 0
#define TWI_prescaler_4 1
#define TWI_prescaler_16 2
#define TWI_prescaler_64 3

void TWI_Init(TWI_Config_t conf);

bool TWI_Master_Transmit_Byte(uint8 byte, uint8 slave_adrr);
bool TWI_Master_Transmit_Buffer(uint8 *buff, uint32 buff_size, uint8 slave_adrr);
uint8 TWI_Master_Receive_Byte(uint8 slave_adrr);

bool TWI_Slave_Transmit_Byte(uint8 byte);
uint8 TWI_Slave_Receive_Byte(void);
bool TWI_Slave_Receive_Buffer(char *buffer, uint32 buff_size);

#endif