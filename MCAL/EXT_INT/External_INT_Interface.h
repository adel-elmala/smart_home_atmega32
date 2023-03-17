#ifndef EXTERNAL_INT_INTERFACE_H
#define EXTERNAL_INT_INTERFACE_H

#include "../../LIB/Datatypes.h"

typedef void (*interrupt_callback_t)(void);
// #define NULL ((void *)0)

/************* Modes ***********************/
// Modes that will be used for the external interrupt configuration
#define LOW_LEVEL_MODE 0
#define FALLING_EDGE_MODE 1
#define RISING_EDGE_MODE 2
#define FALLING_AND_RISING_EDGE_MODE 3

/********** Enable Ext Interrupts ***********/
#define ENABLE_INT0 6
#define ENABLE_INT1 7
#define ENABLE_INT2 5
#define DISABLE_INT 0

/********************************************/
#define Pin_Int0 2
#define Pin_Int1 3
#define Pin_Int2 2
#define GIE 7

// Struct that contains the external interrupt configuration options.
typedef struct
{
    uint8 Enable_INT0_Interrupt;
    uint8 Enable_INT1_Interrupt;
    uint8 Enable_INT2_Interrupt;
    uint8 INT0_Triggering_Mode;
    uint8 INT1_Triggering_Mode;
    uint8 INT2_Triggering_Mode;

} EXT_Int_Conf;
/*********** MCUCR PINS ****************/
#define ISC00 0
#define ISC01 1
#define ISC10 2
#define ISC11 3

/*********** MCUCSR PINS ****************/
#define ISC2 6

/*********** External Interrupt vectors ****************/

#define EXT_INT0 __vector_1
#define EXT_INT1 __vector_2
#define EXT_INT2 __vector_3

/*********** Interrupt service routine ****************/

#define ISR(vector)                                  \
    void vector(void) __attribute__((signal, used)); \
    void vector(void)

/*********** External_Interrupt APIS ****************/

void EXT_INT_SET_CONFIG(EXT_Int_Conf config);

void register_ext_int_callbacks(interrupt_callback_t int0_callback,
                                interrupt_callback_t int1_callback,
                                interrupt_callback_t int2_callback);
void EXT_INT_Disable(void); // disable interrupts
void EXT_INT_Enable(void);  // enable interrupts

#endif