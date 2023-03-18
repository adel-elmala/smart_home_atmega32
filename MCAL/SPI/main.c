#include <avr/delay.h>
#include "DIO_INTERFACE.h"
#include "LCD_Interface.h"
#include "timer.h"
#include "Timer1_Interface.h"
#include "SPI.h"
#include "RFID.h"
#include "Servo_Interface.h"
#include <stdio.h>

// ca b1 49 5b  blue
// e9 79 e9 b3  white

int main()
{
	lcd_init();
	Servo_vInit();
	uint8 index = 0;
	// const uint32 IDVALUE=0X495BCAB1;
	const uint32 IDVALUE = 0XE979E9B3;
	uint8 CardId[4] = {0, 0, 0, 0};
	uint8 Status_ID = 0;

	SPI_Init();
	begin();
	DIO_vSetPinDirection(PORTA, PIN4, OUTPUT);
	DIO_vSetPinDirection(PORTA, PIN5, OUTPUT);
	DIO_vSetPinDirection(PORTA, PIN6, OUTPUT);
	DIO_vSetPinDirection(PORTC, PIN6, OUTPUT);

	uint8 s1[2];
	uint8 s2[2];
	uint8 s3[2];
	uint8 s4[2];
	if (getFirmwareVersion() == 0x92)
	{
		DIO_vWritePin(PORTA, PIN4, HIGH);
		TIMER0_Delay_ms_with_Blocking(500);
		DIO_vWritePin(PORTA, PIN4, LOW);
		TIMER0_Delay_ms_with_Blocking(500);
	}
	//	while(1)
	//	{
	if (DetectCard())
	{
		DIO_vWritePin(PORTA, PIN5, HIGH);
		TIMER0_Delay_ms_with_Blocking(500);
		DIO_vWritePin(PORTA, PIN5, LOW);
		TIMER0_Delay_ms_with_Blocking(500);
		Status_ID = GetCardId(CardId);
		uint32 IDX = ((uint32)(CardId[3])) | ((uint32)(CardId[2]) << 8) | ((uint32)(CardId[1]) << 16) | ((uint32)(CardId[0]) << 24);
		if (IDX == IDVALUE)
		{
			// LCD_writeData('R');
			// LCD_writestring("RIGHT",0,0);
			DIO_vWritePin(PORTC, PIN6, HIGH);
			TIMER0_Delay_ms_with_Blocking(500);
			DIO_vWritePin(PORTC, PIN6, LOW);
			TIMER0_Delay_ms_with_Blocking(500);
			lcd_goto(LCD_LINE_1, LCD_COL_1);
			lcd_displayString("ID IS RIGHT");
			// lcd_clearAndHome();
			lcd_goto(LCD_LINE_3, LCD_COL_1);
			lcd_displayString("DOOR OPEN    ");

			Servo_vSetAngle(0);
			TIMER0_Delay_ms_with_Blocking(500);
			Servo_vSetAngle(90);
			TIMER0_Delay_ms_with_Blocking(500);
		}
		else
		{
			DIO_vWritePin(PORTC, PIN6, HIGH);
			TIMER0_Delay_ms_with_Blocking(500);
			DIO_vWritePin(PORTC, PIN6, LOW);
			TIMER0_Delay_ms_with_Blocking(500);
			DIO_vWritePin(PORTC, PIN6, HIGH);
			TIMER0_Delay_ms_with_Blocking(500);
			DIO_vWritePin(PORTC, PIN6, LOW);
			TIMER0_Delay_ms_with_Blocking(500);
			// LCD_writeData('W');
			// LCD_writestring("WRONG",0,0);
			lcd_goto(LCD_LINE_3, LCD_COL_1);
			lcd_displayString("ID IS WRONG    ");
		}
	}
	else if (!DetectCard())
	{
		DIO_vWritePin(PORTA, PIN6, HIGH);
		TIMER0_Delay_ms_with_Blocking(500);
		DIO_vWritePin(PORTA, PIN6, LOW);
		TIMER0_Delay_ms_with_Blocking(500);
	}
}
