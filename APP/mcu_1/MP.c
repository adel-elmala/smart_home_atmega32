#include "MP_Interface.h"
#include "MP_Private.h"

#include "../../HAL/FingerPrint/FP_Interface.h"
#include "../../HAL/RFID/RFID.h"
#include "../../HAL/OLED/OLED_Interface.h"
#include "../../HAL/LCD/LCD_Interface.h"
#include "../../HAL/LCD/LCD_Interface.h"
#include "../../HAL/UltraSonic/UltraSonic_Interface.h"
#include "../../HAL/UltraSonic/UltraSonic_Private.h"

#include "../../MCAL/SPI/SPI.h"
#include "../../MCAL/TIMER/timer.h"

#include <stdio.h>

uint16 g_distance = 0;
uint16 g_count = 0;

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
    DIO_vWritePin(SYS_ENABLE_PORT, SYS_ENABLE_PIN, LOW);
    DIO_vWritePin(SYS_SHUTDOWN_PORT, SYS_SHUTDOWN_PIN, LOW);

    DIO_vSetPinDirection(PORTC, PIN6, OUTPUT);
}

#if 1
uint8 MP_vUltrasonic_Person_State()
{
    uint16 current_distance;
    uint16 last_distance;

    last_distance = Ultrasonic_Read_Distance();
    TIMER0_Delay_ms_with_Blocking(100);
    current_distance = Ultrasonic_Read_Distance();

    if (current_distance < last_distance) // closing in
        return PERSON_ENTERING;

    else if (current_distance > last_distance) // moving away
        return PERSON_EXITING;

    else
        return PERSON_UNDEFINED;
}
#endif
#if 1
void MP_vUpdate_count_state_dist()
{
    g_distance = Ultrasonic_Read_Distance();
}
#endif
#if 1
void MP_vUpdate_count_state()
{
    uint8 person_state = MP_vUltrasonic_Person_State();
    if (person_state == PERSON_ENTERING)
        g_count++;
    else if (person_state == PERSON_EXITING)
        g_count--;

    if (g_count < 3)
    {
        // yellow led on
        DIO_vWritePin(PORTA, PIN6, HIGH);
        DIO_vWritePin(PORTA, PIN5, LOW);
        DIO_vWritePin(PORTA, PIN4, LOW);
    }

    else if ((g_count >= 3) && (g_count < 10))
    {
        // blue led on

        DIO_vWritePin(PORTA, PIN6, LOW);
        DIO_vWritePin(PORTA, PIN5, HIGH);
        DIO_vWritePin(PORTA, PIN4, LOW);
    }

    else
    {
        // green led on

        DIO_vWritePin(PORTA, PIN6, LOW);
        DIO_vWritePin(PORTA, PIN5, LOW);
        DIO_vWritePin(PORTA, PIN4, HIGH);
    }
}
#endif

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
    // const uint32 IDVALUE = 0X77f6f1d8;
    const uint32 IDVALUE = 0X73643d6;
    uint8 CardId[4] = {0, 0, 0, 0};
    uint8 Status_ID = 0;
    bool status = false;

    while (getFirmwareVersion() != 0x92)
        ;

    if (DetectCard())
    {
        lcd_displayString("Detected");
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
        status = false;
    }
    return status;
}
void MP_vUpdateSystem(bool fp, bool rfid, bool shutdown)
{
    if (rfid && fp)
    {
        DIO_vWritePin(SYS_ENABLE_PORT, SYS_ENABLE_PIN, HIGH);
        TIMER0_Delay_ms_with_Blocking(500);
        DIO_vWritePin(SYS_ENABLE_PORT, SYS_ENABLE_PIN, LOW);
        TIMER0_Delay_ms_with_Blocking(500);
    }
    else if (shutdown == true)
    {
        DIO_vWritePin(SYS_SHUTDOWN_PORT, SYS_SHUTDOWN_PIN, HIGH);
        TIMER0_Delay_ms_with_Blocking(500);
        DIO_vWritePin(SYS_SHUTDOWN_PORT, SYS_SHUTDOWN_PIN, LOW);
        TIMER0_Delay_ms_with_Blocking(500);
    }

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
        if (fp_status == true)
        {
            if (rfid_status == true)
            {
                MP_vUpdateSystem(fp_status, rfid_status, false);
                lcd_displayString("all done");
            }
            else
                rfid_status = MP_vRFID();
        }
        else
            fp_status = MP_vFingerPrint();

        lcd_displayString("ultra");
        MP_vUltraSonic();

        TIMER0_Delay_ms_with_Blocking(600);
        lcd_clearAndHome();
    }
}

void MP_vUltraSonic()
{
    char str[16] = {0};
    TIMER0_SetConfig();
    lcd_init();
    Ultrasonic_Init();

    if (g_count == 0)
        MP_vUpdateSystem(false, false, true);
    else
    {
        MP_vUpdate_count_state();
        sprintf(str, "%d", g_count);
        lcd_displayString(str);
        TIMER0_Delay_ms_with_Blocking(600);
        lcd_clearAndHome();
    }
}
