#ifndef UART_REG_H
#define UART_REG_H

#include "../../LIB/Datatypes.h"

/*
USART I/O Data Register – UDR
*/
#define UDR (*((volatile uint8 *)(0x2C)))
#define UART_DDRD (*((volatile uint8 *)(0x31)))
#define UART_DDRD_TXD 1
#define UART_DDRD_RXD 0
/*
USART Control and
Status Register A – UCSRA
*/
#define UCSRA (*((volatile uint8 *)(0x2B)))
// Bit 7 – RXC: USART Receive Complete
#define UCSRA_RXC 7
// Bit 6 – TXC: USART Transmit Complete
#define UCSRA_TXC 6
// Bit 5 – UDRE: USART Data Register Empty
#define UCSRA_UDRE 5
#define UCSRA_FE 4
#define UCSRA_DOR 3
#define UCSRA_PE 2
// Bit 1 – U2X: Double the USART Transmission Speed
#define UCSRA_U2X 1
#define UCSRA_MPCM 0
/*
USART Control and
Status Register B – UCSRB
*/
#define UCSRB (*((volatile uint8 *)(0x2A)))

#define UCSRB_RXCIE 7
#define UCSRB_TXCIE 6
#define UCSRB_UDRIE 5
#define UCSRB_RXEN 4
#define UCSRB_TXEN 3
#define UCSRB_UCSZ2 2
#define UCSRB_RXB8 1
#define UCSRB_TXB8 0
/*
USART Control and
Status Register C – UCSRC
*/
#define SREG (*((volatile uint8 *)(0x5F)))
#define SREG_GIE 7

#define UCSRC (*((volatile uint8 *)(0x40)))

#define UCSRC_URSEL 7
#define UCSRC_UMSEL 6
#define UCSRC_UPM1 5
#define UCSRC_UPM0 4
#define UCSRC_USBS 3
#define UCSRC_UCSZ1 2
#define UCSRC_UCSZ0 1
#define UCSRC_UCPOL 0
/*
USART Baud Rate
Registers – UBRRL and UBRRHADC
*/
#define UBRRH (*((volatile uint8 *)(0x40))) // shared with UCSRC
#define UBRRH_URSEL 7

#define UBRRL (*((volatile uint8 *)(0x29)))

/*----------------------------------------------*/

#define UART_DISABLE_DOUBLE_TRANSMISSION_SPEED 0
#define UART_ENABLE_DOUBLE_TRANSMISSION_SPEED 1

#define UART_DISABLE_MULTIPROCESSOR_COMMUNICATION_MODE 0
#define UART_ENABLE_MULTIPROCESSOR_COMMUNICATION_MODE 1

#define UART_ENABLE_RECEIVE_COMPLETE_INTERRUPT 1
#define UART_DISABLE_RECEIVE_COMPLETE_INTERRUPT 0

#define UART_ENABLE_TRANSMIT_COMPLETE_INTERRUPT 1
#define UART_DISABLE_TRANSMIT_COMPLETE_INTERRUPT 0

#define UART_ENABLE_DATA_REG_EMPTY_COMPLETE_INTERRUPT 1
#define UART_DISABLE_DATA_REG_EMPTY_COMPLETE_INTERRUPT 0

#define UART_ENABLE_RECEIVER 1
#define UART_DISABLE_RECEIVER 0

#define UART_ENABLE_TRANSMITER 1
#define UART_DISABLE_TRANSMITER 0

#define UART_5BIT_CHAR_SIZE 5
#define UART_6BIT_CHAR_SIZE 6
#define UART_7BIT_CHAR_SIZE 7
#define UART_8BIT_CHAR_SIZE 8
#define UART_9BIT_CHAR_SIZE 9

#define UART_ASYNCHRONOUS_MODE 1
#define UART_SYNCHRONOUS_MODE 0

#define UART_DISABLE_PARITY 0
#define UART_EVEN_PARITY 1
#define UART_ODD_PARITY 2

#define UART_1_BIT_STOP 1
#define UART_2_BIT_STOP 2

#endif