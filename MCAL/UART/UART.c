#include "UART_Interface.h"
#include "../../LIB/Calcbit.h"
#include "../../MCAL/DIO/DIO_REG.h"
#include "../../LIB/Queue/Queue.h"

uint8 char_bit_size;
uint8 UCSRC_temp;

static Queue_Circular_t data_to_be_transmitted_q = {0};
static Queue_Circular_t data_received_q = {0};

void UART_vInit(UART_Config_t conf)
{
    // The initialization process normally consists of setting the baud rate, setting frame format and enabling the
    // Transmitter or the Receiver depending on the usage.
    setbit(UART_DDRD, UART_DDRD_TXD);
    UART_calc_baud_rate_reg_value(conf.baud_rate, conf.enable_double_transmission_speed);

    if (conf.enable_double_transmission_speed == UART_ENABLE_DOUBLE_TRANSMISSION_SPEED)
        setbit(UCSRA, UCSRA_U2X);
    if (conf.enable_multiprocessor_mode == UART_ENABLE_MULTIPROCESSOR_COMMUNICATION_MODE)
        setbit(UCSRA, UCSRA_MPCM);

    if (conf.enable_recevie_complete_interrupt == UART_ENABLE_RECEIVE_COMPLETE_INTERRUPT)
    {
        setbit(UCSRB, UCSRB_RXCIE);
        setbit(SREG, SREG_GIE);
    }

    if (conf.enable_transmit_complete_interrupt == UART_ENABLE_TRANSMIT_COMPLETE_INTERRUPT)
    {
        setbit(UCSRB, UCSRB_TXCIE);
        setbit(SREG, SREG_GIE);
    }

    if (conf.enable_data_reg_empty_complete_interrupt == UART_ENABLE_DATA_REG_EMPTY_COMPLETE_INTERRUPT)
    {
        setbit(UCSRB, UCSRB_UDRIE);
        setbit(SREG, SREG_GIE);
    }
    if (conf.enable_receiver == UART_ENABLE_RECEIVER)
        setbit(UCSRB, UCSRB_RXEN);

    if (conf.enable_transmiter == UART_ENABLE_TRANSMITER)
        setbit(UCSRB, UCSRB_TXEN);

    UART_set_char_size(conf.frame_data_bits_size);
    UART_set_parity_mode(conf.parity_mode);
    UART_set_stop_bits_mode(conf.stop_bits_mode);
    setbit(UCSRC_temp, 7);
    UCSRC = UCSRC_temp;

    q_init(&data_to_be_transmitted_q); // not needed since it was initialized with zeros ,but meehh
    q_init(&data_received_q);          // not needed since it was initialized with zeros ,but meehh
}

void UART_calc_baud_rate_reg_value(uint16 baud_rate, uint8 enable_double_transmission_speed)
{
    volatile uint16 reg_value = 0;
    unsigned long br = baud_rate;
    if (enable_double_transmission_speed == UART_ENABLE_DOUBLE_TRANSMISSION_SPEED)
    {
        reg_value = (F_CPU / (8.0 * br)) - 1;
    }
    else
    {
        reg_value = (F_CPU / (16.0 * br)) - 1;
        // reg_value = 51; // delete later
    }
    // select UBRRH register
    clearbit(UBRRH, UBRRH_URSEL);
    UBRRH = (uint8)(reg_value >> 8);
    UBRRL = (uint8)(reg_value);
    setbit(UBRRH, UBRRH_URSEL); // back to UCSRC
}
void UART_set_stop_bits_mode(uint8 stop_bits_mode)
{
    if (stop_bits_mode == UART_1_BIT_STOP)
        clearbit(UCSRC_temp, UCSRC_USBS);
    else
        setbit(UCSRC_temp, UCSRC_USBS);
}

