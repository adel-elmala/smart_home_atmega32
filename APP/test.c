#include "test.h"
#include "../MCAL/TIMER/timer.h"
#include "../MCAL/DIO/DIO_Interface.h"
#include "../MCAL/DIO/DIO_REG.h"
// #include "../MCAL/PWM/PWM_Interface.h"
// #include "../MCAL/ADC/ADC_Interface.h"
#include "../MCAL/UART/UART_Interface.h"
// #include "../MCAL/SPI/SPI.h"
// #include "../MCAL/TWI/TWI_Interface.h"

// #include "../HAL/L298_H_Bridge/L298_H_Bridge_Interface.h"
#include "../HAL/LCD/LCD_Interface.h"
// #include "../HAL/Servo/Servo_Interface.h"

#include "../LIB/Queue/Queue.h"

#include "../HAL/FingerPrint/FP_Interface.h"
// #include "../HAL/RFID/RFID.h"
// #include "../MCAL/EEPROM/EEPROM_Interface.h"
// #include "../MCAL/StopWatch/StopWatch_Interface.h"
#include <stdio.h>
// #include "../HAL/UltraSonic/UltraSonic_Interface.h"

// bool g_trans_comp = false;
// void test_timer0()
// {

//     TIMER0_SetConfig();
//     DIO_vSetPortDirection(PORTB, OUTPUT);

//     while (1)
//     {

//         DIO_vWritePin(PORTB, PIN7, HIGH);
//         // TIMER0_Delay_ms_with_Blocking(1);
//         TIMER0_Delay_us_with_Blocking(100);

//         // TIMER0_Delay_MicroSeconds_with_Blocking(1);

//         DIO_vWritePin(PORTB, PIN7, LOW);
//         // TIMER0_Delay_ms_with_Blocking(1);
//         TIMER0_Delay_us_with_Blocking(100);

//         // TIMER0_Delay_MicroSeconds_with_Blocking(1);
//     }
// }

// // void test_pwm()
// // {
// //     PWM_Init();
// //     PWM_Generate_CHANNELA(128, 20000);
// //     PWM_Generate_CHANNELB(0, 20000);
// // }

// ADC_Config_t conf = {
//     // ADC_REFVOLTAGE_INTERNAL,
//     ADC_REFVOLTAGE_AVCC,
//     // ADC_REFVOLTAGE_VREF,
//     ADC_RIGHT_ADJUST,
//     ADC_SINGLE_ENDDED_ADC0,
//     ADC_DISABLE_INTR,
//     ADC_DISABLE_AUTOTRIGGER,
//     ADC_AUTO_TRIGGER_SOURCE_IGNORE};

// void test_adc()
// {
//     ADC_init(conf);
//     DIO_vSetPortDirection(PORTC, OUTPUT);
//     DIO_vSetPortDirection(PORTD, OUTPUT);

//     while (1)
//     {
//         uint8 low, high;
//         uint16 result = ADC_PollRead(&low, &high);

//         DIO_vWritePort(PORTC, (result & 0x00ff));
//         DIO_vWritePort(PORTD, ((result & 0xff00) >> 8));
//         // DIO_vWritePort(PORTC, low);
//         // DIO_vWritePort(PORTD, high);
//     }
// }

// L298_H_Bridge_Config_t dc_motor_configuration = {
//     ENABLE_MOTOR_A,
//     DISABLE_MOTOR_B,
//     MOTOR_A_DIRECTION_INPUT_PORT,
//     MOTOR_A_DIRECTION_INPUT_1_PIN,
//     MOTOR_A_DIRECTION_INPUT_2_PIN,
//     MOTOR_B_DIRECTION_INPUT_3_PIN,
//     MOTOR_B_DIRECTION_INPUT_4_PIN
//     //     // MOTOR_A_PWM_PORT,
//     //     // MOTOR_A_PWM_PIN,
//     //     // MOTOR_B_PWM_PORT,
//     //     // MOTOR_B_PWM_PIN
// };

