#include "UltraSonic_Interface.h"
#include "UltraSonic_Private.h"

#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../MCAL/EXT_INT/External_INT_Interface.h"
#include "../../MCAL/StopWatch/StopWatch_Interface.h"
#include "../../MCAL/TIMER/timer.h"

EXT_Int_Conf ultrasonic_rising_intr_conf = {
    ENABLE_INT0,      // uint8 Enable_INT0_Interrupt;
    DISABLE_INT,      // uint8 Enable_INT1_Interrupt;
    DISABLE_INT,      // uint8 Enable_INT2_Interrupt;
    RISING_EDGE_MODE, // uint8 INT0_Triggering_Mode;
    RISING_EDGE_MODE, // uint8 INT1_Triggering_Mode;
    RISING_EDGE_MODE  // uint8 INT2_Triggering_Mode;
};

EXT_Int_Conf ultrasonic_failing_intr_conf = {
    ENABLE_INT0,       // uint8 Enable_INT0_Interrupt;
    DISABLE_INT,       // uint8 Enable_INT1_Interrupt;
    DISABLE_INT,       // uint8 Enable_INT2_Interrupt;
    FALLING_EDGE_MODE, // uint8 INT0_Triggering_Mode;
    FALLING_EDGE_MODE, // uint8 INT1_Triggering_Mode;
    FALLING_EDGE_MODE  // uint8 INT2_Triggering_Mode;
};
static bool g_rising_edge_detected = false;
StopWatch_t stopwatch = {0};

void Ultrsonic_callback(void)
{
    if (g_rising_edge_detected)
    {
        g_rising_edge_detected = false;
        EXT_INT_SET_CONFIG(ultrasonic_rising_intr_conf);
        // update time
        StopWatch_Stop(&stopwatch);
    }
    else
    {
        g_rising_edge_detected = true;
        EXT_INT_SET_CONFIG(ultrasonic_failing_intr_conf);
        StopWatch_Start();
    }
}
void Ultrasonic_Init()
{
    // TIMER0_SetConfig();
    StopWatch_Init();
    DIO_vSetPinDirection(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN, OUTPUT);
    DIO_vSetPinDirection(ULTRASONIC_ECHO_PORT, ULTRASONIC_ECHO_PIN, INPUT);
    EXT_INT_SET_CONFIG(ultrasonic_rising_intr_conf);
    register_ext_int_callbacks(Ultrsonic_callback, NULL, NULL);
}
void Ultrasonic_trigger()
{
    DIO_vWritePin(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN, HIGH);
    TIMER0_Delay_us_with_Blocking(10);
    DIO_vWritePin(ULTRASONIC_TRIGGER_PORT, ULTRASONIC_TRIGGER_PIN, LOW);
}
#include "stdio.h"
uint16 Ultrasonic_Read_Distance(void)
{
    Ultrasonic_trigger();
    StopWatch_t clk = stopwatch;
    const double velocity = 343.0;
    double time = (double)clk.seconds + ((double)clk.milli_seconds / 1000.0) + ((double)clk.u_seconds / 1000000.0);

    double distance = ((velocity * time) / 2.0) * 100.0;

    return (uint16)distance;
}
