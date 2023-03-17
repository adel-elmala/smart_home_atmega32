#include "../../LIB/Calcbit.h"

#include "External_INT_Interface.h"
#include "External_INT_Reg.h"

extern EXT_Int_Conf configuration;

interrupt_callback_t int0_callback = NULL, int1_callback = NULL, int2_callback = NULL;
// void EXT_INT_Init(void)
// {
//     if (config.Enable_INT0_Interrupt)
//         DIO_vSetPinDirection(PORTD, PIN2, INPUT);

//     if (config.Enable_INT1_Interrupt)
//         DIO_vSetPinDirection(PORTD, PIN3, INPUT);

//     if (config.Enable_INT2_Interrupt)
//         DIO_vSetPinDirection(PORTB, PIN2, INPUT);
// }
void EXT_INT_Disable(void)
{
    clearbit(SREG, GIE);
}

void EXT_INT_Enable(void)
{
    setbit(SREG, GIE);
}
void EXT_INT_SET_CONFIG(EXT_Int_Conf config)
{
    setbit(SREG, GIE);

    // Enable or disable external interrupt pins
    if (config.Enable_INT0_Interrupt == ENABLE_INT0)
    {

        setbit(GICR, ENABLE_INT0);
        if (config.INT0_Triggering_Mode == LOW_LEVEL_MODE)
        {
            clearbit(MCUCR, ISC00);
            clearbit(MCUCR, ISC01);
        }
        else if (config.INT0_Triggering_Mode == FALLING_AND_RISING_EDGE_MODE)
        {
            setbit(MCUCR, ISC00);
            clearbit(MCUCR, ISC01);
        }

        else if (config.INT0_Triggering_Mode == FALLING_EDGE_MODE)
        {
            clearbit(MCUCR, ISC00);
            setbit(MCUCR, ISC01);
        }
        else
        {
            setbit(MCUCR, ISC00);
            setbit(MCUCR, ISC01);
        }
    }
    else
        clearbit(GICR, ENABLE_INT0);

    if (config.Enable_INT1_Interrupt == ENABLE_INT1)
    {

        setbit(GICR, ENABLE_INT1);
        if (config.INT1_Triggering_Mode == LOW_LEVEL_MODE)
        {
            clearbit(MCUCR, ISC10);
            clearbit(MCUCR, ISC11);
        }
        else if (config.INT1_Triggering_Mode == FALLING_AND_RISING_EDGE_MODE)
        {
            setbit(MCUCR, ISC10);
            clearbit(MCUCR, ISC11);
        }

        else if (config.INT1_Triggering_Mode == FALLING_EDGE_MODE)
        {
            clearbit(MCUCR, ISC10);
            setbit(MCUCR, ISC11);
        }
        else
        {
            setbit(MCUCR, ISC10);
            setbit(MCUCR, ISC11);
        }
    }
    else
        clearbit(GICR, ENABLE_INT1);

    if (config.Enable_INT2_Interrupt == ENABLE_INT2)
    {
        setbit(GICR, ENABLE_INT2);
        if (config.INT1_Triggering_Mode == RISING_EDGE_MODE)
            setbit(MCUCSR, ISC2);

        else
            clearbit(MCUCSR, ISC2);
    }
    else
        clearbit(GICR, ENABLE_INT2);
}

void register_ext_int_callbacks(interrupt_callback_t int0_clback,
                                interrupt_callback_t int1_clback,
                                interrupt_callback_t int2_clback)
{
    int0_callback = int0_clback;
    int1_callback = int1_clback;
    int2_callback = int2_clback;
}

ISR(EXT_INT0)
{
    if (int0_callback != NULL)
        (*int0_callback)();
}

ISR(EXT_INT1)
{
    if (int1_callback != NULL)
        (*int1_callback)();
}
ISR(EXT_INT2)
{
    if (int2_callback != NULL)
        (*int2_callback)();
}