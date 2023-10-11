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

#include "object/o_stream.h"
#include "o_stream.h"

const char O_Stream::HEX_DIGITS[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

O_Stream &O_Stream::operator<<(const unsigned char c)
{
    put(c);
    return *this;
}

O_Stream &O_Stream::operator<<(const char c)
{
    put(c);
    return *this;
}

O_Stream &O_Stream::operator<<(const char *text)
{
    for (const char *c = text; *c; c++)
    {
        put(*c);
    }
    return *this;
}

O_Stream &O_Stream::operator<<(const void *p)
{
    print_hex((unsigned long int) p);
    return *this;
}

O_Stream &O_Stream::operator<<(O_Stream &(*fkt)(O_Stream &))
{
    return (*fkt)(*this);
}

O_Stream &endl(O_Stream &out)
{
    out.put('\n');
    out.flush();
    return out;
}

O_Stream &bin(O_Stream &out)
{
    out.mode = O_Stream::Bin;
    return out;
}

O_Stream &oct(O_Stream &out)
{
    out.mode = O_Stream::Oct;
    return out;
}

O_Stream &dec(O_Stream &out)
{
    out.mode = O_Stream::Dec;
    return out;
}

O_Stream &hex(O_Stream &out)
{
    out.mode = O_Stream::Hex;
    return out;
}