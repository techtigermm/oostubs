#include "watch.h"
/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              W A T C H                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Handles timer interrupts by managing a time slice and triggering a        */
/* process switch if necessary.                                              */
/*****************************************************************************/

#include "device/watch.h"
#include "machine/plugbox.h"
#include "machine/pic.h"
#include "syscall/guarded_organizer.h"
#include "device/cgastr.h"
#include "meeting/bellringer.h"

extern Plugbox plugbox;
extern PIC pic;
extern Guarded_Organizer organizer;
extern CGA_Stream kout;
extern Bellringer bellringer;

void Watch::windup()
{
    plugbox.assign(Plugbox::timer, *this);
    pic.allow(PIC::timer);
}

bool Watch::prologue()
{
    return true;
}

void Watch::epilogue()
{
    // kout.setpos(0, 24);
    // kout << "Ping";
    // kout.flush();

    bellringer.check();
    organizer.Scheduler::resume();
}
