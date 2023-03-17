#ifndef PWM_REGS_H
#define PWM_REGS_H

#include "../../LIB/Datatypes.h"

/*
Timer/Counter1
Control Register A – TCCR1A
*/

#define TCCR1A (*(volatile uint8 *)(0x4F))

// Bit 7:6 – COM1A1:0: Compare Output Mode for Compare unit A
#define TCCR1A_COM1A1 7
#define TCCR1A_COM1A0 6

// Bit 5:4 – COM1B1:0: Compare Output Mode for Compare unit B
#define TCCR1A_COM1B1 5
#define TCCR1A_COM1B0 4
// Bit 3 – FOC1A: Force Output Compare for Compare unit A
#define TCCR1A_FOC1A 3
// Bit 2 – FOC1B: Force Output Compare for Compare unit B
#define TCCR1A_FOC1B 2
// Bit 1:0 – WGM11:0: Waveform Generation Mode
#define TCCR1A_WGM11 1
#define TCCR1A_WGM10 0

/*
Timer/Counter1
Control Register B –  TCCR1B

ICNC1 ICES1 – WGM13 WGM12 CS12 CS11 CS10
*/

#define TCCR1B (*(volatile uint8 *)(0x4E))

// Bit 7 – ICNC1: Input Capture Noise Canceler
#define TCCR1B_ICNC1 7
// Bit 6 – ICES1: Input Capture Edge Select
#define TCCR1B_ICES1 6
// Bit 5 – Reserved Bit
#define TCCR1B_PRESERVED 5
// Bit 4:3 – WGM13:2: Waveform Generation Mode
#define TCCR1B_WGM13 4
#define TCCR1B_WGM12 3
// Bit 2:0 – CS12:0: Clock Select
#define TCCR1B_CS12 2
#define TCCR1B_CS11 1
#define TCCR1B_CS10 0

/*
Timer/Counter1 – TCNT1H and TCNT1L
*/

#define TCNT1H (*(volatile uint8 *)(0x4D))
#define TCNT1L (*(volatile uint8 *)(0x4C))

/*
Output Compare Register 1 A – OCR1AH and OCR1AL
*/
#define OCR1AH (*(volatile uint8 *)(0x4B))
#define OCR1AL (*(volatile uint8 *)(0x4A))

/*
Output Compare Register 1 B – OCR1BH and OCR1BL
*/
#define OCR1BH (*(volatile uint8 *)(0x49))
#define OCR1BL (*(volatile uint8 *)(0x48))

/*

Input Capture Register 1 – ICR1H and ICR1L

*/
#define ICR1H (*(volatile uint8 *)(0x47))
#define ICR1L (*(volatile uint8 *)(0x46))

/*
Timer/Counter
Interrupt Mask Register – TIMSK
*/
#define TIMSK (*(volatile uint8 *)(0x59))

#define TIMSK_OCIE2 7
#define TIMSK_TOIE2 6
// Bit 5 – TICIE1: Timer/Counter1, Input Capture Interrupt Enable
#define TIMSK_TICIE1 5
// Bit 4 – OCIE1A: Timer/Counter1, Output Compare A Match Interrupt Enable
#define TIMSK_OCIE1A 4
// Bit 3 – OCIE1B: Timer/Counter1, Output Compare B Match Interrupt Enable
#define TIMSK_OCIE1B 3
// Bit 2 – TOIE1: Timer/Counter1, Overflow Interrupt Enable
#define TIMSK_TOIE1 2
#define TIMSK_OCIE0 1
#define TIMSK_TOIE0 0

/*
Timer/Counter
Interrupt Flag Register – TIFR
*/
#define TIFR (*(volatile uint8 *)(0x58))

#define TIFR_OCF2 7
#define TIFR_TOV2 6
// Bit 5 – ICF1: Timer/Counter1, Input Capture Flag
#define TIFR_ICF1 5
// Bit 4 – OCF1A: Timer/Counter1, Output Compare A Match Flag
#define TIFR_OCF1A 4
// Bit 3 – OCF1B: Timer/Counter1, Output Compare B Match Flag
#define TIFR_OCF1B 3
// Bit 2 – TOV1: Timer/Counter1, Overflow Flag
#define TIFR_TOV1 2
#define TIFR_OCF0 1
#define TIFR_TOV0 0

#define OC1A_DDRD (*(volatile uint8 *)(0x31))
#define OC1B_DDRD (*(volatile uint8 *)(0x31))

#define OC1A_PORTD (*(volatile uint8 *)(0x32))
#define OC1B_PORTD (*(volatile uint8 *)(0x32))

#define OC1A 5
#define OC1B 4

#define OUTPUT 1

#define LOW 0
#define HIGH 1

#define PRESCALER_1 1
#define PRESCALER_8 8
#define PRESCALER_64 64
#define PRESCALER_256 256
#define PRESCALER_1024 1024
#endif