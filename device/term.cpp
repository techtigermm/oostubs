#include "term.h"

#include "machine/cgascr.h"

CGA_Screen cga;

Terminal::Terminal(unsigned char *buf, int lines_start, int lines_end) : term_buffer(buf), lines_start(lines_start), lines_end(lines_end), pos_x(0), pos_y(0)
{
    int lines = lines_end - lines_start;

    for (int i = 0; i < lines * COLS; i += 2)
    {
        *(term_buffer + i) = 0;
        *(term_buffer + i + 1) = 0b00000111;
    }

    setpos(0, 0);
}

void Terminal::show(int x, int y, char c, unsigned char attrib)
{
    *(term_buffer + 2 * x + (2 * COLS * y)) = c;
    *(term_buffer + 2 * x + (2 * COLS * y) + 1) = attrib;
}

void Terminal::setpos(int x, int y)
{
    pos_x = x;
    pos_y = y;
}

void Terminal::getpos(int &x, int &y)
{
    x = pos_x;
    y = pos_y;
}

void Terminal::print(char *text, int length, unsigned char attrib)
{
    int x_pos, y_pos;
    getpos(x_pos, y_pos);

    int lines = lines_end - lines_start;

    for (char *c = text; c < text + length; c++)
    {
        if (x_pos == COLS)
        {
            x_pos = 0;
            y_pos++;
        }

        if (*c == '\n')
        {
            x_pos = 0;
            y_pos++;
        }
        else
        {
            show(x_pos, y_pos, *c, attrib);
            x_pos++;
        }

        if (y_pos >= lines)
        {
            for (int i = 2 * COLS; i < 2 * COLS * lines; i += 2)
            {
                char c = *(term_buffer + i);
                *(term_buffer + i - 2 * COLS) = c;
            }

            for (int i = 2 * COLS * (lines - 1); i < 2 * COLS * lines; i += 2)
            {
                *(term_buffer + i) = 0;
                *(term_buffer + i + 1) = 0b00000111;
            }

            y_pos = lines - 1;
        }
    }

    setpos(x_pos, y_pos);
}

void Terminal::flush()
{
    print(buffer, pos, 0b00000111);
    pos = 0;
    cga.copy(term_buffer, lines_start, lines_end);
}
