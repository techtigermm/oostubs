#include "scheduler.h"
/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          S C H E D U L E R                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Scheduler implementation.                                                 */
/*****************************************************************************/

#include "user/idle.h"

extern Idle idle;

void Scheduler::ready(Entrant &that)
{
    ready_list.enqueue(&that);
}

void Scheduler::schedule()
{
    Entrant *next = (Entrant *)ready_list.dequeue();
    if (next)
        dispatch(*next);
}

void Scheduler::exit()
{
    Entrant *next = (Entrant *)ready_list.dequeue();
    if (next)
        dispatch(*next);
    else
        dispatch(idle);
}

void Scheduler::kill(Entrant &that)
{
    Entrant *current = (Entrant *)active();
    if (&that == current)
        exit();
    ready_list.remove(&that);
}

void Scheduler::resume()
{
    Entrant *current = (Entrant *)active();

    if (current != &idle)
        ready_list.enqueue(current);

    current = (Entrant *)ready_list.dequeue();
    
    if (current)
        dispatch(*current);
    else
        dispatch(idle);
}
