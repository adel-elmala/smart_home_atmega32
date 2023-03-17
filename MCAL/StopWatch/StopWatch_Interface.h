#ifndef STOPWATCH_INTERFACE_H
#define STOPWATCH_INTERFACE_H
#include "../../LIB/Datatypes.h"
typedef struct
{
    uint32 seconds;
    uint32 milli_seconds;
    uint32 u_seconds;
} StopWatch_t;

void StopWatch_Init();

void StopWatch_Start();
void StopWatch_Stop(StopWatch_t *clk);
void StopWatch_Snap(StopWatch_t *clk);

#endif