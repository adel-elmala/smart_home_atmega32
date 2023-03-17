#include "Servo_Interface.h"
#include "Servo_Private.h"

#include "../MCAL/PWM/PWM_Interface.h"

double duty_cycle_per_degree = 0;

void SERVO_Init()
{
    PWM_Init();
    duty_cycle_per_degree = (double)(SERVO_MAX_DUTY_CYCLE - SERVO_MIN_DUTY_CYCLE) / (double)(SERVO_MAX_DEGREE - SERVO_MIN_DEGREE);
}
void SERVO_Turn(int degrees)
{
    // double duty_cycle = (degrees * duty_cycle_per_degree) + SERVO_NEUTRAL_DUTY_CYCLE;
    // duty_cycle = 255.0 * (duty_cycle / 100.0);
    // PWM_Generate_CHANNELA(duty_cycle, 50);
    PWM_Generate_CHANNELA(degrees, 50);
}
