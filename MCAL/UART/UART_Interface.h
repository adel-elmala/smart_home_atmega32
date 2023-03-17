#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

#include "UART_REG.h"
typedef struct UART_Config
{
    uint16 baud_rate;
    uint8 enable_double_transmission_speed;
    uint8 enable_multiprocessor_mode;
    uint8 enable_recevie_complete_interrupt;
    uint8 enable_transmit_complete_interrupt;
    uint8 enable_data_reg_empty_complete_interrupt;
    uint8 enable_receiver;
    uint8 enable_transmiter;
    uint8 frame_data_bits_size;
    uint8 parity_mode;
    uint8 stop_bits_mode;

} UART_Config_t;

void UART_set_parity_mode(uint8 parity_mode);
void UART_set_char_size(uint8 frame_data_bits_size);
void UART_set_stop_bits_mode(uint8 stop_bits_mode);
void UART_calc_baud_rate_reg_value(uint16 baud_rate, uint8 enable_double_transmission_speed);

void UART_vInit(UART_Config_t conf);
void UART_vTransmit_poll(uint16);
uint16 UART_u16Receive_poll();

void UART_vTransmit_no_poll(uint16);
uint16 UART_u16Receive_no_poll();

// void UART_vReceive_buffer_no_poll(char *buff, uint8 size,void(*f_pt)(void));

#endif