// void test_motor()
// {
//     L298_H_Bridge_init(dc_motor_configuration);
//     L298_H_Bridge_Motor_A_Direction_Control(MOTOR_DIRECTION_FORWARD);
//     while (1)
//     {
//         L298_H_Bridge_Motor_A_Speed_Control(128, 20000);
//     }
// }

// UART_Config_t uart_conf = {9600,
//                            UART_DISABLE_DOUBLE_TRANSMISSION_SPEED,
//                            UART_DISABLE_MULTIPROCESSOR_COMMUNICATION_MODE,
//                            //    UART_ENABLE_RECEIVE_COMPLETE_INTERRUPT,
//                            UART_DISABLE_RECEIVE_COMPLETE_INTERRUPT,
//                            //    UART_ENABLE_TRANSMIT_COMPLETE_INTERRUPT,
//                            UART_DISABLE_TRANSMIT_COMPLETE_INTERRUPT,
//                            UART_DISABLE_DATA_REG_EMPTY_COMPLETE_INTERRUPT,
//                            UART_ENABLE_RECEIVER,
//                            UART_ENABLE_TRANSMITER,
//                            UART_8BIT_CHAR_SIZE,
//                            //    UART_EVEN_PARITY,
//                            UART_DISABLE_PARITY,
//                            UART_1_BIT_STOP};
// void test_uart()
// {
//     UART_vInit(uart_conf);
//     // UART_vTransmitString("HI from uart");

//     // lcd_init();

//     while (1)
//     {

//         // uint8 d = UART_u16Receive_no_poll();
//         uint8 d = UART_u16Receive_poll();
//         UART_vTransmit_poll(d);
//         // uint8 d = UART_u16Receive_no_poll();
//         // if (d == QUEUE_ERROR_EMPTY)
//         //     continue;
//         // else
//         //     UART_vTransmit_no_poll(d);
//     }
// }

// SPI_Config_t master_spi_conf = {
//     true,           // bool enable_interrupt;
//     true,           // bool enable_spi;
//     true,           // bool is_master;
//     false,          // bool double_speed;
//     CLK_HIGH_IDLE,  // uint8 clk_polarity;
//     SETUP_ON_FIRST, // uint8 clk_phase;
//     CLK_DIV_128,    // uint8 clk_divisor;
//     DORD_LSB_FIRST  // uint8 data_order;
// };
// SPI_Config_t slave_spi_conf = {
//     true,           // bool enable_interrupt;
//     true,           // bool enable_spi;
//     false,          // bool is_master;
//     false,          // bool double_speed;
//     CLK_HIGH_IDLE,  // uint8 clk_polarity;
//     SETUP_ON_FIRST, // uint8 clk_phase;
//     CLK_DIV_128,    // uint8 clk_divisor;
//     DORD_LSB_FIRST  // uint8 data_order;
// };
// // void trans_comp(void)
// // {
// //     g_trans_comp = true;
// // }
// void test_spi_master()
// {
//     // UART_vInit(uart_conf);
//     SPI_Init(&master_spi_conf);

//     uint8 counter = 0;
//     SPI_Transmit_Buffer_Async("adel refat ali", 16, NULL);
//     while (1)
//     {
//         // uint8 data = SPI_Transieve_Sync('z' - counter);
//         // SPI_Transmit_Async('z' - counter);
//         counter++;
//     }
// }

// void test_spi_slave()
// {
//     UART_vInit(uart_conf);
//     SPI_Init(&slave_spi_conf);

//     uint8 counter = 0;
//     while (1)
//     {

//         // TIMER0_Delay_ms_with_Blocking(1000);
//         // uint8 data = SPI_Transieve_Sync('A' + counter);
//         uint8 data = SPI_Receive_Async();
//         if (data != QUEUE_ERROR_EMPTY)
//             UART_vTransmit_no_poll(data);
//         counter++;
//     }
// }
// // // typedef struct TWI_Config
// TWI_Config_t twi_conf_mt = {

