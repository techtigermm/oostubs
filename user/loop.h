/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                 L O O P                                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Loop is a thread that does nothing else but count upwards and print this  */
/* on the screen. In between, it yields the CPU. The Scheduler then decides  */
/* which thread shall run next.                                              */
/*****************************************************************************/

#ifndef __loop_include__
#define __loop_include__

#include "syscall/thread.h"

class Loop : public Thread
{
private:
    int row;
    int i = 0;
    int interval;
public:
    Loop(void *tos, int row, int interval);
    void action();
};

#endif
