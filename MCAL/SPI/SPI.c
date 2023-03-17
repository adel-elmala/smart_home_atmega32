#include "SPI_REG.h"
#include "SPI_Interface.h"
#include "../../LIB/Calcbit.h"
#include "../GIE/GIE_Interface.h"
#include "../../LIB/Queue/Queue.h"
#include "../DIO/DIO_Interface.h"
#include "../DIO/DIO_REG.h"

static Queue_Circular_t data_to_transmit_q = {0};
static Queue_Circular_t data_received_q = {0};
static bool g_is_master = false;
void (*trans_complete_callback)(void) = NULL;
void (*recv_complete_callback)(void) = NULL;

void SPI_Init(SPI_Config_t *conf)
{
    q_init(&data_to_transmit_q);
    q_init(&data_received_q);
    uint8 SPCR_copy = 0;

    if (conf->is_master)
    {
        /* Set MOSI , SS , and SCK output */
        setbit(SPI_DDR, SPI_MOSI);
        setbit(SPI_DDR, SPI_SCK);
        setbit(SPI_DDR, SPI_SS);
        setbit(SPI_PORT, SPI_SS); // initially high

        /* Set MISO as input */
        clearbit(SPI_DDR, SPI_MISO);
        /* set as master*/
        setbit(SPCR_copy, MSTR);
        g_is_master = true;
    }
    else
    {

        /* Set MOSI , SS , and SCK input */
        clearbit(SPI_DDR, SPI_MOSI);
        clearbit(SPI_DDR, SPI_SCK);
        clearbit(SPI_DDR, SPI_SS);

        /* Set MISO as output */
        setbit(SPI_DDR, SPI_MISO);
        g_is_master = false;
    }
    // /* Enable SPI, Master, set clock rate fck/16 */
    // SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
    if (conf->enable_interrupt)
    {
        sei();
        setbit(SPCR_copy, SPIE);
    }
    if (conf->enable_spi)
        setbit(SPCR_copy, SPE);
    if (conf->data_order == DORD_LSB_FIRST)
        setbit(SPCR_copy, DORD);
    // if (conf->is_master)
    //     setbit(SPCR_copy, MSTR);
    if (conf->clk_polarity == CLK_HIGH_IDLE)
        setbit(SPCR_copy, CPOL);
    if (conf->clk_phase == SETUP_ON_FIRST)
        setbit(SPCR_copy, CPHA);
    SPCR_copy |= (conf->clk_divisor & 0x03);
    if (conf->double_speed)
        setbit(SPSR, SPI2X);

    SPCR = SPCR_copy;
}

uint8 SPI_Transieve_Sync(uint8 data)
{
    uint8 flush;

    // SPI_PORT &= ~(1 << SPI_SS);
    if (g_is_master)
        clearbit(SPI_PORT, SPI_SS);

    SPDR = data;
    // while (!(SPSR & (1 << SPIF)))
    while (getbit(SPSR, SPIF) == 0)
        ; // wait till transmission completes

    if (g_is_master)
        setbit(SPI_PORT, SPI_SS);

    flush = SPDR;
    return flush;
}

bool SPI_Transmit_Async(uint8 data)
{
    if (q_isFull(&data_to_transmit_q))
        return false; // can't sent or recevied data
    else
    {

        // try to transmit now
        // if (getbit(SPSR, SPIF) == 1)
        if (q_isEmpty(&data_to_transmit_q))
        {
            // if (g_is_master)
            //     clearbit(SPI_PORT, SPI_SS);

            q_enqueue(&data_to_transmit_q, data);
            SPDR = 0xff; // dummy value to trigger SPIF flag

            if (g_is_master)
                setbit(SPI_PORT, SPI_SS); // this gets the slave to ignore the dummy send
        }
        else
            q_enqueue(&data_to_transmit_q, data);
        return true;
    }
}

uint8 SPI_Receive_Async(void)
{
    if (q_isEmpty(&data_received_q))
        return QUEUE_ERROR_EMPTY;
    else
        return q_dequeue(&data_received_q);
}
void SPI_Transmit_Buffer_Async(uint8 *buff, uint16 buff_size, void (*f_ptr)(void))
{
    for (uint16 i = 0; i < buff_size; ++i)
    {
        SPI_Transmit_Async(buff[i]);
    }
    trans_complete_callback = f_ptr;
}
// void SPI_Receive_Buffer_Async(uint8 *buff, uint16 buff_size, void (*f_ptr)(void))
// {
//     for (uint16 i = 0; i < buff_size; ++i)
//     {
//         SPI_Transmit_Async(buff[i]);
//     }
//     recv_complete_callback = f_ptr;
// }
void __vector_12(void) __attribute__((signal, used)); // SPI, Serial Transfer Complete
void __vector_12(void)
{
    // DIO_vSetPinDirection(PORTC, PIN7, OUTPUT);
    // // DIO_vWritePin(PORTC, PIN7, HIGH);
    // DIO_vTogglePin(PORTC, PIN7);
    q_enqueue(&data_received_q, SPDR); // buffer recieved data
    if (q_isEmpty(&data_to_transmit_q))
    {
        if (trans_complete_callback)
            (*trans_complete_callback)();
        return;
    }
    else
    {
        // q_enqueue(&data_received_q, SPDR); // buffer recieved data
        if (g_is_master)
            clearbit(SPI_PORT, SPI_SS);

        SPDR = q_dequeue(&data_to_transmit_q);

        // if (g_is_master)
        //     setbit(SPI_PORT, SPI_SS);
    }
}
