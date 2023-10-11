#include "keyboard.h"
/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            K E Y B O A R D                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Keyboard driver.                                                          */
/*****************************************************************************/

#include "machine/plugbox.h"
#include "machine/pic.h"
#include "device/cgastr.h"

extern Plugbox plugbox;
extern PIC pic;
extern CGA_Stream kout;

Keyboard::Keyboard() : key_read(false), sem(0)
{
}

void Keyboard::plugin()
{
    plugbox.assign(Plugbox::keyboard, *this);
    pic.allow(PIC::keyboard);
}

bool Keyboard::prologue()
{
    Key hit = key_hit();

    if (hit.ascii())
    {
        key = hit;
        return true;
    }


    if (key.valid() && key.ctrl() && key.alt() && key.scancode() == Key::scan::del)
    {
        kout.setpos(0, 24);
        kout << "Rebooting";
        kout.flush();
        reboot();
    }

    return false;
}

void Keyboard::epilogue()
{
    if (key_read)
    {
        key_read = false;
        // kout << "Waking up" << endl;
        sem.signal();
    }

    // if (key.valid())
    // {
    //     kout.setpos(0, 0);
    //     kout << key.ascii();
    //     kout.flush();
    // }
}

Key Keyboard::getkey()
{
    key_read = true;
    sem.wait();
    return key;
}

// void Keyboard::trigger()
// {
//     Key key = key_hit();

//     if (key.valid())
//     {
//         if (key.ctrl() && key.alt() && key.scancode() == Key::scan::del)
//             reboot();
//         else
//         {
//             kout.setpos(0, 0);
//             kout << key.ascii();
//             kout.flush();
//         }
//     }
// }
