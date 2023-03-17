#include "DIO_Interface.h"
#include "DIO_REG.h"

#include "../../LIB/Calcbit.h"

void DIO_vSetPinDirection(uint8 Copy_u8PORT, uint8 Copy_u8PinNumber, uint8 copy_u8state)
{
    switch (Copy_u8PORT)
    {
    case PORTA:
    {
        if (copy_u8state == INPUT)
            clearbit(PORTA_BASE.DDR, Copy_u8PinNumber);
        else
            setbit(PORTA_BASE.DDR, Copy_u8PinNumber);
        break;
    }

    case PORTB:
    {
        if (copy_u8state == INPUT)
            clearbit(PORTB_BASE.DDR, Copy_u8PinNumber);
        else
            setbit(PORTB_BASE.DDR, Copy_u8PinNumber);

        break;
    }
    case PORTC:
    {
        if (copy_u8state == INPUT)
            clearbit(PORTC_BASE.DDR, Copy_u8PinNumber);
        else
            setbit(PORTC_BASE.DDR, Copy_u8PinNumber);
        break;
    }
    case PORTD:
    {
        if (copy_u8state == INPUT)
            clearbit(PORTD_BASE.DDR, Copy_u8PinNumber);
        else
            setbit(PORTD_BASE.DDR, Copy_u8PinNumber);
        break;
    }

    default:
        break;
    }
}
void DIO_vWritePin(uint8 Copy_u8PORT, uint8 Copy_u8PinNumber, uint8 Copy_u8value)
{
    switch (Copy_u8PORT)
    {
    case PORTA:
    {
        if (Copy_u8value == LOW)
            clearbit(PORTA_BASE.Port, Copy_u8PinNumber);
        else
            setbit(PORTA_BASE.Port, Copy_u8PinNumber);
        break;
    }

    case PORTB:
    {
        if (Copy_u8value == LOW)
            clearbit(PORTB_BASE.Port, Copy_u8PinNumber);
        else
            setbit(PORTB_BASE.Port, Copy_u8PinNumber);

        break;
    }
    case PORTC:
    {
        if (Copy_u8value == LOW)
            clearbit(PORTC_BASE.Port, Copy_u8PinNumber);
        else
            setbit(PORTC_BASE.Port, Copy_u8PinNumber);
        break;
    }
    case PORTD:
    {
        if (Copy_u8value == LOW)
            clearbit(PORTD_BASE.Port, Copy_u8PinNumber);
        else
            setbit(PORTD_BASE.Port, Copy_u8PinNumber);
        break;
    }

    default:
        break;
    }
}
void DIO_vTogglePin(uint8 Copy_u8PORT, uint8 Copy_u8PinNumber)
{

    switch (Copy_u8PORT)
    {
    case PORTA:
    {
        togglebit(PORTA_BASE.Port, Copy_u8PinNumber);
        break;
    }

    case PORTB:
    {
        togglebit(PORTB_BASE.Port, Copy_u8PinNumber);
        break;
    }
    case PORTC:
    {
        togglebit(PORTC_BASE.Port, Copy_u8PinNumber);
        break;
    }
    case PORTD:
    {
        togglebit(PORTD_BASE.Port, Copy_u8PinNumber);
        break;
    }

    default:
        break;
    }
}
void DIO_vSetPortDirection(uint8 Copy_u8PORT, uint8 copy_u8state)
{

    switch (Copy_u8PORT)
    {
    case PORTA:
    {
        if (copy_u8state == INPUT)
            PORTA_BASE.DDR = LOW_PORT;
        else
            PORTA_BASE.DDR = HIGH_PORT;

        break;
    }

    case PORTB:
    {
        if (copy_u8state == INPUT)
            PORTB_BASE.DDR = LOW_PORT;
        else
            PORTB_BASE.DDR = HIGH_PORT;

        break;
    }
    case PORTC:
    {
        if (copy_u8state == INPUT)
            PORTC_BASE.DDR = LOW_PORT;
        else
            PORTC_BASE.DDR = HIGH_PORT;

        break;
    }
    case PORTD:
    {

        if (copy_u8state == INPUT)
            PORTD_BASE.DDR = LOW_PORT;
        else
            PORTD_BASE.DDR = HIGH_PORT;
        break;
    }

    default:
        break;
    }
}
void DIO_vWritePort(uint8 Copy_u8PORT, uint8 Copy_u8value)
{
    switch (Copy_u8PORT)
    {
    case PORTA:
    {
        PORTA_BASE.Port = Copy_u8value;
        break;
    }

    case PORTB:
    {
        PORTB_BASE.Port = Copy_u8value;
        break;
    }
    case PORTC:
    {
        PORTC_BASE.Port = Copy_u8value;
        break;
    }
    case PORTD:
    {
        PORTD_BASE.Port = Copy_u8value;
        break;
    }

    default:
        break;
    }
}
uint8 DIO_u8GetPinValue(uint8 Copy_u8PORT, uint8 Copy_u8PinNumber)
{
    uint8 result = 0;
    switch (Copy_u8PORT)
    {
    case PORTA:
    {
        result = getbit(PORTA_BASE.Pin, Copy_u8PinNumber);
        break;
    }

    case PORTB:
    {
        result = getbit(PORTB_BASE.Pin, Copy_u8PinNumber);
        break;
    }
    case PORTC:
    {
        result = getbit(PORTC_BASE.Pin, Copy_u8PinNumber);
        break;
    }
    case PORTD:
    {
        result = getbit(PORTD_BASE.Pin, Copy_u8PinNumber);
        break;
    }

    default:
        break;
    }
    return result;
}
void DIO_vTogglePort(uint8 Copy_u8PORT)
{
    switch (Copy_u8PORT)
    {
    case PORTA:
    {
        PORTA_BASE.Port ^= HIGH_PORT;
        break;
    }

    case PORTB:
    {
        PORTB_BASE.Port ^= HIGH_PORT;
        break;
    }
    case PORTC:
    {
        PORTC_BASE.Port ^= HIGH_PORT;
        break;
    }
    case PORTD:
    {
        PORTD_BASE.Port ^= HIGH_PORT;
        break;
    }

    default:
        break;
    }
}

uint8 DIO_u8GetPortValue(uint8 Copy_u8PORT)
{
    uint8 result = 0;
    switch (Copy_u8PORT)
    {
    case PORTA:
    {
        result = PORTA_BASE.Pin;
        break;
    }

    case PORTB:
    {
        result = PORTB_BASE.Pin;
        break;
    }
    case PORTC:
    {
        result = PORTC_BASE.Pin;
        break;
    }
    case PORTD:
    {
        result = PORTD_BASE.Pin;
        break;
    }

    default:
        break;
    }
    return result;
}
