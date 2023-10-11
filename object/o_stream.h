/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            O _ S T R E A M                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The O_Stream class defines the << operator for several pre-defined data   */
/* types and thereby realizes output functionality similar to C++'s iostream */
/* library. By default, this class supports printing characters, strings and */
/* integer numbers of various bit sizes. Another << operator allows to use   */
/* so-called 'manipulators'.                                                 */
/*                                                                           */
/* Besides class O_Stream this file also defines the manipulators hex, dec,  */
/* oct and bin for choosing the basis in number representations, and endl    */
/* for implementing an (implicitly flushing) line termination.               */
/*****************************************************************************/

#ifndef __o_stream_include__
#define __o_stream_include__

#include "object/strbuf.h"

class O_Stream : public Stringbuffer
{
private:
	enum Mode
	{
		Bin,
		Oct,
		Dec,
		Hex
	};

	Mode mode;

	const static char HEX_DIGITS[];

	template <typename T>
	inline void print_bin(T number);

	template <typename T>
	void print_oct(T number);

	template <typename T>
	void print_dec(T number);

	template <typename T>
	void print_hex(T number);

public:
	O_Stream() : mode(Dec) {}
	O_Stream(const O_Stream &copy) = delete; // prevent copying

	O_Stream &operator<<(unsigned short number)
	{
		switch (mode)
		{
		case Bin:
			print_bin(number);
			break;
		case Oct:
			print_oct(number);
			break;
		case Dec:
			print_dec(number);
			break;
		case Hex:
			print_hex(number);
			break;
		default:
			break;
		}

		return *this;
	}
	O_Stream &operator<<(short number)
	{
		if (mode == Dec) print_dec(number);
		else *this << (unsigned short) number;

		return *this;
	}
	O_Stream &operator<<(unsigned int number)
	{
		switch (mode)
		{
		case Bin:
			print_bin(number);
			break;
		case Oct:
			print_oct(number);
			break;
		case Dec:
			print_dec(number);
			break;
		case Hex:
			print_hex(number);
			break;
		default:
			break;
		}

		return *this;
	}
	O_Stream &operator<<(int number)
	{
		if (mode == Dec) print_dec(number);
		else *this << (unsigned int) number;

		return *this;
	}
	O_Stream &operator<<(unsigned long number)
	{
		switch (mode)
		{
		case Bin:
			print_bin(number);
			break;
		case Oct:
			print_oct(number);
			break;
		case Dec:
			print_dec(number);
			break;
		case Hex:
			print_hex(number);
			break;
		default:
			break;
		}

		return *this;
	}
	O_Stream &operator<<(long number)
	{
		if (mode == Dec) print_dec(number);
		else *this << (unsigned long) number;

		return *this;
	}

	O_Stream &operator<<(const unsigned char c);
	O_Stream &operator<<(const char c);
	O_Stream &operator<<(const char *text);

	O_Stream &operator<<(const void *p);

	O_Stream &operator<<(O_Stream &(*fkt)(O_Stream &));

	friend O_Stream &endl(O_Stream &out);
	friend O_Stream &bin(O_Stream &out);
	friend O_Stream &oct(O_Stream &out);
	friend O_Stream &dec(O_Stream &out);
	friend O_Stream &hex(O_Stream &out);
};

template <typename T>
inline void O_Stream::print_bin(T number)
{
	char digit = (number % 2) + '0';
	if (number / 2)
		print_bin(number / 2);
	put(digit);
}

template <typename T>
inline void O_Stream::print_oct(T number)
{
	char digit = (number % 8) + '0';
	if (number / 8)
		print_oct(number / 8);
	put(digit);
}

template <typename T>
inline void O_Stream::print_dec(T number)
{
	if (number < 0)
	{
		put('-');
		number = -number;
	}

	char digit = (number % 10) + '0';
	if (number / 10)
		print_dec(number / 10);
	put(digit);
}

template <typename T>
inline void O_Stream::print_hex(T number)
{
	char digit = (number % 16);
	if (number / 16)
		print_hex(number / 16);
	put(HEX_DIGITS[digit]);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          M A N I P U L A T O R S                          */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* The functions below all receive and return a reference to an O_Stream     */
/* object. Because class O_Stream defines an operator<< for functions with   */
/* this signature, they can be called in this operator's implementation and  */
/* even be embedded in a "stream" of outputs. A manipulator's task is to     */
/* influence subsequent output, e.g. by switching to a different number      */
/* system.                                                                   */
/*---------------------------------------------------------------------------*/

// ENDL: inserts a newline in the output and flushes the buffer
O_Stream &endl(O_Stream &out);

// BIN: selects the binary number system
O_Stream &bin(O_Stream &out);

// OCT: selects the octal number system
O_Stream &oct(O_Stream &out);

// DEC: selects the decimal number system
O_Stream &dec(O_Stream &out);

// HEX: selects the hexadecimal number system
O_Stream &hex(O_Stream &out);

#endif