//     400000,          //     uint32 scl_freq;     // shouldn't exceed twi_max_scl supported
//     TWI_prescaler_4, //     uint8 scl_prescaler; // shouldn't exceed twi_max_scl supported
//     true,            //     bool enable_ack;
//     true,            //     bool enable_twi;
//     false,           //     bool enable_interrupt;
//     0x10,            //     uint8 own_slave_address;
//     false            //     bool enable_general_call;
// };
// TWI_Config_t twi_conf_sr = {

//     400000,          //     uint32 scl_freq;     // shouldn't exceed twi_max_scl supported
//     TWI_prescaler_4, //     uint8 scl_prescaler; // shouldn't exceed twi_max_scl supported
//     true,            //     bool enable_ack;
//     true,            //     bool enable_twi;
//     false,           //     bool enable_interrupt;
//     0x20,            //     uint8 own_slave_address;
//     false            //     bool enable_general_call;
// };
// void test_twi_mt_poll()
// {
//     lcd_init();
//     TWI_Init(twi_conf_mt);
//     // // TWI_Master_Transmit_Byte('a', twi_conf_sr.own_slave_address);
//     // // TWI_Master_Transmit_Buffer("adel here!", 11, twi_conf_sr.own_slave_address);

//     lcd_displayString("Master Ready!");
//     TIMER0_Delay_ms_with_Blocking(1000);
//     uint8 counter = 0;
//     while (1)
//     {
//         // uint8 byte = TWI_Master_Receive_Byte(twi_conf_sr.own_slave_address);
//         TWI_Master_Transmit_Byte('A' + (counter++), twi_conf_sr.own_slave_address);
//         // lcd_sendData(byte);

//         TIMER0_Delay_ms_with_Blocking(500);
//         // lcd_displayString("hello!");
//     }

//     // TWI_Master_Transmit_Byte('r', twi_conf_sr.own_slave_address);
// }

// void test_twi_sr_poll()
// {
//     lcd_init();

//     TWI_Init(twi_conf_sr);
//     uint8 counter = 0;
//     TIMER0_Delay_ms_with_Blocking(500);

//     lcd_displayString("Slave Ready!");
//     // TIMER0_Delay_ms_with_Blocking(1000);
//     while (1)
//     {
//         // TWI_Slave_Transmit_Byte('A' + (counter++));
//         uint8 byte = TWI_Slave_Receive_Byte();
//         lcd_sendData(byte);
//     }
// }

// #include <avr/eeprom.h>

// void test_eeprom_write()
// {
//     TIMER0_Delay_ms_with_Blocking(1000);
//     EEPROM_Write_Buffer("eeprom", 7, 0);
//     // EEPROM_Write_Byte('R', 10);
//     // eeprom_write_byte(20, 'R');

//     // lcd_init();
//     // lcd_displayString("hello");
//     while (1)
//         ;
// }

// void test_eeprom_read()
// {
//     lcd_init();
//     uint8 buff[] = "adel_Refat_Ali";
//     EEPROM_Read_Buffer(buff, 7, 0);
//     lcd_displayString(buff);
//     // uint8 data = EEPROM_Read_Byte(10);
//     // uint8 data = eeprom_read_byte(20);
//     // lcd_sendData(data);
//     // lcd_displayString("hi adel eeprom!!?");
//     while (1)
//         ;
// }
void test_fp()
{
    lcd_init();
    FP_Init();
    // lcd_displayString("READY");
    // lcd_displayString("init done");

    // uint8 status = FP_Verify_Password(9);
    uint8 thumb_id = 1;
    uint8 index_id = 2;
    uint8 middle_id = 3;
    FP_Save_Finger_Print(thumb_id);
    FP_Save_Finger_Print(index_id);
    FP_Save_Finger_Print(middle_id);
    // uint8 match_str[10] = {0};
    while (1)
    {

        uint16 match = FP_Match_Finger_Print();
        // sprintf((char *)match_str, "%d", match);
        lcd_sendData(match);
        TIMER0_Delay_ms_with_Blocking(3000);

        lcd_clearAndHome();
        switch (match)
        {
        case 1:
        {
            lcd_displayString("Thumb Finger");
            break;
        }

        case 2:
        {
            lcd_displayString("Index Finger");
            break;
        }

        case 3:
        {
            lcd_displayString("Middle Finger");
            break;
        }

        default:
        {
            lcd_displayString("No match");

            break;
        }
        }
        TIMER0_Delay_ms_with_Blocking(5000);
    }
}

