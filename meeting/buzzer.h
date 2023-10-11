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

#ifndef __Buzzer_include__
#define __Buzzer_include__

#include "meeting/waitingroom.h"
#include "meeting/bell.h"
#include "meeting/bellringer.h"
#include "syscall/guarded_organizer.h"

extern Guarded_Organizer organizer;
extern Bellringer bellringer;

class Buzzer : public Bell, public Waitingroom
{
private:
public:
	Buzzer(const Buzzer &copy); // prevent copying

	Buzzer() {}

	void destroy();
	virtual ~Buzzer();
	virtual void ring();
	void set(int ms);
	void sleep();
};

#endif
