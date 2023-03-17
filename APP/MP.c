#include "MP_Interface.h"
#include "MP_Private.h"
#include "../MCAL/PWM/PWM_Interface.h"
#include "../MCAL/TIMER/timer.h"
#include "../HAL/LCD/LCD_Interface.h"
#include "../HAL/LM35/LM35_Interface.h"
#include "../HAL/UltraSonic/UltraSonic_Interface.h"
#include "../HAL/OLED/OLED_Interface.h"
#include <stdio.h>

MP_Sys_State_t g_state = {0};
void MP_vInit()
{
    TIMER0_SetConfig();
    lcd_init();
    PWM_Init();
    LM35_vInit();
    Ultrasonic_Init();
    // OLED_StoreFont();
    OLED_vInit();
    OLED_ClearDisplay();

    DIO_vSetPinDirection(FAN_PORT, FAN_PIN, OUTPUT);
    DIO_vSetPinDirection(BUZZER_PORT, BUZZER_PIN, OUTPUT);
}
void MP_vMonitor_temprature(void)
{

    uint16 temp = LM35_u16GetReading_NotBLocking();
    // uint16 temp = LM35_u16GetReading();
    // update system-wide state
    g_state.temprature = temp;
#if 0
    // uint8 str[16] = {0};
    // sprintf(str, "%d", temp);
    // lcd_displayString(str);
    // TIMER0_Delay_ms_with_Blocking(400);
    // lcd_clearAndHome();
#endif
    if (temp < 30)
    {
        // if (temp < 30) --> continue
        DIO_vWritePin(FAN_PORT, FAN_PIN, LOW);
        DIO_vWritePin(BUZZER_PORT, BUZZER_PIN, LOW);
    }
    else if ((30 <= temp) && (temp < 40))
    {
        // if (30 < temp < 40) --> fan
        // TODO: change later to use motor driver
        DIO_vWritePin(FAN_PORT, FAN_PIN, HIGH);
        DIO_vWritePin(BUZZER_PORT, BUZZER_PIN, LOW);
    }
    else
    {
        // if (40 < temp) --> buzzer
        DIO_vWritePin(FAN_PORT, FAN_PIN, LOW);
        DIO_vWritePin(BUZZER_PORT, BUZZER_PIN, HIGH);
    }
    return;
}

#if 0
uint8 MP_vUltrasonic_Person_State()
{
    uint16 current_distance;
    uint16 last_distance;
    int is_closing_in = 0;
    int is_moving_away = 0;

    last_distance = Ultrasonic_Read_Distance();
#if 0
    uint8 str[16] = {0};
    sprintf(str, "%d", last_distance);
    lcd_displayString("distance: ");
    lcd_displayString(str);
    TIMER0_Delay_ms_with_Blocking(400);
    lcd_clearAndHome();
#endif
    for (int i = 0; i < 3; ++i)
    {
        current_distance = Ultrasonic_Read_Distance();
        if (current_distance < last_distance) // closing in
            is_closing_in++;
        else if (current_distance > last_distance) // moving away
            is_moving_away++;

        last_distance = current_distance;
        TIMER0_Delay_ms_with_Blocking(200);
    }

    if ((is_closing_in >= 2))
        return PERSON_ENTERING;
    else if ((is_moving_away >= 2))
        return PERSON_EXITING;
    else
        return PERSON_UNDEFINED;
}
#endif
#if 1
uint8 MP_vUltrasonic_Person_State()
{
    uint16 current_distance;
    uint16 last_distance;

    last_distance = Ultrasonic_Read_Distance();
    TIMER0_Delay_ms_with_Blocking(200);
    current_distance = Ultrasonic_Read_Distance();

    if (current_distance < last_distance) // closing in
        return PERSON_ENTERING;

    else if (current_distance > last_distance) // moving away
        return PERSON_EXITING;

    else
        return PERSON_UNDEFINED;
}
#endif

void MP_vUpdate_count_state()
{
    uint8 person_state = MP_vUltrasonic_Person_State();
    if (person_state == PERSON_ENTERING)
        g_state.n_person_in_house++;
    else if (person_state == PERSON_EXITING)
        g_state.n_person_in_house--;

    if (g_state.n_person_in_house < 3)
    {
        // yellow led on
        DIO_vWritePin(PORTA, PIN6, HIGH);
        DIO_vWritePin(PORTA, PIN5, LOW);
        DIO_vWritePin(PORTA, PIN4, LOW);
    }

    else if ((g_state.n_person_in_house >= 3) && (g_state.n_person_in_house < 10))
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
void MP_vStart()
{
    // read temp
    MP_vInit();
    uint8 counter = 0;
    while (1)
    {
        // monitor temp
        MP_vMonitor_temprature();

        // update OLED
        uint8 temp_line[16] = {0};
        sprintf(temp_line, "Temp: %d", g_state.temprature);
        OLED_sendStr_xy(temp_line, 0, 0);

        // ultrasonic counting people
        MP_vUpdate_count_state();
#if 1
        uint8 str[16] = {0};
        sprintf(str, "%d", g_state.n_person_in_house);
        lcd_displayString(str);
        TIMER0_Delay_ms_with_Blocking(500);
        lcd_clearAndHome();
#endif
        // fp , display state on oled
        // rfid + servo
        // push button shutsdown system
    }
}
