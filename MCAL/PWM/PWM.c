#include "PWM_Interface.h"
#include "PWM_Reg.h"
#include "../../LIB/Calcbit.h"

#define FAST_PWM_MODE
// #define CORRECT_PHASE_PWM_MODE
#define INVERTING_POLARITY
// #define NON_INVERTING_POLARITY
// #define F_CPU 16000000UL
void set_prescaler(uint16 prescaler);
void PWM_Init()
{
    // set WGM bits -- (DONE)
    //      select the mode that enables ICR1 to set the TOP -- (DONE)
#ifdef FAST_PWM_MODE
    // mode 14
    clearbit(TCCR1A, TCCR1A_WGM10);
    setbit(TCCR1A, TCCR1A_WGM11);
    setbit(TCCR1B, TCCR1B_WGM12);
    setbit(TCCR1B, TCCR1B_WGM13);

#else //(CORRECT_PHASE_PWM_MODE)
    // mode 10
    clearbit(TCCR1A, TCCR1A_WGM10);
    setbit(TCCR1A, TCCR1A_WGM11);
    clearbit(TCCR1B, TCCR1B_WGM12);
    setbit(TCCR1B, TCCR1B_WGM13);
#endif
}
void PWM_Generate_CHANNELA(uint8 Copy_u8DutyCycle, uint32 Copy_u32freq)
{
    // init the oc pin DIRECTION to be output pins -- (DONE)
    setbit(OC1A_DDRD, OC1A);

    // set COM bit for desired polarity -- (DONE)
#ifdef INVERTING_POLARITY
    setbit(TCCR1A, TCCR1A_COM1A0);
    setbit(TCCR1A, TCCR1A_COM1A1);
    // set the initail state of oc pins based on the polarity selected -- (DONE)
    clearbit(OC1A_PORTD, OC1A); // initially low then set at the first comp. match

#else // NON_INVERTING_POLARITY
    clearbit(TCCR1A, TCCR1A_COM1A0);
    setbit(TCCR1A, TCCR1A_COM1A1);
    // set the initail state of oc pins based on the polarity selected -- (DONE)
    setbit(OC1A_PORTD, OC1A); // initially high then cleared at the first comp. match

#endif

    uint16 max_top = 0xFFFF;
    uint16 prescaler;
    uint16 top; // icr
    uint16 ocr;
#ifdef FAST_PWM_MODE
    if (((F_CPU / (Copy_u32freq * PRESCALER_1)) - 1) <= max_top)
        prescaler = PRESCALER_1;
    else if (((F_CPU / (Copy_u32freq * PRESCALER_8)) - 1) <= max_top)
        prescaler = PRESCALER_8;
    else if (((F_CPU / (Copy_u32freq * PRESCALER_64)) - 1) <= max_top)
        prescaler = PRESCALER_64;
    else if (((F_CPU / (Copy_u32freq * PRESCALER_256)) - 1) <= max_top)
        prescaler = PRESCALER_256;
    else // if (((F_CPU / (Copy_u32freq * PRESCALER_1024)) - 1) <= max_top)
        prescaler = PRESCALER_1024;
    top = ((F_CPU / (Copy_u32freq * prescaler)) - 1);
#ifdef INVERTING_POLARITY
    // ocr = 1 - ((Copy_u8DutyCycle * (top + 1)) - 1);
    if (Copy_u8DutyCycle == 255) // max duty-cycle -- cannot be achived
        ocr = 0;
    else
        ocr = (((1 - ((double)Copy_u8DutyCycle / 255.0)) * (top + 1)) - 1);

#else // NON_INVERTING_POLARITY
    // ocr = (Copy_u8DutyCycle * (top + 1)) - 1;
    if (Copy_u8DutyCycle == 0)
        ocr = 0;
    else
        ocr = ((((double)Copy_u8DutyCycle / 255.0) * (top + 1)) - 1);

#endif

#else // CORRECT_PHASE_PWM_MODE
    if ((F_CPU / (Copy_u32freq * PRESCALER_1 * 2)) <= max_top)
        prescaler = PRESCALER_1;
    else if ((F_CPU / (Copy_u32freq * PRESCALER_8 * 2)) <= max_top)
        prescaler = PRESCALER_8;
    else if ((F_CPU / (Copy_u32freq * PRESCALER_64 * 2)) <= max_top)
        prescaler = PRESCALER_64;
    else if ((F_CPU / (Copy_u32freq * PRESCALER_256 * 2)) <= max_top)
        prescaler = PRESCALER_256;
    else // if (((F_CPU / (Copy_u32freq * PRESCALER_1024 * 2))) <= max_top)
        prescaler = PRESCALER_1024;
    top = (F_CPU / (Copy_u32freq * prescaler * 2));

#ifdef INVERTING_POLARITY
    // ocr = (1 - Copy_u8DutyCycle) * top;
    ocr = ((1 - ((double)Copy_u8DutyCycle / 255.0)) * top);

#else // NON_INVERTING_POLARITY
    // ocr = (Copy_u8DutyCycle * top);
    ocr = ((((double)Copy_u8DutyCycle / 255.0) * top));

#endif

#endif

    // set OCR1AH and OCR1AL  -- calc . OCR
    OCR1AH = (0xff00 & ocr) >> 8;
    OCR1AL = 0x00ff & ocr;
    // ICR1H and ICR1L -- calc TOP = ICR
    ICR1H = (0xff00 & top) >> 8;
    ICR1L = 0x00ff & top;

    // set the prescale bits -- calc. prescale
    set_prescaler(prescaler);
}
void PWM_Generate_CHANNELB(uint8 Copy_u8DutyCycle, uint32 Copy_u32freq)
{
    // init the oc pin DIRECTION to be output pins -- (DONE)
    setbit(OC1B_DDRD, OC1B);

#ifdef INVERTING_POLARITY
    // set COM bit for desired polarity -- (DONE)
    setbit(TCCR1A, TCCR1A_COM1B0);
    setbit(TCCR1A, TCCR1A_COM1B1);
    // set the initail state of oc pins based on the polarity selected -- (DONE)
    clearbit(OC1B_PORTD, OC1B); // initially low then set at the first comp. match

#else
    // set COM bit for desired polarity -- (DONE)
    clearbit(TCCR1A, TCCR1A_COM1B0);
    setbit(TCCR1A, TCCR1A_COM1B1);
    // set the initail state of oc pins based on the polarity selected -- (DONE)
    setbit(OC1B_PORTD, OC1B); // initially high then cleared at the first comp. match

#endif

    uint16 max_top = 0xFFFF;
    uint16 prescaler;
    uint16 top; // icr
    uint16 ocr;

#ifdef FAST_PWM_MODE
    if (((F_CPU / (Copy_u32freq * PRESCALER_1)) - 1) <= max_top)
        prescaler = PRESCALER_1;
    else if (((F_CPU / (Copy_u32freq * PRESCALER_8)) - 1) <= max_top)
        prescaler = PRESCALER_8;
    else if (((F_CPU / (Copy_u32freq * PRESCALER_64)) - 1) <= max_top)
        prescaler = PRESCALER_64;
    else if (((F_CPU / (Copy_u32freq * PRESCALER_256)) - 1) <= max_top)
        prescaler = PRESCALER_256;
    else // if (((F_CPU / (Copy_u32freq * PRESCALER_1024)) - 1) <= max_top)
        prescaler = PRESCALER_1024;
    top = ((F_CPU / (Copy_u32freq * prescaler)) - 1);
#ifdef INVERTING_POLARITY
    // ocr = 1 - ((((double)Copy_u8DutyCycle / 100.0) * (top + 1)) - 1);
    if (Copy_u8DutyCycle == 255) // max duty-cycle -- cannot be achived
        ocr = 0;
    else
        ocr = (((1 - ((double)Copy_u8DutyCycle / 255.0)) * (top + 1)) - 1);
#else // NON_INVERTING_POLARITY
    if (Copy_u8DutyCycle == 0)
        ocr = 0;
    else
        ocr = ((((double)Copy_u8DutyCycle / 255.0) * (top + 1)) - 1);

#endif

#else // CORRECT_PHASE_PWM_MODE
    if ((F_CPU / (Copy_u32freq * PRESCALER_1 * 2)) <= max_top)
        prescaler = PRESCALER_1;
    else if ((F_CPU / (Copy_u32freq * PRESCALER_8 * 2)) <= max_top)
        prescaler = PRESCALER_8;
    else if ((F_CPU / (Copy_u32freq * PRESCALER_64 * 2)) <= max_top)
        prescaler = PRESCALER_64;
    else if ((F_CPU / (Copy_u32freq * PRESCALER_256 * 2)) <= max_top)
        prescaler = PRESCALER_256;
    else // if (((F_CPU / (Copy_u32freq * PRESCALER_1024 * 2))) <= max_top)
        prescaler = PRESCALER_1024;
    top = (F_CPU / (Copy_u32freq * prescaler * 2));

#ifdef INVERTING_POLARITY
    ocr = ((1 - ((double)Copy_u8DutyCycle / 255.0)) * top);
#else // NON_INVERTING_POLARITY
    ocr = ((((double)Copy_u8DutyCycle / 255.0) * top));
#endif

#endif

    // set OCR1AH and OCR1AL  -- calc . OCR
    OCR1BH = (0xff00 & ocr) >> 8;
    OCR1BL = 0x00ff & ocr;
    // ICR1H and ICR1L -- calc TOP = ICR
    ICR1H = (0xff00 & top) >> 8;
    ICR1L = 0x00ff & top;

    // set the prescale bits -- calc. prescale
    set_prescaler(prescaler);
}

