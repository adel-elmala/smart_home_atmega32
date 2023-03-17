/**
 * @file Servo_Prog.c
 * @author Mohamed Elhusseiny
 * @brief  Servo Implementation file
 * @date 2023-03-11
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../LIB/Datatypes.h"
#include "../../LIB/Calcbit.h"
// #include "../../MCAL/Timer/Timer1/Timer1_Interface.h"
#include "../../MCAL/PWM/PWM_Interface.h"
// #include "../../MCAL/Timer/Timer0/Timer0_Interface.h"
#include "../../MCAL/TIMER/timer.h"
#include "./Servo_Interface.h"

#define SERVO_FREQ 50

/**
 * @brief Initialization for PWM
 * @note You need to change PWM Driver to enable any HAL Module to Choose A specific channel [A,B]
 */
void Servo_vInit(void)
{
    /// Init PWM Module with spacific channal
    // PWM_vInit();
    PWM_Init();
}

/**
 * @brief This function well Set Servo Angle From 0 to 180 according to Copy_u8Angle value
 *        It Give the servo static Value of the angle
 *
 * @param Copy_u8Angle Angle Value from 0 to 180
 */
void Servo_vSetAngle(uint8 Copy_u8Angle)
{
    /// Take duty value from 0 to 255
    uint16 MapingValue;
    MapingValue = ((3 * Copy_u8Angle) / 18) + 6;
    // PWM_vGenerateCHA(MapingValue, SERVO_FREQ);
    PWM_Generate_CHANNELA(MapingValue, SERVO_FREQ);
}

/**
 * @brief This function well Set Servo Angle From 0 to 180 according to Copy_u8Angle value
 *        It Give Servo Dynamic Rang to rotate on with spacific period
 * @note  Current wait is happening by busy wait , try to chang it by using timer interrupt.
 *
 * @param Copy_u8AngleStart Min Angle Value
 * @param Copy_u8AngleEnd   Max Angle Value
 * @param Copy_PeriodMsec   Period for every step
 */
void Servo_vContinuousRotate(uint8 Copy_u8AngleStart, uint8 Copy_u8AngleEnd, uint16 Copy_PeriodMsec)
{
    for (uint8 CurrAngle = Copy_u8AngleStart; CurrAngle <= Copy_u8AngleEnd; CurrAngle++)
    {
        Servo_vSetAngle(CurrAngle);
        // Timer0_vDelay_Milli_with_Blocking(Copy_PeriodMsec);
        TIMER0_Delay_ms_with_Blocking(Copy_PeriodMsec);
    }
    for (uint8 CurrAngle = Copy_u8AngleEnd; CurrAngle >= Copy_u8AngleStart; CurrAngle--)
    {
        Servo_vSetAngle(CurrAngle);
        // Timer0_vDelay_Milli_with_Blocking(Copy_PeriodMsec);
        TIMER0_Delay_ms_with_Blocking(Copy_PeriodMsec);
    }
}
