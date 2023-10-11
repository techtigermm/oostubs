/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         A P P L I C A T I O N                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The Application class defines the (only) application for OOStuBS.         */
/*****************************************************************************/

#ifndef __application_include__
#define __application_include__

#include "syscall/thread.h"

class Application : public Thread
{
private:
	int i = 0;
	int row;

public:
	Application(const Application &copy) = delete; // prevent copying
	Application(void *tos, int row) : Thread(tos), row(row) {}

	void action();
};

#endif
