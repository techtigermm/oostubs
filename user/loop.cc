#include "loop.h"
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

#include "guard/secure.h"
#include "syscall/guarded_scheduler.h"
#include "syscall/guarded_buzzer.h"

// extern Guarded_Scheduler organizer;

Loop::Loop(void *tos, int row, int interval) : Thread(tos), row(row), interval(interval) {}

void Loop::action()
{
    Guarded_Buzzer buzzer;
    for (;;)
    {
        buzzer.set(interval);
        {
            Secure secure;
            kout.setpos(0, row);
            kout << "I'm Loop" << i++ << endl;
            kout.flush();
        }
        buzzer.sleep();
    }
}
