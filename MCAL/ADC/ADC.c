#include "ADC_Interface.h"
#include "../../LIB/Calcbit.h"
// #include <avr/interrupt.h>
extern uint16 adc_last_result;
static uint16 g_result_adjust;
static double g_adc_step;
func_ptr_t ADC_ISR_callback = NULL;

void ADC_setPrescaler(void)
{
    if (((F_CPU / ADC_PRESCALER_2) <= ADC_MAX_FREQ) && ((F_CPU / ADC_PRESCALER_2) >= ADC_MIN_FREQ))
    {
        setbit(ADCSRA, ADCSRA_ADPS0);
        clearbit(ADCSRA, ADCSRA_ADPS1);
        clearbit(ADCSRA, ADCSRA_ADPS2);
    }

    else if (((F_CPU / ADC_PRESCALER_4) <= ADC_MAX_FREQ) && ((F_CPU / ADC_PRESCALER_4) >= ADC_MIN_FREQ))
    {
        clearbit(ADCSRA, ADCSRA_ADPS0);
        setbit(ADCSRA, ADCSRA_ADPS1);
        clearbit(ADCSRA, ADCSRA_ADPS2);
    }
    else if (((F_CPU / ADC_PRESCALER_8) <= ADC_MAX_FREQ) && ((F_CPU / ADC_PRESCALER_8) >= ADC_MIN_FREQ))
    {
        setbit(ADCSRA, ADCSRA_ADPS0);
        setbit(ADCSRA, ADCSRA_ADPS1);
        clearbit(ADCSRA, ADCSRA_ADPS2);
    }
    else if (((F_CPU / ADC_PRESCALER_16) <= ADC_MAX_FREQ) && ((F_CPU / ADC_PRESCALER_16) >= ADC_MIN_FREQ))
    {
        clearbit(ADCSRA, ADCSRA_ADPS0);
        clearbit(ADCSRA, ADCSRA_ADPS1);
        setbit(ADCSRA, ADCSRA_ADPS2);
    }
    else if (((F_CPU / ADC_PRESCALER_32) <= ADC_MAX_FREQ) && ((F_CPU / ADC_PRESCALER_32) >= ADC_MIN_FREQ))
    {
        setbit(ADCSRA, ADCSRA_ADPS0);
        clearbit(ADCSRA, ADCSRA_ADPS1);
        setbit(ADCSRA, ADCSRA_ADPS2);
    }

    else if (((F_CPU / ADC_PRESCALER_64) <= ADC_MAX_FREQ) && ((F_CPU / ADC_PRESCALER_64) >= ADC_MIN_FREQ))
    {
        clearbit(ADCSRA, ADCSRA_ADPS0);
        setbit(ADCSRA, ADCSRA_ADPS1);
        setbit(ADCSRA, ADCSRA_ADPS2);
    }
    else
    {
        setbit(ADCSRA, ADCSRA_ADPS0);
        setbit(ADCSRA, ADCSRA_ADPS1);
        setbit(ADCSRA, ADCSRA_ADPS2);
    }
}
void ADC_setVref(uint8 vrefSelect)
{
    switch (vrefSelect)
    {
    case ADC_REFVOLTAGE_VREF:
    {
        clearbit(ADMUX, ADMUX_REFS0);
        clearbit(ADMUX, ADMUX_REFS1);
        g_adc_step = ADC_AREF_VOLT_VALUE / ADC_RESLUTION;
        break;
    }
    case ADC_REFVOLTAGE_AVCC:
    {
        setbit(ADMUX, ADMUX_REFS0);
        clearbit(ADMUX, ADMUX_REFS1);
        g_adc_step = ADC_AVCC_VOLT_VALUE / ADC_RESLUTION;
        break;
    }
    case ADC_REFVOLTAGE_INTERNAL:
    {
        setbit(ADMUX, ADMUX_REFS0);
        setbit(ADMUX, ADMUX_REFS1);
        g_adc_step = ADC_INTERNAL_VOLT_VALUE / ADC_RESLUTION;
        break;
    }
    default:
        break;
    }
}
void ADC_result_adjusting(uint8 result_adjust)
{
    switch (result_adjust)
    {
    case ADC_LEFT_ADJUST:
    {
        setbit(ADMUX, ADMUX_ADLAR);
        g_result_adjust = ADC_LEFT_ADJUST;
        break;
    }
    case ADC_RIGHT_ADJUST:
    {
        clearbit(ADMUX, ADMUX_ADLAR);
        g_result_adjust = ADC_RIGHT_ADJUST;
        break;
    }

    default:
        break;
    }
}
void ADC_channel_init(uint8 mask)
{
    // set channel and gain selection
    ADMUX |= mask;
    // init used channels pin direction
    if ((mask == ADC_SINGLE_ENDDED_ADC0) ||
        (mask == ADC_DIFF_ADC0_ADC0_10x) ||
        (mask == ADC_DIFF_ADC1_ADC0_10x) ||
        (mask == ADC_DIFF_ADC0_ADC0_200x) ||
        (mask == ADC_DIFF_ADC1_ADC0_200x) ||
        (mask == ADC_DIFF_ADC0_ADC1_1x) ||
        (mask == ADC_DIFF_ADC0_ADC2_1x))
    {
        clearbit(ADC_DDRA, ADC_CHANNEL0);
    }
    if ((mask == ADC_SINGLE_ENDDED_ADC1) ||
        (mask == ADC_DIFF_ADC1_ADC0_10x) ||
        (mask == ADC_DIFF_ADC1_ADC0_200x) ||
        (mask == ADC_DIFF_ADC0_ADC1_1x) ||
        (mask == ADC_DIFF_ADC1_ADC1_1x) ||
        (mask == ADC_DIFF_ADC2_ADC1_1x) ||
        (mask == ADC_DIFF_ADC3_ADC1_1x) ||
        (mask == ADC_DIFF_ADC4_ADC1_1x) ||
        (mask == ADC_DIFF_ADC5_ADC1_1x) ||
        (mask == ADC_DIFF_ADC6_ADC1_1x) ||
        (mask == ADC_DIFF_ADC7_ADC1_1x) ||
        (mask == ADC_DIFF_ADC1_ADC2_1x))
    {
        clearbit(ADC_DDRA, ADC_CHANNEL1);
    }
    if ((mask == ADC_SINGLE_ENDDED_ADC2) ||
        (mask == ADC_DIFF_ADC2_ADC2_10x) ||
        (mask == ADC_DIFF_ADC3_ADC2_10x) ||
        (mask == ADC_DIFF_ADC2_ADC2_200x) ||
        (mask == ADC_DIFF_ADC3_ADC2_200x) ||
        (mask == ADC_DIFF_ADC2_ADC1_1x) ||
        (mask == ADC_DIFF_ADC0_ADC2_1x) ||
        (mask == ADC_DIFF_ADC1_ADC2_1x) ||
        (mask == ADC_DIFF_ADC2_ADC2_1x) ||
        (mask == ADC_DIFF_ADC3_ADC2_1x) ||
        (mask == ADC_DIFF_ADC4_ADC2_1x) ||
        (mask == ADC_DIFF_ADC5_ADC2_1x))
    {
        clearbit(ADC_DDRA, ADC_CHANNEL2);
    }

    if ((mask == ADC_SINGLE_ENDDED_ADC3) ||
        (mask == ADC_DIFF_ADC3_ADC2_10x) ||
        (mask == ADC_DIFF_ADC3_ADC2_200x) ||
        (mask == ADC_DIFF_ADC3_ADC1_1x) ||
        (mask == ADC_DIFF_ADC3_ADC2_1x))
    {
        clearbit(ADC_DDRA, ADC_CHANNEL3);
    }

    if ((mask == ADC_SINGLE_ENDDED_ADC4) ||
        (mask == ADC_DIFF_ADC4_ADC1_1x) ||
        (mask == ADC_DIFF_ADC4_ADC2_1x))
    {
        clearbit(ADC_DDRA, ADC_CHANNEL4);
    }
    if ((mask == ADC_SINGLE_ENDDED_ADC5) ||
        (mask == ADC_DIFF_ADC5_ADC1_1x) ||
        (mask == ADC_DIFF_ADC5_ADC2_1x))
    {
        clearbit(ADC_DDRA, ADC_CHANNEL5);
    }
    if ((mask == ADC_SINGLE_ENDDED_ADC6) ||
        (mask == ADC_DIFF_ADC6_ADC1_1x))
    {
        clearbit(ADC_DDRA, ADC_CHANNEL6);
    }
    if ((mask == ADC_SINGLE_ENDDED_ADC7) ||
        (mask == ADC_DIFF_ADC7_ADC1_1x))
    {
        clearbit(ADC_DDRA, ADC_CHANNEL7);
    }
}

