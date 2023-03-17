/**
 * @file Servo_Interface.h
 * @author Mohamed Elhusseiny
 * @brief  Servo Interface file
 * @version 0.1
 * @date 2023-03-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef     SERVO_INTERFACE_H
#define     SERVO_INTERFACE_H

/**
 * @brief Initialization for PWM
 * @note You need to change PWM Driver to enable any HAL Module to Choose A specific channel [A,B]
 */
void Servo_vInit(void);

/**
 * @brief This function well Set Servo Angle From 0 to 180 according to Copy_u8Angle value
 *        It Give the servo static Value of the angle
 * 
 * @param Copy_u8Angle Angle Value from 0 to 180
 */
void Servo_vSetAngle(uint8 Copy_u8Angle);


/**
 * @brief This function well Set Servo Angle From 0 to 180 according to Copy_u8Angle value
 *        It Give Servo Dynamic Rang to rotate on with spacific period
 * @note  Current wait is happening by busy wait , try to chang it by using timer interrupt.
 * 
 * @param Copy_u8AngleStart Min Angle Value 
 * @param Copy_u8AngleEnd   Max Angle Value 
 * @param Copy_PeriodMsec   Period for every step
 */
void Servo_vContinuousRotate(uint8 Copy_u8AngleStart , uint8 Copy_u8AngleEnd ,  uint16 Copy_PeriodMsec);


#endif