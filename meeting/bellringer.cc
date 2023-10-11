/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          B E L L R I N G E R                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The "bell ringer" (Bellringer) is activated periodically and checks if    */
/* any "bells" (Bell objects) need to ring. The bells are in a list that the */
/* bellringer manages.                                                       */
/*****************************************************************************/

#include "meeting/bellringer.h"

void Bellringer::check()
{
    Bell *tmp = (Bell *)first();

    Bell *del = nullptr;

    while (tmp)
    {
        tmp->tick();
        if (tmp->run_down())
        {
            tmp->ring();
            del = tmp;
            tmp = (Bell *)tmp->next;
            remove(del);
            continue;
        }
        tmp = (Bell *)tmp->next;
    }
}

void Bellringer::job(Bell *bell, int ticks)
{
    bell->wait(ticks);
    enqueue(bell);
}

void Bellringer::cancel(Bell *bell)
{
    remove(bell);
}