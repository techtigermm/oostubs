#include "user/idle.h"
#include "machine/cpu.h"
#include "syscall/guarded_semaphore.h"

extern CGA_Stream kout;
extern CPU cpu;
extern Guarded_Semaphore semaphore;
 
inline void Idle::action()
{
    int i = 1;
    for (;;) {
        cpu.idle();
        // // semaphore.p();   //Q : don't need to  
        // //cout.setpos(15, 15);
		// cout << "idle" << i << endl;
        // i++;
        // // semaphore.v();
        // if (i > 100)
        //     i = 0;
    }
 
}