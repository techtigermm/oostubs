/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                  P I T                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Programmable Interval Timer.                                              */
/*****************************************************************************/

#ifndef __pit_include__
#define __pit_include__

#include "machine/io_port.h"

class PIT
{
private:
	IO_Port ctrl;
	IO_Port data;

	int inter;
public:
	PIT(const PIT &copy) = delete; // prevent copying
	PIT(int us) : ctrl(0x43), data(0x04)
	{
		interval(us);
	}
	int interval()
	{
		return inter;
	}
	void interval(int us);
};

#endif
