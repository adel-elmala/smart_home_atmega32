#include "MP_Interface.h"
#include "MP_Private.h"

#include "../../HAL/FingerPrint/FP_Interface.h"
#include "../../HAL/RFID/RFID.h"
#include "../../HAL/OLED/OLED_Interface.h"
#include "../../HAL/LCD/LCD_Interface.h"

#include "../../MCAL/SPI/SPI.h"
#include "../../MCAL/TIMER/timer.h"

// #include <stdio.h>

void MP_vInit_FIRST_TIME()
{
    TIMER0_SetConfig();
    lcd_init();
    // OLED_StoreFont();
    lcd_displayString("WAITING!");
    FP_Init();
    FP_Save_Finger_Print(1);
    FP_Save_Finger_Print(2);
    FP_Save_Finger_Print(3);
    FP_Save_Finger_Print(4);
}
void MP_vInit()
{
    TIMER0_SetConfig();
    lcd_init();
    OLED_vInit();
    OLED_ClearDisplay();
    SPI_Init();
    // RFID_INIT();
    FP_Init();

    DIO_vSetPinDirection(FAN_PORT, FAN_PIN, OUTPUT);
    DIO_vSetPinDirection(BUZZER_PORT, BUZZER_PIN, OUTPUT);

    // DIO_vSetPinDirection(PORTA, PIN4, OUTPUT);
    // DIO_vSetPinDirection(PORTA, PIN5, OUTPUT);
    // DIO_vSetPinDirection(PORTA, PIN6, OUTPUT);
    // DIO_vSetPinDirection(PORTC, PIN6, OUTPUT);
}

void MP_vFingerPrint()
{
    uint16 match_id = FP_Match_Finger_Print();
    if (match_id == 1)
        OLED_sendStr_xy((uint8 *)"Welcome Adel!", 2, 0);

    else if (match_id == 2)
        OLED_sendStr_xy((uint8 *)"Adel!", 2, 0);
    else if (match_id == 3)
        OLED_sendStr_xy((uint8 *)"hus!", 2, 0);

    else if (match_id == 4)
        OLED_sendStr_xy((uint8 *)"omar!", 2, 0);
    else
        OLED_sendStr_xy((uint8 *)"???", 2, 0);
}
#if 0
void MP_vRFID()
{
    uint8 index = 0;
    // const uint32 IDVALUE=0X495BCAB1;
    const uint32 IDVALUE = 0XE979E9B3;
    uint8 CardId[4] = {0, 0, 0, 0};
    uint8 Status_ID = 0;

    if (getFirmwareVersion() == 0x92)
    {
        DIO_vWritePin(PORTA, PIN4, HIGH);
        TIMER0_Delay_ms_with_Blocking(500);
        DIO_vWritePin(PORTA, PIN4, LOW);
        TIMER0_Delay_ms_with_Blocking(500);
    }

    if (DetectCard())
    {
        // lcd_displayString("det");

        DIO_vWritePin(PORTA, PIN5, HIGH);
        TIMER0_Delay_ms_with_Blocking(500);
        DIO_vWritePin(PORTA, PIN5, LOW);
        TIMER0_Delay_ms_with_Blocking(500);
        Status_ID = GetCardId(CardId);
        uint32 IDX = ((uint32)(CardId[3])) | ((uint32)(CardId[2]) << 8) | ((uint32)(CardId[1]) << 16) | ((uint32)(CardId[0]) << 24);
        if (IDX == IDVALUE)
        {
            DIO_vWritePin(PORTC, PIN6, HIGH);
            TIMER0_Delay_ms_with_Blocking(500);
            DIO_vWritePin(PORTC, PIN6, LOW);
            TIMER0_Delay_ms_with_Blocking(500);
            lcd_goto(LCD_LINE_1, LCD_COL_1);
            lcd_displayString("ID IS RIGHT");
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
#endif

void MP_vStart()
{
    // read temp
    MP_vInit();

    // fp , display state on oled
    MP_vFingerPrint();

    while (1)
    {
        // MP_vRFID();

        // update OLED
    }
}
