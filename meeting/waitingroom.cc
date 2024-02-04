/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                        W A I T I N G R O O M                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Implements a list of processes (Customer objects) that are all waiting    */
/* for a specific event.                                                     */
/*****************************************************************************/

#include "meeting/waitingroom.h"
#include "object/chain.h"
#include "thread/customer.h"
#include "syscall/guarded_organizer.h"

extern Guarded_Organizer organizer;

Waitingroom::~Waitingroom()
{
    Customer *customer;
    while (Chain *chain = dequeue())
    {
        customer = (Customer *)chain;
        organizer.Organizer::wakeup(*customer);
    }
}

void Waitingroom::remove(Customer *customer)
{
    Queue::remove(customer);
    organizer.Organizer::wakeup(*customer);
}