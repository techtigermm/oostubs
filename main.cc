#include "device/cgastr.h"
#include "machine/keyctrl.h"
#include "machine/key.h"
#include "machine/pic.h"
#include "machine/cpu.h"
#include "machine/plugbox.h"
#include "guard/guard.h"
#include "syscall/guarded_organizer.h"
#include "device/watch.h"
#include "thread/scheduler.h"
#include "syscall/guarded_keyboard.h"
#include "syscall/guarded_semaphore.h"
#include "meeting/bellringer.h"
#include "user/idle.h"

#include "user/appl.h"
#include "user/loop.h"

CGA_Stream kout;
CPU cpu;
PIC pic;
Plugbox plugbox;
Guarded_Keyboard keyboard;
Guard guard;
Scheduler scheduler;
Guarded_Organizer organizer;
Guarded_Semaphore semaphore(0);
Watch watch(1000);
Bellringer bellringer;

long idle_stack[1024];
long app_stack[1024];
long app2_stack[1024];
long loop1_stack[1024];
long loop2_stack[1024];

Idle idle(idle_stack + sizeof(idle_stack));
Application app(app_stack + sizeof(app_stack), 0);
//Application app2(app2_stack + sizeof(app2_stack), 1);
Loop loop1(loop1_stack + sizeof(loop1_stack), 2, 10);
Loop loop2(loop2_stack + sizeof(loop2_stack), 3, 20);

int main()
{
	cpu.enable_int();
	keyboard.plugin();

	organizer.ready(app);
	//organizer.ready(app2);

	//organizer.ready(loop1);
	//organizer.ready(loop2);

	guard.enter();
	watch.windup();

	organizer.schedule();

	return 0;
}
