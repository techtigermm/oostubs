/* $Id: io_port.h 956 2008-10-19 22:24:23Z hsc $ */

#ifndef __io_port_include__
#define __io_port_include__
#include "object/uint_templates.h"
/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              I O _ P O R T                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Diese Klasse dient dem Zugriff auf die Ein-/Ausgabe Ports des PCs. Beim   */
/* PC gibt es einen gesonderten I/O-Adressraum, der nur mittels der Maschi-  */
/* neninstruktionen 'in' und 'out' angesprochen werden kann. Ein IO_Port-    */
/* Objekt wird beim Erstellen an eine Adresse des I/O-Adressraums gebunden   */
/* und kann dann fuer byte- oder wortweise Ein- oder Ausgaben verwendet wer- */
/* den.                                                                      */
/*****************************************************************************/

/* BENUTZTE FUNKTIONEN */

extern "C" void outb  (uint16_t port, uint8_t value);
extern "C" void outw (uint16_t port, uint16_t value);
extern "C" void outl (uint16_t port, uint32_t value);
extern "C" uint8_t inb   (uint16_t port);
extern "C" uint16_t inw  (uint16_t port);
extern "C" uint32_t inl (uint16_t port);

/* KLASSENDEFINITION */

class IO_Port
 {
      // Kopieren erlaubt!

      // Adresse im I/O-Adressraum
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