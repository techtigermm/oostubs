/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                           S E M A P H O R E                               */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The class Semaphore implements the synchronization concept of the         */
/* counting semaphore.                                                       */
/*****************************************************************************/

#include "meeting/semaphore.h"
#include "syscall/guarded_organizer.h"
#include "device/cgastr.h"

extern Guarded_Organizer organizer;
extern CGA_Stream kout;

void Semaphore::p()
{
    if (counter > 0)
        counter--;
    else
        organizer.Organizer::block(*(Customer *)organizer.active(), *this);
}

void Semaphore::v()
{
    if (Chain *chain = dequeue())
    {
        // kout << "Waiting up";
        // kout.flush();
        organizer.Organizer::wakeup(*(Customer *)(chain));
    }
    else
        counter++;
}
