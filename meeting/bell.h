/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                 B E L L                                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Bell is an abstract base class that allows the time-controlled triggering */
/* of an activity. For this purpose, it has an internal counter that is      */
/* managed by the Bellringer.                                                */
/*****************************************************************************/

#ifndef __Bell_include__
#define __Bell_include__

#include "object/chain.h"

class Bell : public Chain
{
private:
	int counter;

public:
	Bell(const Bell &copy) = delete; // prevent copying
	Bell() : counter(0) {}

	void wait(int value)
	{
		counter = value;
	}

	int wait()
	{
		return counter;
	}

	void tick()
	{
		--counter;
	}

	bool run_down()
	{
		if (counter <= 0)
			return true;
		return false;
	}

	virtual void ring() = 0;
};

#endif
