#include "dispatch.h"
/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          D I S P A T C H E R                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Dispatcher implementation.                                                */
/* The Dispatcher maintains the life pointer that points to the currently    */
/* active coroutine. go() initializes the life pointer and starts the first  */
/* coroutine, all further context switches are triggered by dispatch().      */
/* active() returns the life pointer.                                        */
/*****************************************************************************/

Dispatcher::Dispatcher() : active_coroutine(0) {}

void Dispatcher::go(Coroutine &first)
{
    active_coroutine = &first;
    active_coroutine->go();
}

void Dispatcher::dispatch(Coroutine &next)
{
    Coroutine *current = active_coroutine;
    active_coroutine = &next;
    current->resume(next);
}

Coroutine *Dispatcher::active()
{
    return active_coroutine;
}
