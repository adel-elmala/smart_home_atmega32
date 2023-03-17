#ifndef L298_H_BRIDGE_INTERFACE_H
#define L298_H_BRIDGE_INTERFACE_H

#define MOTOR_A_DIRECTION_INPUT_PORT PORTC

#define MOTOR_DIRECTION_FORWARD 0
#define MOTOR_DIRECTION_BACKWARD 1

// Motor A
#define MOTOR_A_DIRECTION_INPUT_1_PIN PIN0 // l298-input1
#define MOTOR_A_DIRECTION_INPUT_2_PIN PIN1 // l298-input2

#define DISABLE_MOTOR_A 0
#define ENABLE_MOTOR_A 1

// #define MOTOR_A_PWM_PORT PORTD // timer1 pwm
// #define MOTOR_A_PWM_PIN PIN5   // channel A

// Motor B

#define MOTOR_B_DIRECTION_INPUT_3_PIN PIN2 // l298-input3
#define MOTOR_B_DIRECTION_INPUT_4_PIN PIN3 // l298-input4

#define DISABLE_MOTOR_B 0
#define ENABLE_MOTOR_B 1

// #define MOTOR_B_PWM_PORT PORTD // timer1 pwm
// #define MOTOR_B_PWM_PIN PIN4   // channel B

typedef struct L298_H_Bridge_Config
{
    uint8 enable_motor_a;
    uint8 enable_motor_b;
    uint8 inputs_port;
    uint8 input1_pin;
    uint8 input2_pin;
    uint8 input3_pin;
    uint8 input4_pin;
    // uint8 pwm1_port;
    // uint8 pwm1_pin;
    // uint8 pwm2_port;
    // uint8 pwm2_pin;
} L298_H_Bridge_Config_t;

void L298_H_Bridge_init(L298_H_Bridge_Config_t conf);
void L298_H_Bridge_Motor_A_Speed_Control(uint8 duty_cycle, uint16 freqency);
void L298_H_Bridge_Motor_B_Speed_Control(uint8 duty_cycle, uint16 freqency);
void L298_H_Bridge_Motor_A_Direction_Control(uint8 move_forward);
void L298_H_Bridge_Motor_B_Direction_Control(uint8 move_forward);

#endif