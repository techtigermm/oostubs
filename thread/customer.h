/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         C U S T O M E R                                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The Customer class extends the Entrant class with the ability to record   */
/* and retrieve an event that the process in question is waiting for.        */
/*****************************************************************************/

#ifndef __customer_include__
#define __customer_include__

#include "meeting/waitingroom.h"
#include "thread/entrant.h"
#include "object/chain.h"

class Waitingroom;
class Customer : public Entrant
{
private:
	Waitingroom *room;

public:
	Customer(const Customer &copy); // prevent copying

	Customer(void *tos) : Entrant(tos), room(0) {};

	void waiting_in(Waitingroom *w) { room = w; };

	Waitingroom *waiting_in() { return room; };
};

#endif
