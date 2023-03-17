#include "OLED_Interface.h"
#include "OLED_Private.h"

#include "../../MCAL/TWI/TWI_Interface.h"

TWI_Config_t oled_twi_conf =
    {
        TWI_MAX_SCL,     // uint32 scl_freq; // shouldn't exceed twi_max_scl supported
        TWI_prescaler_1, // uint8 scl_prescaler; // shouldn't exceed twi_max_scl supported
        true,            // bool enable_ack;
        true,            // bool enable_twi;
        false,           // bool enable_interrupt;
        0x10,            // uint8 own_slave_address;
        false            // bool enable_general_call;
};

uint8 OLED_Init()
{
    TWI_Init(oled_twi_conf);
    return 0;
}
uint8 OLED_Send_Command(uint8 command)
{
    // uint8 oled_slave_address = 0b0111100;
    uint8 oled_slave_address = 0b01111000;
    // uint8 buffer[] = {0xa5}; // display on
    // uint8 buffer[] = {0xa8, 0x3f,
    //   0xd3, 0x00,
    //   0x40,
    //   0xa0,
    //   0xc0,
    //   0xda, 0x02,
    //   0x81, 0x7f,
    //   0xa4,
    //   0xa6,
    //   0xd5, 0x80,
    //   0x8d, 0x14,
    //   0xaf}; // display on
    uint8 buffer[] = {0xae, 0xd5, 0x80, 0xa8, 0x3f, 0xd3, 0x00, 0x40, 0x8d, 0x14, 0x20, 0x00, 0xa1, 0xc8, 0xda, 0x12, 0x81, 0x7f, 0xd9, 0xf1, 0xdb, 0x40, 0xa4, 0xa6, 0xaf}; // display on

    // 0 1 1 1 1 0 SA0 R/W#
    TWI_Master_Transmit_Buffer(buffer, 25, oled_slave_address);
    // TWI_Master_Transmit_Byte(0xa5, oled_slave_address);
    return 0;
}
uint8 OLED_Send_Data(uint8 command);
