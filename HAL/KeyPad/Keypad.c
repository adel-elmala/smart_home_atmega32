#include "Keypad_Interface.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../MCAL/DIO/DIO_REG.h"
// #define F_CPU 8000000UL
#include <util/delay.h>

#define keypad_output_port PORTC
#define keypad_input_port PORTD

#define ROW1 PIN5
#define ROW2 PIN4
#define ROW3 PIN3
#define ROW4 PIN2

#define COL1 PIN7
#define COL2 PIN6
#define COL3 PIN5
#define COL4 PIN3

uint8 columns[4] = {COL1, COL2, COL3, COL4};
uint8 rows[4] = {ROW1, ROW2, ROW3, ROW4};

uint8 labels[4][4] = {
    {'7', '8', '9', '/'},
    {'4', '5', '6', '*'},
    {'1', '2', '3', '-'},
    {'c', '0', '+', '='}};

void keypad_init(void)
{
    for (int i = 0; i < 4; ++i)
    {
        DIO_vSetPinDirection(keypad_output_port, rows[i], OUTPUT);
        DIO_vSetPinDirection(keypad_input_port, columns[i], INPUT);
    }
}

void setAllRows(uint8 value)
{
    for (int i = 0; i < 4; i++)
        DIO_vWritePin(keypad_output_port, rows[i], value);
}

/*  Checks if there is a button press
    Returns the column number that has the pressed button and 0 if no press */
inline uint8 buttonPressed(uint8 avoidLongPress)
{
    // uint8 stat;
    uint8 allHighMask = (1 << COL1) | (1 << COL2) | (1 << COL3) | (1 << COL4);
    uint8 col1LowMask = (1 << COL2) | (1 << COL3) | (1 << COL4);
    uint8 col2LowMask = (1 << COL1) | (1 << COL3) | (1 << COL4);
    uint8 col3LowMask = (1 << COL1) | (1 << COL2) | (1 << COL4);

    uint8 colsReading = DIO_u8GetPortValue(keypad_input_port);

    if ((colsReading & allHighMask) == allHighMask) // all cols are high - no btn press
        return 0;

    if (avoidLongPress == 1)
    {
        while ((allHighMask & DIO_u8GetPortValue(keypad_input_port)) == (colsReading & allHighMask)) // to handle long press
            ;
    }

    if ((colsReading & allHighMask) == col1LowMask)
        return 1;
    else if ((colsReading & allHighMask) == col2LowMask)
        return 2;
    else if ((colsReading & allHighMask) == col3LowMask)
        return 3;
    return 4;
}

uint8 getRow(void)
{
    uint8 rowNumber = 0xFF;
    uint8 colNumber = 0;
    for (int i = 0; i < 4; ++i)
    {
        setAllRows(HIGH);
        DIO_vWritePin(keypad_output_port, rows[i], LOW); // then set one row to be low
        if ((colNumber = buttonPressed(1)) != 0)
        {
            rowNumber = i + 1;
            break;
        }
    }
    return rowNumber;
}

uint8 keypad_GetPress(void)
{
    uint8 colNumber = 0;
    uint8 rowNumber = 0;

    setAllRows(LOW);
    while ((colNumber = buttonPressed(0)) == 0)
        ;
    // if ((colNumber = buttonPressed(0)) == 0)
    //     _delay_ms(500);
    rowNumber = getRow();
    return labels[rowNumber - 1][colNumber - 1];
}
