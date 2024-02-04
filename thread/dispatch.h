/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          D I S P A T C H E R                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Dispatcher implementation.                                                */
/* The Dispatcher maintains the life pointer that points to the currently    */
/* active coroutine. go() initializes the life pointer and starts the first  */
/* coroutine, all further context switches are triggered by dispatch().      */
/* active() returns the life pointer.                                        */
/*****************************************************************************/

#ifndef __dispatch_include__
#define __dispatch_include__

#include "thread/coroutine.h"

class Dispatcher
{
private:
	Coroutine *active_coroutine;

public:
	Dispatcher(const Dispatcher &copy) = delete; // prevent copying
	Dispatcher();
	void go(Coroutine &first);
	void dispatch(Coroutine &next);
	Coroutine *active();
};

#endif
