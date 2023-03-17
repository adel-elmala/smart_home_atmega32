#ifndef ADC_REG_H
#define ADC_REG_H
#include "../../LIB/Datatypes.h"
/*
ADC Multiplexer
Selection Register – ADMUX
*/
#define ADMUX (*((volatile uint8 *)(0x27)))
// Bits 4:0 – MUX4:0: Analog Channel and Gain Selection Bits
#define ADMUX_MUX0 0
#define ADMUX_MUX1 1
#define ADMUX_MUX2 2
#define ADMUX_MUX3 3
#define ADMUX_MUX4 4
// Bit 5 – ADLAR: ADC Left Adjust Result
#define ADMUX_ADLAR 5
// Bit 7:6 – REFS1:0: Reference Selection Bits
#define ADMUX_REFS0 6
#define ADMUX_REFS1 7

/*
ADC Control and
Status Register A – ADCSRA
*/
#define ADCSRA (*((volatile uint8 *)(0x26)))

// Bit 7 – ADEN: ADC Enable
#define ADCSRA_ADEN 7
// Bit 6 – ADSC: ADC Start Conversion
#define ADCSRA_ADSC 6
// Bit 5 – ADATE: ADC Auto Trigger Enable
#define ADCSRA_ADATE 5
// Bit 4 – ADIF: ADC Interrupt Flag
#define ADCSRA_ADIF 4
// Bit 3 – ADIE: ADC Interrupt Enable
#define ADCSRA_ADIE 3
// Bits 2:0 – ADPS2:0: ADC Prescaler Select Bits
#define ADCSRA_ADPS2 2
#define ADCSRA_ADPS1 1
#define ADCSRA_ADPS0 0

/*
The ADC Data
Register – ADCL and ADCH
*/
#define ADCH (*((volatile uint8 *)(0x25)))
#define ADCL (*((volatile uint8 *)(0x24)))
#define ADCDATA (*((volatile uint16 *)(0x24)))

/*
Special FunctionIO
Register – SFIOR
*/
#define SFIOR (*((volatile uint8 *)(0x50)))
// Bit 7:5 – ADTS2:0: ADC Auto Trigger Source
#define SFIOR_ADTS2 7
#define SFIOR_ADTS1 6
#define SFIOR_ADTS0 5
// Bit 4 – Reserved Bit
#define SFIOR_RESERVED 4
// Bit 3:0 IGNORE
#define SFIOR_ACME 3
#define SFIOR_PUD 2
#define SFIOR_PSR2 1
#define SFIOR_PSR10 0

#define ADC_DDRA (*((volatile uint8 *)(0x3A)))

#define SREG (*((volatile uint8 *)(0x5F)))
#define GIE 7

#define ADC_CHANNEL0 0
#define ADC_CHANNEL1 1
#define ADC_CHANNEL2 2
#define ADC_CHANNEL3 3
#define ADC_CHANNEL4 4
#define ADC_CHANNEL5 5
#define ADC_CHANNEL6 6
#define ADC_CHANNEL7 7
#endif