#ifndef TIMER_REGS_H
#define TIMER_REGS_H

// #define F_CPU 16000000UL
// #define F_CPU 8000000UL
#define TIMER0_MAX_COUNT (256)

#define TIMER0_TICK_TIME_NO_PRESCALE (1.0 / (double)F_CPU)
#define TIMER0_TICK_TIME_8_PRESCALE (8.0 / (double)F_CPU)
#define TIMER0_TICK_TIME_64_PRESCALE (64.0 / (double)F_CPU)
#define TIMER0_TICK_TIME_256_PRESCALE (256.0 / (double)F_CPU)
#define TIMER0_TICK_TIME_1024_PRESCALE (1024.0 / (double)F_CPU)

#define TIMER0_TIME_TO_OVERFLOW_NO_PRESCALE ((TIMER0_TICK_TIME_NO_PRESCALE) * (TIMER0_MAX_COUNT))
#define TIMER0_TIME_TO_OVERFLOW_8_PRESCALE ((TIMER0_TICK_TIME_8_PRESCALE) * (TIMER0_MAX_COUNT))
#define TIMER0_TIME_TO_OVERFLOW_64_PRESCALE ((TIMER0_TICK_TIME_64_PRESCALE) * (TIMER0_MAX_COUNT))
#define TIMER0_TIME_TO_OVERFLOW_256_PRESCALE ((TIMER0_TICK_TIME_256_PRESCALE) * (TIMER0_MAX_COUNT))
#define TIMER0_TIME_TO_OVERFLOW_1024_PRESCALE ((TIMER0_TICK_TIME_1024_PRESCALE) * (TIMER0_MAX_COUNT))

/*
    Timer/Counter
    Register – TCNT0
*/
#define TCNT0 (*(volatile uint8 *)(0x52))
/*
    Output Compare
    Register – OCR0
*/
#define OCR0 (*(volatile uint8 *)(0x5C))

#define TIMER0_NORMAL_MODE 0
#define TIMER0_CTC_MODE 1

#define TIMER0_INTR_ENABLE 0
#define TIMER0_INTR_DISABLE 1

// Prescale Macros
#define PRESCALER_CLEAR 0b11111000
#define PRESCALER_1 1
#define PRESCALER_8 8
#define PRESCALER_64 64
#define PRESCALER_256 256
#define PRESCALER_1024 1024
#define EXT_CLK_FAILING_EGDE 2
#define EXT_CLK_RISING_EGDE 3
/*
    Timer/Counter Control
    Register – TCCR0
*/
#define TCCR0 (*(volatile uint8 *)(0x53))

// Bit 7 – FOC0: Force Output Compare
#define TCCR0_FOC0 7

// Bit 6, 3 – WGM01:0: Waveform Generation Mode
#define TCCR0_WGM00 6
#define TCCR0_WGM01 3

// Bit 5:4 – COM01:0: Compare Match Output Mode
#define TCCR0_COM01 5
#define TCCR0_COM00 4

// Bit 2:0 – CS02:0: Clock Select
#define TCCR0_CS02 2
#define TCCR0_CS01 1
#define TCCR0_CS00 0
/*
    Timer/Counter
    Interrupt Mask Register – TIMSK
*/
#define TIMSK (*(volatile uint8 *)(0x59))

// Bit 0 – TOIE0: Timer/Counter0 Overflow Interrupt Enable
#define TIMSK_TOIE0 0
// Bit 1 – OCIE0: Timer/Counter0 Output Compare Match Interrupt Enable
#define TIMSK_OCIE0 1

/*
    Timer/Counter
    Interrupt Flag Register – TIFR
*/
#define TIFR (*(volatile uint8 *)(0x58))
// Bit 0 – TOV0: Timer/Counter0 Overflow Flag
#define TIRF_TOV0 0
// Bit 1 – OCF0: Output Compare Flag 0
#define TIRF_OCF0 1

#endif