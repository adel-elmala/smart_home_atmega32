#include "MP_Interface.h"
#include "MP_Private.h"

#include "../../HAL/FingerPrint/FP_Interface.h"
#include "../../HAL/RFID/RFID.h"
#include "../../HAL/OLED/OLED_Interface.h"
#include "../../HAL/LCD/LCD_Interface.h"

#include "../../MCAL/SPI/SPI.h"
#include "../../MCAL/TIMER/timer.h"

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
    RFID_INIT();
    FP_Init();

    DIO_vSetPinDirection(SYS_ENABLE_PORT, SYS_ENABLE_PIN, OUTPUT);
    DIO_vSetPinDirection(SYS_SHUTDOWN_PORT, SYS_SHUTDOWN_PIN, OUTPUT);

    // rfid pins
    DIO_vSetPinDirection(PORTA, PIN4, OUTPUT);
    DIO_vSetPinDirection(PORTA, PIN5, OUTPUT);
    DIO_vSetPinDirection(PORTA, PIN6, OUTPUT);
    DIO_vSetPinDirection(PORTC, PIN6, OUTPUT);
}

bool MP_vFingerPrint()
{
    uint16 match_id = FP_Match_Finger_Print();
    bool result;
    if (match_id == 1)
    {
        OLED_sendStr_xy((uint8 *)"Welcome Adel!", 2, 0);
        result = true;
    }

    else if (match_id == 2)
    {
        OLED_sendStr_xy((uint8 *)"Welcome Adel!", 2, 0);
        result = true;
    }
    else if (match_id == 3)
    {
        OLED_sendStr_xy((uint8 *)"Welcome Husseny!", 2, 0);
        result = true;
    }
    else if (match_id == 4)
    {
        OLED_sendStr_xy((uint8 *)"Welcome Omar!", 2, 0);
        result = true;
    }
    else
    {
        OLED_sendStr_xy((uint8 *)"No Match!", 2, 0);
        result = false;
    }
    return result;
}

bool MP_vRFID()
{
    // const uint32 IDVALUE=0X495BCAB1;
    // const uint32 IDVALUE = 0XE979E9B3;
    const uint32 IDVALUE = 0X73643d6;
    // const uint32 IDVALUE = 0X77f6f1d8;
    uint8 CardId[4] = {0, 0, 0, 0};
    uint8 Status_ID = 0;
    bool status = false;
    // lcd_displayString("rfid");

    if (getFirmwareVersion() == 0x92)
    {
        DIO_vWritePin(PORTA, PIN4, HIGH);
        TIMER0_Delay_ms_with_Blocking(500);
        DIO_vWritePin(PORTA, PIN4, LOW);
        TIMER0_Delay_ms_with_Blocking(500);
    }

    // lcd_displayString("firwmare");

    if (DetectCard())
    {
        lcd_displayString("Detected");

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
            // TIMER0_Delay_ms_with_Blocking(500);
            lcd_goto(LCD_LINE_1, LCD_COL_1);
            lcd_displayString("ID IS RIGHT");
            lcd_goto(LCD_LINE_3, LCD_COL_1);
            lcd_displayString("DOOR OPEN");

            status = true;
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
            lcd_displayString("ID IS WRONG");
            status = false;
        }
    }
    else if (!DetectCard())
    {
        lcd_displayString("Not Detected");

        DIO_vWritePin(PORTA, PIN6, HIGH);
        TIMER0_Delay_ms_with_Blocking(500);
        DIO_vWritePin(PORTA, PIN6, LOW);
        TIMER0_Delay_ms_with_Blocking(500);
        status = false;
    }
    return status;
}
void MP_vUpdateSystem(bool fp_status, bool rfid_status)
{
    if (fp_status && rfid_status)
        DIO_vWritePin(SYS_ENABLE_PORT, SYS_ENABLE_PIN, HIGH);
    else
        DIO_vWritePin(SYS_ENABLE_PORT, SYS_ENABLE_PIN, LOW);
}
void MP_vStart()
{
    MP_vInit();

    bool fp_status = false;
    bool rfid_status = false;
    fp_status = MP_vFingerPrint();
    while (1)
    {
        if (fp_status)
        {
            if (rfid_status)
                MP_vUpdateSystem(fp_status, rfid_status);
            else
                rfid_status = MP_vRFID();
        }
        else
            fp_status = MP_vFingerPrint();

        TIMER0_Delay_ms_with_Blocking(200);
        lcd_clearAndHome();
    }
}
