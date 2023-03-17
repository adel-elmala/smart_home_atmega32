#include "TWI_REG.h"
#include "TWI_Interface.h"
#include "TWI_Private.h"
#include "../../LIB/Calcbit.h"
#include "../GIE/GIE_Interface.h"
#include "../HAL/LCD/LCD_Interface.h"
#include "../TIMER/timer.h"
#include <math.h>

// typedef struct TWI_Config
// {
//     /* data */
//     uint32 scl_freq;     // shouldn't exceed twi_max_scl supported
//     uint8 scl_prescaler; // shouldn't exceed twi_max_scl supported
//     bool enable_ack;
//     bool enable_twi;
//     bool enable_interrupt;
//     uint8 own_slave_address;
//     bool enable_general_call;
// } TWI_Config_t;

void TWI_Init(TWI_Config_t conf)
{
    /* set prescaler */
    TWSR |= (conf.scl_prescaler) & 0x03;
    //  set frequency
    uint32 scl = (conf.scl_freq > TWI_MAX_SCL) ? TWI_MAX_SCL : conf.scl_freq;
    TWBR = ((F_CPU / scl) - 16) / (2 * pow(4, conf.scl_prescaler));

    // enable twi module
    if (conf.enable_twi)
        setbit(TWCR, TWEN);

    // enable ACK-ing
    if (conf.enable_ack) // check if this bit shouldn't be set at the init.
        setbit(TWCR, TWEA);

    // enable interrupts
    if (conf.enable_interrupt)
    {
        sei();
        setbit(TWCR, TWIE);
    }

    uint8 addr = (conf.own_slave_address);
    if (conf.enable_general_call)
        addr += 1;
    TWAR = addr;

    // // enable twi module
    // TWCR = (1 << TWEN);
}

// bool TWI_Master_Transmit_Byte(uint8 byte, uint8 slave_adrr)
// {
//     {
//         TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
//         while (!(TWCR & (1 << TWINT)))
//             ;
//         if ((TWSR & 0xF8) != START)
//             return MT_START_ERROR;
//     }

//     {
//         TWDR = (slave_adrr);
//         TWCR = (1 << TWINT) | (1 << TWEN);
//         while (!(TWCR & (1 << TWINT)))
//             ;
//         if ((TWSR & 0xF8) != MT_SLA_ACK)
//             return MT_SLA_ERROR;
//     }
//     {
//         TWDR = byte;
//         TWCR = (1 << TWINT) | (1 << TWEN);
//         while (!(TWCR & (1 << TWINT)))
//             ;

//         if ((TWSR & 0xF8) != MT_DATA_ACK)
//             return MT_DATA_ERROR;
//     }
//     {
//         TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
//     }
//     return TWI_SUCESS;
// }

uint8 TWI_GetStatus(void)
{
    return (TWSR & 0xF8);
}
void TWI_Wait_TWINT()
{
    while (getbit(TWCR, TWINT) == 0)
        ;
}
uint8 TWI_Start()
{
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    // while (!(TWCR & (1 << TWINT)))

    TWI_Wait_TWINT();

    if (TWI_GetStatus() != START)
        return MT_START_ERROR;
    return TWI_SUCESS;
}

uint8 TWI_SlaveAddr(uint8 slave_adrr, uint8 read_write)
{
    // TWDR = (slave_adrr << 1) + read_write;
    TWDR = (slave_adrr) | read_write;
    TWCR = (1 << TWINT) | (1 << TWEN);
    // while (!(TWCR & (1 << TWINT)))
    TWI_Wait_TWINT();
    // uint8 status = TWI_GetStatus();
    // if (read_write == TWI_WRITE)
    // {
    //     // if ((status != MT_SLA_ACK) || (status != MT_SLA_NACK))
    //     if ((status != MT_SLA_ACK))
    //         return MT_SLA_ERROR;
    // }
    // else
    // {
    //     // if ((status != MR_SLA_ACK) || (status != MR_SLA_NACK))
    //     if ((status != MR_SLA_ACK))
    //         return MR_SLA_ERROR;
    // }
    return TWI_SUCESS;
}
uint8 TWI_Send_data(uint8 byte)
{
    TWI_Wait_TWINT();

    /* send data */
    TWDR = byte;
    // setbit(TWCR, TWINT); // clear flag
    TWCR = (1 << TWEN) | (1 << TWINT);
    /* wait for data  to be sent*/
    TWI_Wait_TWINT();
    /*Check value of TWI Status Register*/
    uint8 status = TWI_GetStatus();
    // if ((status != MT_DATA_ACK) || (status != MT_DATA_NACK))
    // if ((status != MT_DATA_ACK))
    //     return MT_DATA_ERROR;
    return TWI_SUCESS;
}
void TWI_stop()
{
    /* send stop cond */
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}
bool TWI_Master_Transmit_Byte(uint8 byte, uint8 slave_adrr)
{
    if (TWI_Start() != TWI_SUCESS)
        return false;

    lcd_clearAndHome();
    lcd_displayString("Start sent");
    TIMER0_Delay_ms_with_Blocking(3000);

    if (TWI_SlaveAddr(slave_adrr, TWI_WRITE) != TWI_SUCESS)
    {
        TWI_stop();
        return false;
    }

    lcd_clearAndHome();
    lcd_displayString("SLA_W sent");
    TIMER0_Delay_ms_with_Blocking(3000);

    if (TWI_Send_data(byte) != TWI_SUCESS)
    {
        TWI_stop();
        return false;
    }

    lcd_clearAndHome();
    lcd_displayString("Data sent");
    TIMER0_Delay_ms_with_Blocking(3000);

    TWI_stop();

    lcd_clearAndHome();
    lcd_displayString("Stop sent");
    TIMER0_Delay_ms_with_Blocking(3000);

    return true;
}