void set_prescaler(uint16 prescaler)
{
    switch (prescaler)
    {
    case PRESCALER_1:
    {
        setbit(TCCR1B, TCCR1B_CS10);
        clearbit(TCCR1B, TCCR1B_CS11);
        clearbit(TCCR1B, TCCR1B_CS12);
        break;
    }
    case PRESCALER_8:
    {
        clearbit(TCCR1B, TCCR1B_CS10);
        setbit(TCCR1B, TCCR1B_CS11);
        clearbit(TCCR1B, TCCR1B_CS12);
        break;
    }
    case PRESCALER_64:
    {
        setbit(TCCR1B, TCCR1B_CS10);
        setbit(TCCR1B, TCCR1B_CS11);
        clearbit(TCCR1B, TCCR1B_CS12);
        break;
    }
    case PRESCALER_256:
    {
        clearbit(TCCR1B, TCCR1B_CS10);
        clearbit(TCCR1B, TCCR1B_CS11);
        setbit(TCCR1B, TCCR1B_CS12);
        break;
    }
    case PRESCALER_1024:
    {
        setbit(TCCR1B, TCCR1B_CS10);
        clearbit(TCCR1B, TCCR1B_CS11);
        setbit(TCCR1B, TCCR1B_CS12);
        break;
    }

    default:
        break;
    }
}