// void test_servo()
// {
//     SERVO_Init();
//     lcd_init();
//     int counter = 0;
//     char str[5] = {0};
//     while (1)
//     {
//         sprintf(str, "%d", counter);
//         lcd_clearAndHome();
//         lcd_displayString(str);
//         SERVO_Turn(counter++);
//         TIMER0_Delay_ms_with_Blocking(1000);
//         if (counter > 255)
//             counter = 0;
//         // SERVO_Turn(-88);
//     }
// }

// void test_stopwatch()
// {
//     StopWatch_t clk;
//     uint8 str[12] = {0};

//     lcd_init();
//     TIMER0_SetConfig();
//     DIO_vSetPortDirection(PORTC, OUTPUT);

//     StopWatch_Init();
//     StopWatch_Start(&clk);

//     while (1)
//     {
//         TIMER0_Delay_ms_with_Blocking(3000);
//         StopWatch_Snap(&clk);
//         // DIO_vTogglePin(PORTC, PIN0);

//         lcd_clearAndHome();

//         sprintf(str, "%d", clk.seconds);
//         lcd_displayString("Sec: ");
//         lcd_displayString(str);

//         sprintf(str, "%d", clk.milli_seconds);
//         lcd_displayString("  mSec: ");
//         lcd_displayString(str);

//         lcd_goto_line2();
//         sprintf(str, "%d", clk.u_seconds);
//         lcd_displayString("uSec: ");
//         lcd_displayString(str);
//     }
// }

// void test_ultrasonic()
// {
//     TIMER0_SetConfig();
//     Ultrasonic_Init();
//     lcd_init();
//     char str[16] = {0};

//     while (1)
//     {
//         TIMER0_Delay_ms_with_Blocking(200);
//         uint16 distance = Ultrasonic_Read_Distance();
//         sprintf(str, "%d cm", distance);
//         lcd_clearAndHome();
//         lcd_displayString(str);
//     }
// }

// #include "../HAL/OLED/OLED_Interface.h"
// #include "../HAL/OLED/OLED_Private.h"
// void test_oled()
// {

//     lcd_init();
//     OLED_Init();
//     OLED_Send_Command(0x00);
//     while (1)
//     {
//         ;
//     }
// }
#if 0
void test_rfid()
{
    lcd_init();
    lcd_displayString("h");
    Servo_vInit();
    uint8 index = 0;
    // const uint32 IDVALUE=0X495BCAB1;
    const uint32 IDVALUE = 0XE979E9B3;
    uint8 CardId[4] = {0, 0, 0, 0};
    uint8 Status_ID = 0;
    lcd_displayString("e");

    lcd_displayString("l");
    SPI_Init();
    RFID_INIT();
    DIO_vSetPinDirection(PORTA, PIN4, OUTPUT);
    DIO_vSetPinDirection(PORTA, PIN5, OUTPUT);
    DIO_vSetPinDirection(PORTA, PIN6, OUTPUT);
    DIO_vSetPinDirection(PORTC, PIN6, OUTPUT);

    // uint8 s1[2];
    // uint8 s2[2];
    // uint8 s3[2];
    // uint8 s4[2];
    if (getFirmwareVersion() == 0x92)
    {
        DIO_vWritePin(PORTA, PIN4, HIGH);
        TIMER0_Delay_ms_with_Blocking(500);
        DIO_vWritePin(PORTA, PIN4, LOW);
        TIMER0_Delay_ms_with_Blocking(500);
    }
    lcd_displayString("o");

    while (1)
    {
        if (DetectCard())
        {
            lcd_displayString("det");

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
}
#endif