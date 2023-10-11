#include "plugbox.h"
/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              P L U G B O X                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Abstracts an interrupt vector table. Allows to configure handler routines */
/* for every hardware and software interrupt and every CPU exception.        */
/*****************************************************************************/

#include "device/panic.h"

Panic panic;

Plugbox::Plugbox()
{
    for (int i = 0; i < 64; i++) {

    }
}

void Plugbox::assign(unsigned int slot, Gate &gate)
{
    if (slot >= 64) panic.prologue();
    else gates[slot] = &gate;
}

Gate &Plugbox::report(unsigned int slot)
{
    if (slot >= 64) panic.prologue();
    else return *gates[slot];
}
