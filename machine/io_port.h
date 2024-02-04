#ifndef __io_port_include__
#define __io_port_include__
#include "object/uint_templates.h"

/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              I O _ P O R T                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* This class allows accesses to x86's I/O address space. This special       */
/* address space can only be accessed with the machine instructions 'in' and */
/* 'out'. An IO_Port object is bound to a specific I/O address (called       */
/* "port") at instantiation time and can then be used for byte- or word-wise */
/* input or output operations.                                               */
/*****************************************************************************/

/* USED FUNCTIONS */

extern "C" void outb  (uint16_t port, uint8_t value);
extern "C" void outw (uint16_t port, uint16_t value);
extern "C" void outl (uint16_t port, uint32_t value);
extern "C" uint8_t inb   (uint16_t port);
extern "C" uint16_t inw  (uint16_t port);
extern "C" uint32_t inl (uint16_t port);

/* CLASS DEFINITION */

class IO_Port {
	// copying is allowed

	// address in I/O address space ("port")
	uint16_t address;
   public:
      IO_Port (uint16_t a) : address (a) {};

      // OUTB: Byteweise Ausgabe eines Wertes ueber einen I/O-Port.
      void outb (uint8_t val) const
       { 
	      ::outb (address, val); 
       };

      // OUTW: Wortweise Ausgabe eines Wertes ueber einen I/O-Port.
      void outw (uint16_t val) const
       { 
	      ::outw (address, val); 
       };

      // OUTL: Longweise Ausgabe eines Wertes ueber einen I/O-Port.
      void outl (uint32_t val) const
       { 
	      ::outl (address, val); 
       };
      // INB: Byteweises Einlesen eines Wertes ueber einen I/O-Port.
      uint8_t inb () const
       { 
	      return ::inb (address); 
       };

      // INW: Wortweises Einlesen eines Wertes ueber einen I/O-Port.
      uint16_t inw () const
       { 
	       return ::inw (address); 
       };
             // INL: Longweises Einlesen eines Wertes ueber einen I/O-Port.
      uint32_t inl () const
       { 
	       return ::inl (address); 
       };
 };

#endif
