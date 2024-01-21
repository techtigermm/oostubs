; $Id: io_port.asm 8485 2017-03-27 11:50:06Z friesel $

;*****************************************************************************
;* Betriebssysteme                                                           *
;*---------------------------------------------------------------------------*
;*                                                                           *
;*                             I O _ P O R T                                 *
;*                                                                           *
;*---------------------------------------------------------------------------*
;* Die hier definierten Funktionen stellen die Maschinebefehle 'in' und      *
;* 'out' fuer die Klasse IO_Port zur Verfuegung.                             *
;*****************************************************************************

; EXPORTIERTE FUNKTIONEN

[GLOBAL outb]
[GLOBAL outw]
[GLOBAL outl]
[GLOBAL inb]
[GLOBAL inw]
[GLOBAL inl]
; IMPLEMENTIERUNG DER FUNKTIONEN

[SECTION .text]
	
; OUTB: Byteweise Ausgabe eines Wertes ueber einen I/O-Port.
;
;       C-Prototyp: void outb (int port, int value);

outb:
	push   rbp
	mov    rbp, rsp
	mov    rdx, rdi
	mov    rax, rsi
	out    dx, al
	pop    rbp
	ret

; OUTW: Wortweise Ausgabe eines Wertes ueber einen I/O-Port.
;
;       C-Prototyp: void outw (int port, int value);

outw:
	push   rbp
	mov    rbp, rsp
	mov    rdx, rdi
	mov    rax, rsi
	out    dx, ax
	pop    rbp
	ret

; OUTL: Longweise Ausgabe eines Wertes ueber einen I/O-Port.
;
;       C-Prototyp: void outl (int port, int value);

outl:
	push   rbp
	mov    rbp, rsp
	mov    rdx, rdi
	mov    rax, rsi
	out    dx, eax
	pop    rbp
	ret


; INB: Byteweises Einlesen eines Wertes ueber einen I/O-Port.
;
;      C-Prototyp: int inb (int port);

inb:
	push   rbp
	mov    rbp, rsp
	mov    rdx, rdi
	mov    rax, rsi
	in     al, dx
	pop    rbp
	ret

; INW: Wortweises Einlesen eines Wertes ueber einen I/O-Port.
;
;      C-Prototyp: int inw (int port);

inw:
	push   rbp
	mov    rbp, rsp
	mov    rdx, rdi
	mov    rax, rsi
	in     ax, dx
	pop    rbp
	ret

; INL: Longweises Einlesen eines Wertes ueber einen I/O-Port.
;
;      C-Prototyp: int inl (int port);

inl:
	push   rbp
	mov    rbp, rsp
	mov    rdx, rdi
	mov    rax, rsi
	in     eax, dx
	pop    rbp
	ret