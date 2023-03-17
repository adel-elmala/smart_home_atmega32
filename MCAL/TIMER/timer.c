#include "timer.h"
#include "timer_regs.h"
#include "../../LIB/Calcbit.h"

// static Timer_Config Config = {TIMER0_NORMAL_MODE, TIMER0_INTR_DISABLE};
static Timer_Config Config = {TIMER0_CTC_MODE, TIMER0_INTR_DISABLE};

void TIMER0_SetConfig()
{
    // setup TCCR0
    // setup TIMSK
    switch (Config.Mode)
    {
    case TIMER0_NORMAL_MODE:
    {
        // set control reg to select
        clearbit(TCCR0, TCCR0_WGM00);
        clearbit(TCCR0, TCCR0_WGM01);
        if (Config.Enable_Interrupt == TIMER0_INTR_ENABLE)
            // enable interrupt
            setbit(TIMSK, TIMSK_TOIE0);

        break;
    }
    case TIMER0_CTC_MODE:
    {
        // set control reg to select

        clearbit(TCCR0, TCCR0_WGM00);
        setbit(TCCR0, TCCR0_WGM01);
        if (Config.Enable_Interrupt == TIMER0_INTR_ENABLE)
            // enable interrupt
            setbit(TIMSK, TIMSK_OCIE0);

        break;
    }
    default:
        break;
    }
}

void stopTimer0()
{
    set_Timer0_Prescaler(PRESCALER_CLEAR);
}
inline void set_Timer0_Prescaler(uint16 prescaler)
{
    switch (prescaler)
    {

    case PRESCALER_CLEAR:
    {
        clearbit(TCCR0, TCCR0_CS00);
        clearbit(TCCR0, TCCR0_CS01);
        clearbit(TCCR0, TCCR0_CS02);
        break;
    }

    case PRESCALER_1:
    {
        setbit(TCCR0, TCCR0_CS00);
        clearbit(TCCR0, TCCR0_CS01);
        clearbit(TCCR0, TCCR0_CS02);
        break;
    }

    case PRESCALER_8:
    {
        clearbit(TCCR0, TCCR0_CS00);
        setbit(TCCR0, TCCR0_CS01);
        clearbit(TCCR0, TCCR0_CS02);
        break;
    }

    case PRESCALER_64:
    {
        setbit(TCCR0, TCCR0_CS00);
        setbit(TCCR0, TCCR0_CS01);
        clearbit(TCCR0, TCCR0_CS02);
        break;
    }

    case PRESCALER_256:
    {
        clearbit(TCCR0, TCCR0_CS00);
        clearbit(TCCR0, TCCR0_CS01);
        setbit(TCCR0, TCCR0_CS02);
        break;
    }

    case PRESCALER_1024:
    {
        setbit(TCCR0, TCCR0_CS00);
        clearbit(TCCR0, TCCR0_CS01);
        setbit(TCCR0, TCCR0_CS02);
        break;
    }

    case EXT_CLK_FAILING_EGDE:
    {
        clearbit(TCCR0, TCCR0_CS00);
        setbit(TCCR0, TCCR0_CS01);
        setbit(TCCR0, TCCR0_CS02);
        break;
    }

    case EXT_CLK_RISING_EGDE:
    {
        setbit(TCCR0, TCCR0_CS00);
        setbit(TCCR0, TCCR0_CS01);
        setbit(TCCR0, TCCR0_CS02);
        break;
    }

    default:
        break;
    }
}

void TIMER0_Delay_ms_with_Blocking(uint16 Milli_Seconds)
{
    // calculate the correct prescale to make the time_to_overflow == 1 ms
    uint16 correct_prescaler = PRESCALER_64;

    uint8 ticks_to_1ms = 250; // for 16-MHZ clock
    // uint8 ticks_to_1ms = 125; // for 8-MHZ clock

    // loop on Milli_Seconds and poll on the overflow flag and decrement Milli_Seconds
    switch (Config.Mode)
    {
    case TIMER0_NORMAL_MODE:
    {
        TCNT0 = TIMER0_MAX_COUNT - ticks_to_1ms;
        set_Timer0_Prescaler(correct_prescaler);
        while (Milli_Seconds)
        {

            while (getbit(TIFR, TIRF_TOV0) == 0) // poll on the overflow-flag
                ;
            TCNT0 = TIMER0_MAX_COUNT - ticks_to_1ms;
            setbit(TIFR, TIRF_TOV0);
            Milli_Seconds--;
        }
        break;
    }
    case TIMER0_CTC_MODE:
    {
        OCR0 = (uint8)ticks_to_1ms;
        set_Timer0_Prescaler(PRESCALER_64);
        // TCCR0 = (TCCR0 & 0xF8) | 0x03;
        while (Milli_Seconds)
        {

            while (getbit(TIFR, TIRF_OCF0) == 0) // poll on the compare-flag
                ;
            setbit(TIFR, TIRF_OCF0);
            Milli_Seconds--;
        }
        break;
    }
    default:
        break;
    }
    stopTimer0();
    // TCCR0 &= 0xF8;
}

void TIMER0_Delay_us_with_Blocking(uint16 Micro_Seconds)
{
    // calculate the correct prescale to make the time_to_overflow == 1 ms
    uint16 correct_prescaler = PRESCALER_1;

    uint8 ticks_to_1us = 16; // for 16-MHZ clock
    // uint8 ticks_to_1us = 8; // for 8-MHZ clock

    // loop on Milli_Seconds and poll on the overflow flag and decrement Milli_Seconds
    switch (Config.Mode)
    {
    case TIMER0_NORMAL_MODE:
    {
        TCNT0 = TIMER0_MAX_COUNT - ticks_to_1us;
        set_Timer0_Prescaler(correct_prescaler);
        while (Micro_Seconds)
        {

            while (getbit(TIFR, TIRF_TOV0) == 0) // poll on the overflow-flag
                ;
            TCNT0 = TIMER0_MAX_COUNT - ticks_to_1us;
            setbit(TIFR, TIRF_TOV0);
            Micro_Seconds--;
        }
        break;
    }
    case TIMER0_CTC_MODE:
    {
        OCR0 = ticks_to_1us;
        set_Timer0_Prescaler(correct_prescaler);
        while (Micro_Seconds)
        {
            // TCCR0 = (TCCR0 & PRESCALER_CLEAR) | 0x01;
            while (getbit(TIFR, TIRF_OCF0) == 0) // poll on the overflow-flag
                ;
            setbit(TIFR, TIRF_OCF0);
            Micro_Seconds--;
        }
        break;
    }
    default:
        break;
    }

    stopTimer0();
}
