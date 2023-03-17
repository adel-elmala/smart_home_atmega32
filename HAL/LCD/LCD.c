#include "LCD_Interface.h"
// #define F_CPU 16000000UL
// #define F_CPU 8000000UL
#include "../../MCAL/TIMER/timer.h"
// #include <util/delay.h>
void enablePulse(void)
{
    DIO_vWritePin(LCD_CONTROL_PORT, LCD_CONTROL_E, HIGH);
    // _delay_us(1);
    TIMER0_Delay_us_with_Blocking(1);
    DIO_vWritePin(LCD_CONTROL_PORT, LCD_CONTROL_E, LOW);
}
void lcd_init(void)
{
    TIMER0_SetConfig();
    // init ports
    DIO_vSetPinDirection(LCD_DATA_PORT, LCD_DATA_0, OUTPUT);
    DIO_vSetPinDirection(LCD_DATA_PORT, LCD_DATA_1, OUTPUT);
    DIO_vSetPinDirection(LCD_DATA_PORT, LCD_DATA_2, OUTPUT);
    DIO_vSetPinDirection(LCD_DATA_PORT, LCD_DATA_3, OUTPUT);

    DIO_vSetPinDirection(LCD_CONTROL_PORT, LCD_CONTROL_RS, OUTPUT);
    // DIO_vSetPinDirection(LCD_CONTROL_PORT, LCD_CONTROL_RW, OUTPUT); // hardware ground
    DIO_vSetPinDirection(LCD_CONTROL_PORT, LCD_CONTROL_E, OUTPUT);
    // set enable low
    DIO_vWritePin(LCD_CONTROL_PORT, LCD_CONTROL_E, LOW);

    // send commands
    // init lcd mode
    lcd_sendCommand(0x33);
    lcd_sendCommand(0x32); // 4 bit mode
    lcd_sendCommand(0x28); // 2-lines , 5x7 matrix
    lcd_sendCommand(0x0e); // display on , cursor on
    lcd_sendCommand(0x01); // clear lcd
    // _delay_us(2000);
    TIMER0_Delay_us_with_Blocking(2000);
    lcd_sendCommand(0x06); // shift cursor right
}
void lcd_clearAndHome()
{
    lcd_sendCommand(0x01); // clear lcd
    lcd_sendCommand(0x03); // clear lcd
    // _delay_us(2000);
    TIMER0_Delay_us_with_Blocking(2000);
}
void lcd_writeDataNibble(uint8 nibble)
{
    uint8 bit0 = nibble & 0x01;
    uint8 bit1 = (nibble & 0x02) >> 1;
    uint8 bit2 = (nibble & 0x04) >> 2;
    uint8 bit3 = (nibble & 0x08) >> 3;
    DIO_vWritePin(LCD_DATA_PORT, LCD_DATA_0, bit0);
    DIO_vWritePin(LCD_DATA_PORT, LCD_DATA_1, bit1);
    DIO_vWritePin(LCD_DATA_PORT, LCD_DATA_2, bit2);
    DIO_vWritePin(LCD_DATA_PORT, LCD_DATA_3, bit3);
}
void lcd_sendCommand(uint8 commandCode)
{
    uint8 lowNibble = (commandCode & 0x0F);
    uint8 highNibble = (commandCode & 0xF0) >> 4;

    lcd_writeDataNibble(highNibble);
    DIO_vWritePin(LCD_CONTROL_PORT, LCD_CONTROL_RS, LCD_COMMAND_REG);
    // DIO_vWritePin(LCD_CONTROL_PORT, LCD_CONTROL_RW, LCD_WRITE);// hardware ground
    enablePulse();
    // _delay_us(100);
    TIMER0_Delay_us_with_Blocking(100);

    lcd_writeDataNibble(lowNibble);
    enablePulse();
    // _delay_us(100);
    TIMER0_Delay_us_with_Blocking(100);
}
void lcd_sendData(uint8 data)
{
    uint8 lowNibble = (data & 0x0F);
    uint8 highNibble = (data & 0xF0) >> 4;

    lcd_writeDataNibble(highNibble);
    DIO_vWritePin(LCD_CONTROL_PORT, LCD_CONTROL_RS, LCD_DATA_REG);
    // DIO_vWritePin(LCD_CONTROL_PORT, LCD_CONTROL_RW, LCD_WRITE); // hardware ground
    enablePulse();
    // _delay_us(100);
    TIMER0_Delay_us_with_Blocking(100);

    lcd_writeDataNibble(lowNibble);
    enablePulse();
    // _delay_us(100);
    TIMER0_Delay_us_with_Blocking(100);
}

void lcd_displayString(char *string)
{
    while (*string)
    {
        lcd_sendData(*string);
        string++;
    }
}

void lcd_goto_line2()
{
    lcd_sendCommand(0xc0);
}
void lcd_goto(uint8 line, uint8 col)
{
    lcd_sendCommand(line + (col - 1));
}