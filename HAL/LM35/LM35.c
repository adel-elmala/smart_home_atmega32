#include "LM35_Interface.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../MCAL/ADC/ADC_Interface.h"

uint16 adc_last_result = 0;

void LM35_vInit()
{
    // init output volt pin to be used as adc input
    // ADC_Config_t adc_conf = {ADC_REFVOLTAGE_AVCC,
    ADC_Config_t adc_conf = {ADC_REFVOLTAGE_INTERNAL,
                             ADC_LEFT_ADJUST,
                             ADC_SINGLE_ENDDED_ADC1,
                             //  ADC_DISABLE_INTR,
                             ADC_ENABLE_INTR,
                             ADC_DISABLE_AUTOTRIGGER,
                             ADC_AUTO_TRIGGER_SOURCE_IGNORE};
    ADC_init(adc_conf);
    ADC_setCallBack(get_adc_last_read);
}
unsigned int LM35_u16GetReading()
{
    uint8 adc_low, adc_high;
    unsigned int adc_volt_reading = ADC_PollRead(&adc_low, &adc_high);
    // return ((adc_volt_reading - ((-LM35_MIN_TEMP) * LM35_STEP_mVOLT)) / LM35_STEP_mVOLT);
    return (adc_volt_reading / 4);
}

unsigned int LM35_u16GetReading_NotBLocking()
{
    start_conversion();
    return (adc_last_result / 4);
}
void get_adc_last_read(void)
{
    adc_last_result = ADC_getReading(NULL, NULL);
}
