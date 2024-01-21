/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         A P P L I C A T I O N                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The Application class defines the (only) application for OOStuBS.         */
/*****************************************************************************/

/* INCLUDES */

#include "user/appl.h"
#include "device/cgastr.h"
#include "machine/key.h"
#include "appl.h"
#include "machine/cpu.h"
#include "guard/secure.h"
#include "syscall/guarded_scheduler.h"
#include "syscall/guarded_keyboard.h"
#include "syscall/guarded_semaphore.h"
#include "user/loop.h"
#include "user/shellcommands.h"
#include "object/stdlib.h"
#include "strcmp.h"
#include "machine/pci.h"
#include "machine/ioport.h"
#include "machine/checkForDevices.h"
#include "device/devices.h"

/* GLOBAL VARIABLES */

extern CGA_Stream kout;
extern Guarded_Keyboard keyboard;
extern CPU cpu;
extern Guarded_Scheduler organizer;
extern Guarded_Semaphore semaphore;

/*Defines*/
#define BACKSPACE 8

// long stack1[1024];


//Kommandozeilenprogramm

void Application::action()
{
    argc = 0;
    bufferpos = 0;
    kout.getpos(x,y);
    // Loop loop1(stack1 + sizeof(stack1), 1);

    // organizer.ready(loop1);
    // for (;;)
    // {
    //     {
    //         Secure secure;
    //         kout.setpos(15, 15);
    //         kout << "test" << i++ << endl;
    //         kout.flush();
    //     }
    // }
    //test
    for (;;) {
        
        // semaphore.wait();
        kout.setpos(0, row);

//Source: https://github.com/LikeAnShadow/oostubs_changed/
//Einlesen der Tastatureingaben während der Laufzeit
    while (true) {
        if (printshell)
        {
            kout << "OOStubs Shell> "; //Anzeige Shellinfo
            kout.flush();
            kout.setpos(x+15,y); //verschiebe Cursor um Anzahl der Zeichen von Shellinfo
            kout.getpos(x,y);
            printshell = false;
        }
    Key key = keyboard.getkey();
    //char c = key.ascii();
    kout.setpos(x,y);
    if (bufferpos < BUFFERSIZE -1)
    {
        switch (key.ascii())
            {
            case BACKSPACE:
                if(bufferpos != 0){
                    kout.setpos(--x,y);
                    kout << ' ';
                    kout.flush();
                    kout.setpos(x,y);
                    --bufferpos;
                }/*else{                       //redundant?!
                    if(bufferpos != 0) {
                        kout.setpos(79, --y);
                        --bufferpos;
                    }
                } */ 
                if(y < 5){
                    kout.setpos(0,5);
                }
                break;
            case '\n':
                buffer[bufferpos] = '\0';
                kout.flush();
                commandParser(buffer);
                break;
            default:
                kout << key.ascii();
                buffer[bufferpos] = key.ascii();
                ++bufferpos;
                kout.flush();
                break;
            }
    } else if(key.ascii()=='\n'){
            buffer[bufferpos] = '\0';
            kout.flush();
            commandParser(buffer);
    }
    kout.getpos(x,y);
    //waiter.signal();
}
    }
}

