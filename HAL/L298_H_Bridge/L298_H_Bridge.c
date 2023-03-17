#include "../../MCAL/DIO/DIO_REG.h"
#include "../../MCAL/DIO/DIO_Interface.h"

// #define CORRECT_PHASE_PWM_MODE
// #define INVERTING_POLARITY

#include "../../MCAL/PWM/PWM_Interface.h"

#include "L298_H_Bridge_Interface.h"

// L298_H_Bridge_Config_t configuration = {
//     ENABLE_MOTOR_A,
//     DISABLE_MOTOR_B,
//     MOTOR_A_DIRECTION_INPUT_PORT,
//     MOTOR_A_DIRECTION_INPUT_1_PIN,
//     MOTOR_A_DIRECTION_INPUT_2_PIN,
//     MOTOR_B_DIRECTION_INPUT_3_PIN,
//     MOTOR_B_DIRECTION_INPUT_4_PIN
//     // MOTOR_A_PWM_PORT,
//     // MOTOR_A_PWM_PIN,
//     // MOTOR_B_PWM_PORT,
//     // MOTOR_B_PWM_PIN
// };
L298_H_Bridge_Config_t g_conf;
uint8 g_motor_a_dir;
uint8 g_motor_b_dir;
void L298_H_Bridge_init(L298_H_Bridge_Config_t conf)
{
    g_conf = conf;
    // init ports directions
    if (conf.enable_motor_a == ENABLE_MOTOR_A)
    {
        DIO_vSetPinDirection(conf.inputs_port, conf.input1_pin, OUTPUT);
        DIO_vSetPinDirection(conf.inputs_port, conf.input2_pin, OUTPUT);
    }
    if (conf.enable_motor_b == ENABLE_MOTOR_B)
    {
        DIO_vSetPinDirection(conf.inputs_port, conf.input3_pin, OUTPUT);
        DIO_vSetPinDirection(conf.inputs_port, conf.input4_pin, OUTPUT);
    }
    // init pwm
    PWM_Init();
}
void L298_H_Bridge_Motor_A_Speed_Control(uint8 duty_cycle, uint16 freqency)
{
    if (duty_cycle == 0)
    {
        // select an invalid direction -- stops the motor -- as stated in the datasheet
        DIO_vWritePin(g_conf.inputs_port, g_conf.input1_pin, LOW);
        DIO_vWritePin(g_conf.inputs_port, g_conf.input2_pin, LOW);
    }
    else
    {
        L298_H_Bridge_Motor_A_Direction_Control(g_motor_a_dir);
        PWM_Generate_CHANNELA(duty_cycle, freqency);
    }
}

void L298_H_Bridge_Motor_B_Speed_Control(uint8 duty_cycle, uint16 freqency)
{
    if (duty_cycle == 0)
    {
        // select an invalid direction -- stops the motor -- as stated in the datasheet
        DIO_vWritePin(g_conf.inputs_port, g_conf.input3_pin, LOW);
        DIO_vWritePin(g_conf.inputs_port, g_conf.input4_pin, LOW);
    }
    else
    {
        PWM_Generate_CHANNELB(duty_cycle, freqency);
        L298_H_Bridge_Motor_B_Direction_Control(g_motor_b_dir);
    }
}

void L298_H_Bridge_Motor_A_Direction_Control(uint8 move_forward)
{
    if (move_forward == MOTOR_DIRECTION_FORWARD)
    {
        DIO_vWritePin(g_conf.inputs_port, g_conf.input1_pin, HIGH);
        DIO_vWritePin(g_conf.inputs_port, g_conf.input2_pin, LOW);
        g_motor_a_dir = MOTOR_DIRECTION_FORWARD;
    }
    else
    {
        DIO_vWritePin(g_conf.inputs_port, g_conf.input1_pin, LOW);
        DIO_vWritePin(g_conf.inputs_port, g_conf.input2_pin, HIGH);
        g_motor_a_dir = MOTOR_DIRECTION_BACKWARD;
    }
}
void L298_H_Bridge_Motor_B_Direction_Control(uint8 move_forward)
{
    if (move_forward == MOTOR_DIRECTION_FORWARD)
    {
        DIO_vWritePin(g_conf.inputs_port, g_conf.input3_pin, HIGH);
        DIO_vWritePin(g_conf.inputs_port, g_conf.input4_pin, LOW);
        g_motor_b_dir = MOTOR_DIRECTION_FORWARD;
    }
    else
    {
        DIO_vWritePin(g_conf.inputs_port, g_conf.input3_pin, LOW);
        DIO_vWritePin(g_conf.inputs_port, g_conf.input4_pin, HIGH);
        g_motor_b_dir = MOTOR_DIRECTION_BACKWARD;
    }
}