/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                               B U Z Z E R                                 */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* An "alarm clock" is a synchronization object that allows one or more      */
/* threads to put themselves to sleep for a specified time.                  */
/*****************************************************************************/

#include "meeting/buzzer.h"

void Buzzer::destroy()
{
    bellringer.cancel(this);
    Customer *customer = 0;
    while (customer = (Customer *)dequeue())
        organizer.Organizer::wakeup(*customer);
}

Buzzer::~Buzzer()
{
    destroy();
}

void Buzzer::ring()
{

    Customer *customer = nullptr;

    while (customer = (Customer *)dequeue())
    {
        remove(customer);
    }
}

void Buzzer::set(int ms)
{
    bellringer.cancel(this);
    bellringer.job(this, ms);
}

void Buzzer::sleep()
{
    if (wait() > 0)
    {
        Customer *customer = (Customer *)organizer.active();
        enqueue(customer);
        organizer.Organizer::block(*customer, *this);
    }
}