void Application::commandParser(char* buffer){
    printshell = true;
    checkForSpaces(buffer, &argc, argv);
    kout.setpos(0,++y);
    kout.getpos(x,y);
    if (bufferpos == 0) {}
    
    else if(HELP) {
        kout << "help - Zeigt diese Hilfe an" << endl;
        kout << "---------------------------" << endl;
        kout << "reboot - Startet das System neu" << endl;
        kout << "---------------------------" << endl;
        kout << "shutdown - Faehrt das System herunter" << endl;
        kout << "---------------------------" << endl;
        kout << "tr - Taschenrechner; Moegliche Eingaben: tr x operand y " << endl;
        kout << "Operanden: +, -, *, / ; Trennung von Operand und Zahl mit Leerzeichen " << endl;
        kout << "x,y <= ? (maximale Groeße von Integern ist compilerabhängig)" << endl; //maximal vom Programm richtig verarbeitbare Größe eingegebener Zahl
        kout << "---------------------------" << endl;
        kout << "check - Information ueber PCI-Geraetekonfiguration" << endl;
        kout << "Eingabe: check <Bus> <Slot> <Funktion> <Offset>" << endl;
        kout << "---------------------------" << endl;
        //kout << "cioa - ?" << endl; Was macht das?
        //kout << "wioa - ?" << endl;
        //kout << "dhcpb - DHCP-Broadcast ... " << endl;
        kout.flush();
    }
    else if(REBOOT) {
        kout << "rebooting..." << endl;
        kout.flush();
        keyboard.reboot();
    }
    else if(SHUTDOWN) {
        kout << "power off..." << endl;
        //keyboard.shutdown();
        kout << "...muss noch implementiert werden..." << endl;
        kout << "...Abbruch" << endl;
        kout.flush();
    } 
    else if(TR) {
        int erg;
        if(argc == 4) {
            switch(argv[2][0]) {
                case '+':
                    erg = atoi(argv[1]) + atoi(argv[3]);
                    kout << "Ergebnis: " << erg << endl;
                    break;
                case '-':
                    erg = atoi(argv[1]) - atoi(argv[3]);
                    kout << "Ergebnis: " << erg << endl;
                    break;
                case '*':
                    erg = atoi(argv[1]) * atoi(argv[3]);
                    kout << "Ergebnis: " << erg << endl;
                    break;
                case '/':
                    erg = atoi(argv[1]) / atoi(argv[3]);
                    kout << "Ergebnis: " << erg << endl;
                    break;
                default:
                    kout << "Ungueltig!" << endl;
                    break;
            }
            kout.flush();
        }
    }
    else if (CHECK) {
        uint32_t fullDeviceID;
        if(argc != 5) {
            kout << "Ausfuehren mit: check <Bus> <Slot> <Funktion> <Offset>" << endl;
            kout.flush();
        } else {
        kout << "Vendor: " << hex << pciCheckVendor(atoi(argv[1]),atoi(argv[2]),atoi(argv[3])) << ", Device: " << pciCheckDevice(atoi(argv[1]), atoi(argv[2]), atoi(argv[3])) << dec << endl;
        kout << "Headertype: " << pciGetHeaderType(atoi(argv[1]), atoi(argv[2]), atoi(argv[3])) << endl;
        kout << "Offset-Ergebnis (16bit): " << hex << pciConfigReadWord(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4])) << " | " << dec << pciConfigReadWord(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4])) << endl;
        kout << "Offset-Ergebnis (32bit): " << hex << pciConfigReadLong(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4])) << " | " << dec << pciConfigReadLong(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4])) << endl;
        if((fullDeviceID = checkFullDevice(atoi(argv[1]), atoi(argv[2])) == 0x10EC8139)){
            kout << "Name des Geraetes: RTL8139" << endl;
            kout << "Verbunden: " << getDevice()->getConnected()<< endl;
        } else {
            kout << "Name des Geraetes: N/A" << endl;
        }
        kout.flush();
        }
    }
    else if(CHECKIOA) {
        if(argc != 2) {} 
        else{
            kout << hex << inl(atoi(argv[1])) << dec << endl;
        }
        kout.flush();
    } else if(WRITEIOA) {
        if(argc != 3) {} 
        else{
            outl(atoi(argv[1]), atoi(argv[2]));
        }
        kout.flush();
    }
     else if(DHCP_BROADCAST) {
        //HCP_Packet *packet = new DHCP_Packet(0x0,0xFFFFFFFF, 1, 1, 6, 1, 0,0,0,0,0,0);
        //kout << bp.getTotalLength()/8 <<endl;kout << "---------------------------" << endl;
        kout << "...muss noch implementiert werden..." << endl;
        kout << "...Abbruch" << endl;
        //kout.flush();
        //getDevice()->sendPacket((uint8_t*)(&bp), bp.getTotalLength()/8);

    }
    else {
        kout << "Diese Eingabe ist ungueltig!" << endl;
        kout.flush();
    }
    for(int i = bufferpos; i>-1;--i) {
        buffer[i] = 0;
    }
    bufferpos = 0;
}


void checkForSpaces(char* buffer, unsigned int* argc, char (* argv)[16]){
    int arr1 = 0;
    int arr2 = 0;
    *argc = 1;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 16;j++) {
            argv[i][j] = '\0';
        }
    }
    for(char *buf = buffer; *buf != '\0'; buf++) {
        
        if(*buf == ' ') {
            argv[arr1][arr2] = '\0';
            arr1++;
            *argc = *argc + 1;
            arr2 = 0;
        } else {
        argv[arr1][arr2] = *buf;
        arr2++;
        }
    }
}
