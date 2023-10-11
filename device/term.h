#ifndef __term_include__
#define __term_include__

#include "object/o_stream.h"
#include "machine/cgascr.h"

class Terminal : public O_Stream, public CGA_Screen
{
private:
    unsigned char *term_buffer;
    int lines_start;
    int lines_end;
    int pos_x, pos_y;

public:
    Terminal(unsigned char *buf, int lines_start, int lines_end);
    ~Terminal() {}

    void show(int x, int y, char c, unsigned char attrib);
    void setpos(int x, int y);
    void getpos(int &x, int &y);
    void print(char *text, int length, unsigned char attrib);

    void flush();
};

#endif