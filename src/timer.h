// Timer Service Library
// Jason Losh

//-----------------------------------------------------------------------------
// Hardware Target
//-----------------------------------------------------------------------------

// Target Platform: EK-TM4C123GXL
// Target uC:       TM4C123GH6PM
// System Clock:    40 MHz

// Hardware configuration:
// Timer 4

//-----------------------------------------------------------------------------
// Device includes, defines, and assembler directives
//-----------------------------------------------------------------------------

#ifndef TIMER_H_
#define TIMER_H_

//typedef void (*_callback)();
typedef void (*_callback_arg)(void *arg);

typedef struct
{
    _callback_arg fn;
    void *arg;
    uint32_t period;
    uint32_t ticks;
    bool reload;
} TimerEntry;

//-----------------------------------------------------------------------------
// Subroutines
//-----------------------------------------------------------------------------

void initTimer();
bool startOneshotTimer(_callback_arg callback, void* arg, uint32_t seconds);
bool startPeriodicTimer(_callback_arg callback, void *arg, uint32_t seconds);
bool restartTimer(_callback_arg callback);
void stopTimer(_callback_arg callback);
void tickIsr();
uint32_t random32();

#endif
