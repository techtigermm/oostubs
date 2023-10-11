/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         A P P L I C A T I O N                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The Application class defines the (only) application for OOStuBS.         */
/*****************************************************************************/

/* INCLUDES */

#include "user/appl.h"
#include "device/cgastr.h"
#include "machine/key.h"
#include "appl.h"
#include "machine/cpu.h"
#include "guard/secure.h"
#include "syscall/guarded_scheduler.h"
#include "syscall/guarded_keyboard.h"
#include "syscall/guarded_semaphore.h"

#include "user/loop.h"

/* GLOBAL VARIABLES */

extern CGA_Stream kout;
extern Guarded_Keyboard keyboard;
extern CPU cpu;
extern Guarded_Scheduler organizer;
extern Guarded_Semaphore semaphore;

// long stack1[1024];

void Application::action()
{
    // Loop loop1(stack1 + sizeof(stack1), 1);

    // organizer.ready(loop1);
    // for (;;)
    // {
    //     {
    //         Secure secure;
    //         kout.setpos(15, 15);
    //         kout << "test" << i++ << endl;
    //         kout.flush();
    //     }
    // }
    for (;;) {
        // kout << 'X' << endl;
        Key key = keyboard.getkey();
        // semaphore.wait();
        kout.setpos(0, row);
        kout << key.ascii();
        kout.flush();
        // semaphore.signal();
    }
}