void UART_set_parity_mode(uint8 parity_mode)
{
    switch (parity_mode)
    {
    case UART_DISABLE_PARITY:
    {
        clearbit(UCSRC_temp, UCSRC_UPM0);
        clearbit(UCSRC_temp, UCSRC_UPM1);
        break;
    }

    case UART_EVEN_PARITY:
    {
        clearbit(UCSRC_temp, UCSRC_UPM0);
        setbit(UCSRC_temp, UCSRC_UPM1);
        break;
    }

    case UART_ODD_PARITY:
    {
        setbit(UCSRC_temp, UCSRC_UPM0);
        setbit(UCSRC_temp, UCSRC_UPM1);
        break;
    }

    default:
        break;
    }
}

void UART_set_char_size(uint8 frame_data_bits_size)
{
    switch (frame_data_bits_size)
    {
    case UART_5BIT_CHAR_SIZE:
    {
        clearbit(UCSRC_temp, UCSRC_UCSZ0);
        clearbit(UCSRC_temp, UCSRC_UCSZ1);
        clearbit(UCSRB, UCSRB_UCSZ2);
        char_bit_size = UART_5BIT_CHAR_SIZE;

        break;
    }
    case UART_6BIT_CHAR_SIZE:
    {
        setbit(UCSRC_temp, UCSRC_UCSZ0);
        clearbit(UCSRC_temp, UCSRC_UCSZ1);
        clearbit(UCSRB, UCSRB_UCSZ2);
        char_bit_size = UART_6BIT_CHAR_SIZE;

        break;
    }
    case UART_7BIT_CHAR_SIZE:
    {
        clearbit(UCSRC_temp, UCSRC_UCSZ0);
        setbit(UCSRC_temp, UCSRC_UCSZ1);
        clearbit(UCSRB, UCSRB_UCSZ2);
        char_bit_size = UART_7BIT_CHAR_SIZE;

        break;
    }
    case UART_8BIT_CHAR_SIZE:
    {
        setbit(UCSRC_temp, UCSRC_UCSZ0);
        setbit(UCSRC_temp, UCSRC_UCSZ1);
        clearbit(UCSRB, UCSRB_UCSZ2);
        char_bit_size = UART_8BIT_CHAR_SIZE;
        break;
    }
    case UART_9BIT_CHAR_SIZE:
    {
        setbit(UCSRC_temp, UCSRC_UCSZ0);
        setbit(UCSRC_temp, UCSRC_UCSZ1);
        setbit(UCSRB, UCSRB_UCSZ2);
        char_bit_size = UART_9BIT_CHAR_SIZE;
        break;
    }

    default:
        break;
    }
}

void UART_vTransmit_poll(uint16 data)
{
    while (getbit(UCSRA, UCSRA_UDRE) == 0)
        ; // wait

    if (char_bit_size == UART_9BIT_CHAR_SIZE)
    {
        UCSRB &= ~(1 << UCSRB_TXB8); // clear last data's 9th bit
        if (data & 0x0100)
        {
            UCSRB |= (1 << UCSRB_TXB8); // clear last data's 9th bit
        }
    }
    UDR = (uint8)data;

    // while (!(UCSRA & (1 << UCSRA_UDRE)))
    //     ;
    // /* Put data into buffer, sends the data */
    // UDR = data;
}
uint16 UART_u16Receive_poll()
{
    unsigned char status, resh, resl;
    /* Wait for data to be received */
    while (!(UCSRA & (1 << UCSRA_RXC)))
        ;
    if (char_bit_size == UART_9BIT_CHAR_SIZE)
    {
        /* Get status and 9th bit, then data */
        /* from buffer */
        status = UCSRA;
        resh = UCSRB;
        resl = UDR;
        /* If error, return -1 */
        if (status & ((1 << UCSRA_FE) | (1 << UCSRA_DOR) | (1 << UCSRA_PE)))
            return -1;
        /* Filter the 9th bit, then return */
        resh = (resh >> 1) & 0x01;
        return ((resh << 8) | resl);
    }
    else
        return UDR;

    // while (!(UCSRA & (1 << UCSRA_RXC)))
    //     ;
    // return UDR;
}

