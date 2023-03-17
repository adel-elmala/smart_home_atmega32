#ifndef LCD_INTERFACE
#define LCD_INTERFACE
#include "../../LIB/Datatypes.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../MCAL/DIO/DIO_REG.h"

// typedef struct LCD_CONFIG
// {
//     uint8 mode;

// } LCD_CONFIG_t;

#define LCD_DATA_PORT PORTB
#define LCD_CONTROL_PORT PORTA

#define LCD_DATA_0 PIN0
#define LCD_DATA_1 PIN1
#define LCD_DATA_2 PIN2
// #define LCD_DATA_3 PIN3
#define LCD_DATA_3 PIN4

// #define LCD_DATA_4 PIN4
// #define LCD_DATA_5 PIN5
// #define LCD_DATA_6 PIN6
// #define LCD_DATA_7 PIN7

#define LCD_CONTROL_RS PIN3
#define LCD_CONTROL_RW PIN6
#define LCD_CONTROL_E PIN2

#define LCD_8bit_MODE 8
#define LCD_4bit_MODE 4

#define LCD_WRITE LOW
#define LCD_READ HIGH
#define LCD_COMMAND_REG LOW
#define LCD_DATA_REG HIGH

#define LCD_LINE_1 0x80
#define LCD_LINE_2 0xc0
#define LCD_LINE_3 0x94
#define LCD_LINE_4 0xd4
#define LCD_COL_1 1
#define LCD_COL_2 2
#define LCD_COL_3 3
#define LCD_COL_4 4
#define LCD_COL_5 5
#define LCD_COL_6 6
#define LCD_COL_7 7
#define LCD_COL_8 8
#define LCD_COL_9 9
#define LCD_COL_10 10
#define LCD_COL_11 11
#define LCD_COL_12 12
#define LCD_COL_13 13
#define LCD_COL_14 14
#define LCD_COL_15 15
#define LCD_COL_16 16
#define LCD_COL_17 17
#define LCD_COL_18 18
#define LCD_COL_19 19
#define LCD_COL_20 20

void lcd_init(void);
void lcd_sendCommand(uint8 commandCode);
void lcd_sendData(uint8 data);
void lcd_displayString(char *string);
void lcd_clearAndHome();
void lcd_goto_line2();
void lcd_goto(uint8 line, uint8 col);

#endif