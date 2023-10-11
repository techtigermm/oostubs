#include "pit.h"
/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                  P I T                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Programmable Interval Timer.                                              */
/*****************************************************************************/

void PIT::interval(int us)
{
    inter = us;

    int ns = 1000 * us;
    int interval = ns / 838;

    unsigned char low = interval & 0xFF;
    unsigned char high = interval >> 8;

    ctrl.outb(0x34);

    data.outb(low);
    data.outb(high);
}
