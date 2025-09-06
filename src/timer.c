// Timer Service Library
// Jason Losh

// Omar Elsaghir
// ID: 1001768494
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

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "timer.h"

//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------

#define NUM_TIMERS 10

//-----------------------------------------------------------------------------
// Subroutines
//-----------------------------------------------------------------------------

TimerEntry timers[NUM_TIMERS];

void initTimer()
{
    uint8_t i;

    // Enable clocks
    SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R4;
    _delay_cycles(3);

    // Configure Timer 4 for 1 sec tick
    TIMER4_CTL_R &= ~TIMER_CTL_TAEN;                // Turn off timer before reconfiguring
    TIMER4_CFG_R = TIMER_CFG_32_BIT_TIMER;          // Configure as 32-bit timer (A+B)
    TIMER4_TAMR_R = TIMER_TAMR_TAMR_PERIOD;         // Configure for periodic mode (count down)
    TIMER4_TAILR_R = 40000000;                      // Set load value (1 Hz rate)
    TIMER4_CTL_R |= TIMER_CTL_TAEN;                 // Turn-on timer
    TIMER4_IMR_R |= TIMER_IMR_TATOIM;               // Enable interrupt
    NVIC_EN2_R |= 1 << (INT_TIMER4A - 80);          // Enable interrupt 86 (TIMER4A)

    // Initialize timers
    for (i = 0; i < NUM_TIMERS; i++)
    {
        timers[i].fn = NULL;
        timers[i].arg = NULL;
        timers[i].period = 0;
        timers[i].ticks = 0;
        timers[i].reload = false;
    }
}

bool startPeriodicTimer(_callback_arg callback, void *arg, uint32_t seconds)
{
    uint8_t i;
    for (i = 0; i < NUM_TIMERS; i++)
    {
        if (timers[i].fn == NULL)  // Find an empty slot
        {
            timers[i].fn = callback;
            timers[i].arg = arg;
            timers[i].period = seconds;
            timers[i].ticks = seconds;
            timers[i].reload = true;  // Periodic timer should reload
            return true;
        }
    }
    return false; // No available timer slots
}

bool startOneshotTimer(_callback_arg callback, void *arg, uint32_t seconds)
{
    uint8_t i;
    for (i = 0; i < NUM_TIMERS; i++)
    {
        if (timers[i].fn == NULL)  // Find an empty slot
        {
            timers[i].fn = callback;
            timers[i].arg = arg;
            timers[i].period = seconds;
            timers[i].ticks = seconds;
            timers[i].reload = false;  // One-shot timers do not reload
            return true;
        }
    }
    return false;
}

bool restartTimer(_callback_arg callback)
{
    uint8_t i;
    for (i = 0; i < NUM_TIMERS; i++)
    {
        if (timers[i].fn == callback)
        {
            timers[i].ticks = timers[i].period;
            return true;
        }
    }
    return false;  // Timer not found
}

void stopTimer(_callback_arg callback)
{
    uint8_t i;
    for (i = 0; i < NUM_TIMERS; i++)
    {
        if (timers[i].fn == callback)
        {
            timers[i].fn = NULL;
            timers[i].arg = NULL;
            timers[i].ticks = 0;
            timers[i].period = 0;
            timers[i].reload = false;
        }
    }
}

// Timer Interrupt Service Routine (ISR)
void tickIsr()
{
    uint8_t i;
    for (i = 0; i < NUM_TIMERS; i++)
    {
        if (timers[i].ticks != 0)  // If the timer is running
        {
            timers[i].ticks--;
            if (timers[i].ticks == 0)  // Timer expired
            {
                if (timers[i].reload)
                    timers[i].ticks = timers[i].period;  // Reload timer

                if (timers[i].fn)  // Call the callback with argument
                    timers[i].fn(timers[i].arg);
            }
        }
    }
    TIMER4_ICR_R = TIMER_ICR_TATOCINT; // Clear interrupt
}

// Placeholder random number function
uint32_t random32()
{
    return TIMER4_TAV_R;
}

