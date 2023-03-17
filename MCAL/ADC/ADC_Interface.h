#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

#include "ADC_REG.h"
#include "../../LIB/Datatypes.h"

typedef struct ADC_Config
{
    /* data */
    uint8 ref_volt;
    uint8 result_adjust;
    uint8 analog_channel_and_gain_select_mask;
    uint8 enable_interrupt;
    uint8 enable_autoTriggerMode;
    uint8 autoTriggerSource;
} ADC_Config_t;
typedef void (*func_ptr_t)(void);

// Reference Selection MACROS
#define ADC_REFVOLTAGE_VREF 0
#define ADC_REFVOLTAGE_AVCC 1
#define ADC_REFVOLTAGE_INTERNAL 3

#define ADC_AVCC_VOLT_VALUE ((150) * 10) // (max tmp)* (10mv/1clesc)
#define ADC_AREF_VOLT_VALUE ((150) * 10)
#define ADC_INTERNAL_VOLT_VALUE 2560
#define ADC_RESLUTION 1024

// ADC Left Adjust Result MACROS
#define ADC_LEFT_ADJUST 0
#define ADC_RIGHT_ADJUST 1

// ADC Interrupt MACROS
#define ADC_DISABLE_INTR 0
#define ADC_ENABLE_INTR 1

// Analog Channel and Gain Selection Bits MASKS
#define ADC_SINGLE_ENDDED_ADC0 0b00000
#define ADC_SINGLE_ENDDED_ADC1 0b00001
#define ADC_SINGLE_ENDDED_ADC2 0b00010
#define ADC_SINGLE_ENDDED_ADC3 0b00011
#define ADC_SINGLE_ENDDED_ADC4 0b00100
#define ADC_SINGLE_ENDDED_ADC5 0b00101
#define ADC_SINGLE_ENDDED_ADC6 0b00110
#define ADC_SINGLE_ENDDED_ADC7 0b00111

#define ADC_DIFF_ADC0_ADC0_10x 0b01000
#define ADC_DIFF_ADC1_ADC0_10x 0b01001
#define ADC_DIFF_ADC0_ADC0_200x 0b01010
#define ADC_DIFF_ADC1_ADC0_200x 0b01011
#define ADC_DIFF_ADC2_ADC2_10x 0b01100
#define ADC_DIFF_ADC3_ADC2_10x 0b01101
#define ADC_DIFF_ADC2_ADC2_200x 0b01110
#define ADC_DIFF_ADC3_ADC2_200x 0b01111
#define ADC_DIFF_ADC0_ADC1_1x 0b10000
#define ADC_DIFF_ADC1_ADC1_1x 0b10001
#define ADC_DIFF_ADC2_ADC1_1x 0b10010
#define ADC_DIFF_ADC3_ADC1_1x 0b10011
#define ADC_DIFF_ADC4_ADC1_1x 0b10100
#define ADC_DIFF_ADC5_ADC1_1x 0b10101
#define ADC_DIFF_ADC6_ADC1_1x 0b10110
#define ADC_DIFF_ADC7_ADC1_1x 0b10111
#define ADC_DIFF_ADC0_ADC2_1x 0b11000
#define ADC_DIFF_ADC1_ADC2_1x 0b11001
#define ADC_DIFF_ADC2_ADC2_1x 0b11010
#define ADC_DIFF_ADC3_ADC2_1x 0b11011
#define ADC_DIFF_ADC4_ADC2_1x 0b11100
#define ADC_DIFF_ADC5_ADC2_1x 0b11101

#define ADC_SINGLE_ENDDED_1_22V 0b11110
#define ADC_SINGLE_ENDDED_0_V 0b11111

// ADC Prescaler Select MACROS
#define ADC_PRESCALER_2 2
#define ADC_PRESCALER_2 2
#define ADC_PRESCALER_4 4
#define ADC_PRESCALER_8 8
#define ADC_PRESCALER_16 16
#define ADC_PRESCALER_32 32
#define ADC_PRESCALER_64 64
#define ADC_PRESCALER_128 128

#define ADC_MAX_FREQ 200000UL
#define ADC_MIN_FREQ 50000UL

// ADC Auto Trigger Source MACROS
#define ADC_DISABLE_AUTOTRIGGER 0
#define ADC_ENABLE_AUTOTRIGGER 1

#define ADC_AUTO_TRIGGER_SOURCE_FREE_RUNNING 0
#define ADC_AUTO_TRIGGER_SOURCE_ANALOG_COMPARATOR 1
#define ADC_AUTO_TRIGGER_SOURCE_EXT_INTR0 2
#define ADC_AUTO_TRIGGER_SOURCE_TIMER0_COMP_MATCH 3
#define ADC_AUTO_TRIGGER_SOURCE_TIMER0_OVERFLOW 4
#define ADC_AUTO_TRIGGER_SOURCE_TIMER1_COMP_MATCH_B 5
#define ADC_AUTO_TRIGGER_SOURCE_TIMER1_OVERFLOW 6
#define ADC_AUTO_TRIGGER_SOURCE_TIMER1_EVENT_CAPTURE 7
#define ADC_AUTO_TRIGGER_SOURCE_IGNORE 8

#define LOW 0
#define HIGH 1

#define ADC_VECT __vector_16

#define ISR(vector)                                  \
    void vector(void) __attribute__((signal, used)); \
    void vector(void)

void ADC_init(ADC_Config_t conf);
// uint16 ADC_getReading();
uint16 ADC_getReading(uint8 *low, uint8 *high);

unsigned int ADC_PollRead(uint8 *low, uint8 *high);

void ADC_setCallBack(func_ptr_t callback);
void start_conversion();

#endif