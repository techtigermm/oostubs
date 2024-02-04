/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                               L O C K E R                                 */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The Locker class implements a lock that can be used to protect critical   */
/* sections. However, the variable only indicates whether the critical       */
/* section is free. Potentially necessary waiting, and protection for        */
/* counting functionality, must be implemented elsewhere.                    */
/*****************************************************************************/

#ifndef __Locker_include__
#define __Locker_include__

#include "device/cgastr.h"

extern CGA_Stream kout;

class Locker
{
private:
	bool locked;

public:
	Locker(const Locker &copy) = delete; // prevent copying
	Locker() : locked(false) {}

	void enter()
	{
		if (locked)
		{
			kout << "Section entered twice" << endl;
		}
		locked = true;
	}

	void retne()
	{
		if (!locked)
		{
			kout << "Section not entered" << endl;
		}
		locked = false;
	}

	bool avail()
	{
		return !locked;
	}
};

#endif
