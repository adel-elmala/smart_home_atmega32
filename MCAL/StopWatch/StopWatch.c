#include "StopWatch_Interface.h"
#include "StopWatch_REG.h"
#include "StopWatch_Private.h"

#include "../../LIB/Calcbit.h"
#include "../GIE/GIE_Interface.h"
static unsigned long int g_number_of_overflow = 0;

void StopWatch_Init()
{
    // disable force output compare
    clearbit(TCCR2, TCCR2_FOC2);
    // normal mode
    clearbit(TCCR2, TCCR2_WGM20);
    clearbit(TCCR2, TCCR2_WGM21);
    // oc2 diconnect
    clearbit(TCCR2, TCCR2_COM20);
    clearbit(TCCR2, TCCR2_COM21);

    // enable overflow interrupt
    setbit(TIMSK, TIMSK_TOIE2);
    // enable global intrrupt
    // _sei();
    sei();
}
void StopWatch_Start()
{
    // start clk -- no prescaler
    setbit(TCCR2, TCCR2_CS20);
}
void StopWatch_Stop(StopWatch_t *clk)
{
    // start clk -- no prescaler
    clearbit(TCCR2, TCCR2_CS20);
    StopWatch_Calculate_time(clk);

    g_number_of_overflow = 0;
}
void StopWatch_Snap(StopWatch_t *clk)
{
    StopWatch_Calculate_time(clk);
}

void StopWatch_Calculate_time(StopWatch_t *clk)
{
    uint8 current_count = TCNT2;
    uint32 current_overflow_number = g_number_of_overflow;

    double tick_time = 1.0 / (double)F_CPU;                    // in seconds
    double overflow_time = tick_time * (TIMER2_MAX_COUNT + 1); // in seconds

    double total_time_in_seconds = (current_count * tick_time) + (current_overflow_number * overflow_time);

    clk->seconds = (uint32)total_time_in_seconds;
    clk->milli_seconds = (uint32)((total_time_in_seconds - clk->seconds) * 1000);
    clk->u_seconds = (uint32)((((total_time_in_seconds - clk->seconds) * 1000) - clk->milli_seconds) * 1000);
}

/* timer2 tcnt2 overflow ISR  */
void __vector_5(void) __attribute__((signal, used));
void __vector_5(void)
{
    g_number_of_overflow++;
}