#include "pic.h"
/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                  P I C                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Programmable Interrupt Controller.                                        */
/* By using the PIC, hardware interrupts can be enabled or suppressed        */
/* individually. This way we can control whether interrupts of a specific    */
/* device are forwarded to the CPU at all. Even then, the interrupt handler  */
/* gets only activated if the CPU is ready to react to interrupts. This can  */
/* be controlled by using class CPU.                                         */
/*****************************************************************************/

void PIC::allow(int interrupt_device)
{
    if (interrupt_device < 8)
    {
        unsigned char mask = master.inb();
        mask &= ~(1 << interrupt_device);
        master.outb(mask);
    }
    else
    {
        unsigned char mask = slave.inb();
        mask &= ~(1 << (interrupt_device - 8));
        slave.outb(mask);
    }
}

void PIC::forbid(int interrupt_device)
{
    if (interrupt_device < 8)
    {
        unsigned char mask = master.inb();
        mask |= 1 << interrupt_device;
        master.outb(mask);
    }
    else
    {
        unsigned char mask = slave.inb();
        mask |= 1 << (interrupt_device - 8);
        slave.outb(mask);
    }
}

bool PIC::is_masked(int interrupt_device)
{
    if (interrupt_device < 8)
    {
        return master.inb() & (1 << interrupt_device);
    }
    else
    {
        return slave.inb() & (1 << (interrupt_device - 8));
    }

    return false;
}