// void UART_Flush(void)
// {
//     volatile unsigned char dummy;
//     while (UCSRA & (1 << UCSRA_RXC))
//         dummy = UDR;
// }
void UART_vTransmitString(char *str)
{
    while (*str)
    {
        UART_vTransmit_poll(*str);
        str++;
    }
}

void UART_vTransmit_no_poll(uint16 data)
{
    // check if can be sent immediatly
    if (getbit(UCSRA, UCSRA_UDRE) == 1)
    {
        if (char_bit_size == UART_9BIT_CHAR_SIZE)
        {
            UCSRB &= ~(1 << UCSRB_TXB8); // clear last data's 9th bit
            if (data & 0x0100)
            {
                UCSRB |= (1 << UCSRB_TXB8); // clear last data's 9th bit
            }
        }
        UDR = (uint8)data;
    }
    else
        // add to buffer to bes sent later by ISR
        q_enqueue(&data_to_be_transmitted_q, data);
}
uint16 UART_u16Receive_no_poll()
{
    if (q_isEmpty(&data_received_q))
        return QUEUE_ERROR_EMPTY;
    else
        return q_dequeue(&data_received_q);
}
// void UART_vReceive_buffer_no_poll(char *buff, uint8 size, void (*f_ptr)(void))
// {
//     // if (q_isEmpty(&data_received_q))
//     //     return QUEUE_ERROR_EMPTY;
//     // else
//     //     return q_dequeue(&data_received_q);
// }

void __vector_15(void) __attribute__((signal, used)); // USART, Tx Complete
void __vector_15(void)
{
    if (q_isEmpty(&data_to_be_transmitted_q))
        return;
    else
    {
        uint16 data = q_dequeue(&data_to_be_transmitted_q);
        if (char_bit_size == UART_9BIT_CHAR_SIZE)
        {
            UCSRB &= ~(1 << UCSRB_TXB8); // clear last data's 9th bit
            if (data & 0x0100)
            {
                UCSRB |= (1 << UCSRB_TXB8); // clear last data's 9th bit
            }
        }
        UDR = (uint8)data;
    }
}

void __vector_14(void) __attribute__((signal, used)); // USART Data Register Empty
void __vector_14(void)
{
    if (q_isEmpty(&data_to_be_transmitted_q))
        return;
    else
    {
        uint16 data = q_dequeue(&data_to_be_transmitted_q);
        if (char_bit_size == UART_9BIT_CHAR_SIZE)
        {
            UCSRB &= ~(1 << UCSRB_TXB8); // clear last data's 9th bit
            if (data & 0x0100)
            {
                UCSRB |= (1 << UCSRB_TXB8); // clear last data's 9th bit
            }
        }
        UDR = (uint8)data;
    }
}

void __vector_13(void) __attribute__((signal, used)); // USART, Rx Complete
void __vector_13(void)
{

    // setbit((*(volatile uint8 *)(0x3a)), HIGH);
    // togglebit((*(volatile uint8 *)(0x3b)), PIN0);
    if (q_isFull(&data_received_q))
        return; // drop data
    else
    {
        unsigned char status, resh, resl;
        uint16 data;
        if (char_bit_size == UART_9BIT_CHAR_SIZE)
        {
            /* Get status and 9th bit, then data */
            /* from buffer */
            status = UCSRA;
            resh = UCSRB;
            resl = UDR;
            /* If error, return -1 */
            if (status & ((1 << UCSRA_FE) | (1 << UCSRA_DOR) | (1 << UCSRA_PE)))
                return; // data coruppted - drop recvd data
            /* Filter the 9th bit, then return */
            resh = (resh >> 1) & 0x01;
            data = ((resh << 8) | resl);
        }
        else
            data = UDR;
        q_enqueue(&data_received_q, data);
    }
}