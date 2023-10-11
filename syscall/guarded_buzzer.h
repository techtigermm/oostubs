/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         G U A R D E D _ B U Z Z E R                       */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The Guarded_Buzzer class implements the system call interface to the      */
/* Buzzer class.                                                             */
/*****************************************************************************/

#ifndef __Guarded_Buzzer_include__
#define __Guarded_Buzzer_include__

#include "meeting/buzzer.h"
#include "guard/secure.h"
class Guarded_Buzzer : public Buzzer
{

public:
	Guarded_Buzzer(const Guarded_Buzzer &copy); // prevent copying
	Guarded_Buzzer() {}
	virtual ~Guarded_Buzzer()
	{
		Secure sec;
		Buzzer::destroy();
	}

	void set(int ms)
	{
		Secure secure;
		Buzzer::set(ms);
	}

	void sleep()
	{
		Secure secure;
		Buzzer::sleep();
	}
};

#endif
