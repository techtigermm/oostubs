/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            K I C K O F F                                  */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Function to start a coroutine.                                            */
/* Since this function is not really called, but only jumped to by a clever  */
/* initialization of the stack of the coroutine, it must never terminate.    */
/* Otherwise a meaningless value would be interpreted as a return address    */
/* and the computer would crash.                                             */
/*****************************************************************************/

#include "thread/kickoff.h"
#include "thread/coroutine.h"
#include "thread/scheduler.h"
#include "guard/guard.h"
extern Guard guard;


extern Scheduler scheduler;

extern "C" void kickoff(void *dummy1, void *dummy2, void *dummy3, void *dummy4, void *dummy5, void *dummy6, void *object)
{
    guard.leave();   
    Coroutine *object_cpp = (Coroutine *)object;
    object_cpp->action();

    scheduler.exit();
}
