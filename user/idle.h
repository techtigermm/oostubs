#ifndef __idle_include__
#define __idle_include__

/* Add your code here */ 
 
#include "device/cgastr.h"
#include "thread/entrant.h"
#include "syscall/thread.h"

class Idle: public Thread
{
private:
	Idle (const Idle &copy); // prevent copying

public:
	Idle (void* tos):  Thread(tos){}
	void action ();
};

#endif