bool TWI_Master_Transmit_Buffer(uint8 *buff, uint32 buff_size, uint8 slave_adrr)
{
    if (TWI_Start() != TWI_SUCESS)
    {
        lcd_displayString("start failed");
        return false;
    }

    if (TWI_SlaveAddr(slave_adrr, TWI_WRITE) != TWI_SUCESS)
    {
        lcd_displayString("addres failed");

        TWI_stop();
        return false;
    }
    for (int i = 0; i < buff_size; ++i)
    {
        if (TWI_Send_data(buff[i]) != TWI_SUCESS)
        {
            TWI_stop();
            lcd_displayString("data failed");
            return false;
        }
    }

    TWI_stop();

    return true;
}

uint8 TWI_Master_Receive_Byte(uint8 slave_adrr)
{
    uint8 byte;
    if (TWI_Start() == MT_START_ERROR)
        return false;

    lcd_clearAndHome();
    lcd_displayString("start sent");
    TIMER0_Delay_ms_with_Blocking(1000);

    TWI_SlaveAddr(slave_adrr, TWI_READ);

    lcd_clearAndHome();
    lcd_displayString("SLA_R sent");
    TIMER0_Delay_ms_with_Blocking(1000);

    /* wait for data  to be recieved*/
    TWI_GetStatus();

    /* rec data */
    TWCR = (1 << TWINT) | (1 << TWEN); // send nack

    /* wait for nack  to be recieved*/
    TWI_Wait_TWINT();
    byte = TWDR;

    lcd_clearAndHome();
    lcd_displayString("Data Recieved");
    TIMER0_Delay_ms_with_Blocking(1000);

    /*Check value of TWI Status Register*/
    // if (TWI_GetStatus() != MR_DATA_NACK)
    //     return MR_DATA_ERROR;

    /* send stop cond */
    TWI_stop();
    // setbit(TWCR, TWSTO);

    lcd_clearAndHome();
    lcd_displayString("Stop sent");
    TIMER0_Delay_ms_with_Blocking(1000);

    return byte;
}

uint8 TWI_Slave_Receive_Byte(void)
{
    lcd_clearAndHome();
    lcd_displayString("Slave Listen");
    TIMER0_Delay_ms_with_Blocking(3000);

    // listen to be addressed
    TWCR = (1 << TWEN);
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    TWI_Wait_TWINT();

    lcd_clearAndHome();
    lcd_displayString("Slave Addressed");
    TIMER0_Delay_ms_with_Blocking(3000);
    // uint8 status = TWI_GetStatus();                             /* Read TWI status register */
    // if ((status != SR_SLA_ACK) || (status != SR_GCALL_SLA_ACK)) /* Own SLA+W received &ack returned */
    //     return SR_SLA_ERROR;

    // wait for data to arrive
    // TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    TWCR = (1 << TWINT) | (1 << TWEN);
    TWI_Wait_TWINT();

    lcd_clearAndHome();
    lcd_displayString("data recieved");
    TIMER0_Delay_ms_with_Blocking(3000);
    // Wait until TWI finish its current job
    // status = TWI_GetStatus();                                   /* Read TWI status register */
    // if (status == SR_DATA_NACK || status == SR_GCALL_DATA_NACK) /* Check for data received &nack returned */
    return TWDR; /* If yes then return received data */
}
bool TWI_Slave_Receive_Buffer(char *buffer, uint32 buff_size)
{
    // listen to be addressed
    TWCR = (1 << TWEN);
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    TWI_Wait_TWINT();

    // uint8 status = TWI_GetStatus();                             /* Read TWI status register */
    // if ((status != SR_SLA_ACK) || (status != SR_GCALL_SLA_ACK)) /* Own SLA+W received &ack returned */
    //     return SR_SLA_ERROR;

    // Wait until TWI finish its current job
    // status = TWI_GetStatus();                                   /* Read TWI status register */
    // if (status == SR_DATA_NACK || status == SR_GCALL_DATA_NACK) /* Check for data received &ack returned */
    //     return TWDR;

    for (uint32 i = 0; i < buff_size; ++i)
    {
        // wait for data to arrive
        TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
        TWI_Wait_TWINT(); /* Wait until TWI finish its current job */

        // status = TWI_GetStatus();                                 /* Read TWI status register */
        // if (status == SR_DATA_ACK || status == SR_GCALL_DATA_ACK) /* Check for data received &ack returned */
        buffer[i] = TWDR;
    }
    return true;
}

bool TWI_Slave_Transmit_Byte(uint8 byte)
{
    // listen to be addressed
    TWCR = (1 << TWEN);
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    TWI_Wait_TWINT();

    lcd_clearAndHome();
    lcd_displayString("Slave addressed");
    TIMER0_Delay_ms_with_Blocking(1000);

    // uint8 status = TWI_GetStatus();                             /* Read TWI status register */
    // if ((status != SR_SLA_ACK) || (status != SR_GCALL_SLA_ACK)) /* Own SLA+W received &ack returned */
    //     return SR_SLA_ERROR;

    TWDR = byte;
    // wait for data to arrive
    // TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    TWCR = (1 << TWINT) | (1 << TWEN);
    TWI_Wait_TWINT();

    lcd_clearAndHome();
    lcd_displayString("Slave sent byte");
    TIMER0_Delay_ms_with_Blocking(1000);

    // Wait until TWI finish its current job
    // status = TWI_GetStatus();                                   /* Read TWI status register */
    // if (status == SR_DATA_NACK || status == SR_GCALL_DATA_NACK) /* Check for data received &nack returned */
    return true; /* If yes then return received data */
}
