#ifndef STOPWATCH_REG_H
#define STOPWATCH_REG_H
#include "../../LIB/Datatypes.h"

/* ------- REGESTIER ADDRESSES ------- */
/* Timer/Counter Control Register – TCCR2 */
#define TCCR2 (*((volatile uint8 *)(0x45)))

/* Timer/Counter Register – TCNT2 */
#define TCNT2 (*((volatile uint8 *)(0x44)))

/* Output Compare Register – OCR2 */
#define OCR2 (*((volatile uint8 *)(0x43)))

/* Asynchronous Status Register – ASSR */
#define ASSR (*((volatile uint8 *)(0x42)))

/* Timer/Counter Interrupt Mask Register – TIMSK */
#define TIMSK (*((volatile uint8 *)(0x59)))

/* Timer/Counter Interrupt Flag Register – TIFR */
#define TIFR (*((volatile uint8 *)(0x58)))

/* Special Function IO Register – SFIOR */
#define SFIOR (*((volatile uint8 *)(0x50)))

/* ------- PIN NAMES ------- */
#define TCCR2_FOC2 7
#define TCCR2_WGM20 6
#define TCCR2_COM21 5
#define TCCR2_COM20 4
#define TCCR2_WGM21 3
#define TCCR2_CS22 2
#define TCCR2_CS21 1
#define TCCR2_CS20 0

#define ASSR_AS2 3
#define ASSR_TCN2UB 2
#define ASSR_OCR2UB 1
#define ASSR_TCR2UB 0

#define TIMSK_OCIE2 7
#define TIMSK_TOIE2 6

#define TIFR_OCF2 7
#define TIFR_TOV2 6

#define SFIOR_PSR2 1
#endif