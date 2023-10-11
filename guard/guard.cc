#include "guard.h"
/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                G U A R D                                  */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Using this class, we can synchronize activities with a critical section   */
/* with interrupt handlers that also access this critical section. This      */
/* synchronization takes place along the prologue/epilogue model.            */
/*****************************************************************************/

#include "machine/cpu.h"

extern CPU cpu;

void Guard::leave()
{
    for (;;)
    {
        cpu.disable_int();
        gate = (Gate *)queue.dequeue();

        if (!gate)
            break;

        gate->queued(false);
        cpu.enable_int();
        gate->epilogue();
    }

    retne();
    cpu.enable_int();
}

void Guard::relay(Gate *item)
{
    if (item->queued())
        return;

    if (avail())
    {
        enter();
        cpu.enable_int();
        item->epilogue();
        leave();
    }
    else
    {
        item->queued(true);
        queue.enqueue(item);
    }
}