void ADC_setTriggerSource(uint8 autoTriggerSource)
{
    switch (autoTriggerSource)
    {
    case ADC_AUTO_TRIGGER_SOURCE_FREE_RUNNING:
    {
        clearbit(SFIOR, SFIOR_ADTS0);
        clearbit(SFIOR, SFIOR_ADTS1);
        clearbit(SFIOR, SFIOR_ADTS2);
        break;
    }
    case ADC_AUTO_TRIGGER_SOURCE_ANALOG_COMPARATOR:
    {
        setbit(SFIOR, SFIOR_ADTS0);
        clearbit(SFIOR, SFIOR_ADTS1);
        clearbit(SFIOR, SFIOR_ADTS2);
        break;
    }
    case ADC_AUTO_TRIGGER_SOURCE_EXT_INTR0:
    {
        clearbit(SFIOR, SFIOR_ADTS0);
        setbit(SFIOR, SFIOR_ADTS1);
        clearbit(SFIOR, SFIOR_ADTS2);
        break;
    }
    case ADC_AUTO_TRIGGER_SOURCE_TIMER0_COMP_MATCH:
    {
        setbit(SFIOR, SFIOR_ADTS0);
        setbit(SFIOR, SFIOR_ADTS1);
        clearbit(SFIOR, SFIOR_ADTS2);
        break;
    }
    case ADC_AUTO_TRIGGER_SOURCE_TIMER0_OVERFLOW:
    {
        clearbit(SFIOR, SFIOR_ADTS0);
        clearbit(SFIOR, SFIOR_ADTS1);
        setbit(SFIOR, SFIOR_ADTS2);
        break;
    }
    case ADC_AUTO_TRIGGER_SOURCE_TIMER1_COMP_MATCH_B:
    {
        setbit(SFIOR, SFIOR_ADTS0);
        clearbit(SFIOR, SFIOR_ADTS1);
        setbit(SFIOR, SFIOR_ADTS2);
        break;
    }
    case ADC_AUTO_TRIGGER_SOURCE_TIMER1_OVERFLOW:
    {
        clearbit(SFIOR, SFIOR_ADTS0);
        setbit(SFIOR, SFIOR_ADTS1);
        setbit(SFIOR, SFIOR_ADTS2);
        break;
    }

    case ADC_AUTO_TRIGGER_SOURCE_TIMER1_EVENT_CAPTURE:
    {
        setbit(SFIOR, SFIOR_ADTS0);
        setbit(SFIOR, SFIOR_ADTS1);
        setbit(SFIOR, SFIOR_ADTS2);
        break;
    }

    default:
        break;
    }
}
void ADC_init(ADC_Config_t conf)
{

    // 2- control reg
    // ADC enable
    setbit(ADCSRA, ADCSRA_ADEN);

    // calculate the prescaler that makes 50khz<= f_adc <= 200khz
    ADC_setPrescaler();
    // 1- dmux reg
    // set vref select
    ADC_setVref(conf.ref_volt);

    // set l-r adjust
    ADC_result_adjusting(conf.result_adjust);
    // set channel and gain selection
    // init used channels pin direction
    ADC_channel_init(conf.analog_channel_and_gain_select_mask);

    // enable auto trigger
    if (conf.enable_autoTriggerMode == ADC_ENABLE_AUTOTRIGGER)
    {
        setbit(ADCSRA, ADCSRA_ADATE);
        // 3.sfior ref
        // set trigger source
        ADC_setTriggerSource(conf.autoTriggerSource);
    }
    // interrupt enable
    if (conf.enable_interrupt == ADC_ENABLE_INTR)
    {
        setbit(SREG, GIE);
        setbit(ADCSRA, ADCSRA_ADIE);
    }
}
uint16 ADC_getReading(uint8 *low, uint8 *high)
{
    // ADC Start Conversion
    // ADSC -> ADCSRA
    uint16 result;
    if (g_result_adjust == ADC_LEFT_ADJUST)
        result = (ADCDATA) >> 6;
    else
        result = ADCDATA;
    return result;
}
void start_conversion()
{
    setbit(ADCSRA, ADCSRA_ADSC);
}
unsigned int ADC_PollRead(uint8 *low, uint8 *high)
{
    // ADC Start Conversion
    // ADSC -> ADCSRA
    start_conversion();

    while ((getbit(ADCSRA, ADCSRA_ADIF) == LOW)) // / conversion in progress
        ;
    setbit(ADCSRA, ADCSRA_ADIF); // clear flag
    uint16 adc_read = ADC_getReading(low, high);
    return adc_read;
}
void ADC_setCallBack(func_ptr_t callback)
{
    if (callback)
        ADC_ISR_callback = callback;
}

// void __vector_16(void) __attribute__((signal, used));
// void __vector_16(void)
// {
//     // if (ADC_ISR_callback)
//     // {
//     // (*ADC_ISR_callback)();
//     adc_last_result = ADC_getReading(NULL, NULL);

//     setbit(*(volatile uint8 *)(0x3a), 7);
//     togglebit(*(volatile uint8 *)(0x3b), 7);
//     // ADC Start Conversion
//     setbit(ADCSRA, ADCSRA_ADSC);
//     // }
// }

ISR(ADC_VECT)
{
    adc_last_result = ADC_getReading(NULL, NULL);

    setbit(*(volatile uint8 *)(0x3a), 7);
    togglebit(*(volatile uint8 *)(0x3b), 7);
    // ADC Start Conversion
    setbit(ADCSRA, ADCSRA_ADSC);
}