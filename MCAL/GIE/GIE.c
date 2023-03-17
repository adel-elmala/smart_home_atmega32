#include "GIE_Interface.h"
#include "GIE_REG.h"
#include "../../LIB/Calcbit.h"
#include "../../LIB/Datatypes.h"

#ifndef __GNUC__
#define __asm__ asm
#endif

void _cli(void)
{
    __asm__("cli\n\t");
}
void _sei(void)
{
    __asm__("sei\n\t");
}

void cli(void)
{
    clearbit(SREG, SREG_GIE);
}
void sei(void)
{
    setbit(SREG, SREG_GIE);
}