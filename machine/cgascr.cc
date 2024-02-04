/*****************************************************************************/
/* Operating-System Construction                                             */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                             C G A _ S C R E E N                           */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* This class allows accessing the PC's screen.  Accesses work directly on   */
/* the hardware level, i.e. via the video memory and the graphic adapter's   */
/* I/O ports.                                                                */
/*****************************************************************************/

#include "machine/cgascr.h"
#include "machine/io_port.h"
#include "cgascr.h"

void CGA_Screen::show(int x, int y, char c, unsigned char attrib)
{
    *(VIDEO_BUFFER + 2 * x + (2 * COLS * y)) = c;
    *(VIDEO_BUFFER + 2 * x + (2 * COLS * y) + 1) = attrib;
}

void CGA_Screen::setpos(int x, int y)
{
    int pos = (COLS * y) + x;

    index.outb(15);
    unsigned int low = pos & 0xFF;
    data.outb(low);

    index.outb(14);
    unsigned int high = (pos >> 8) & 0xFF;
    data.outb(high);

    // x_pos = x;
    // y_pos = y;
}

void CGA_Screen::getpos(int &x, int &y)
{
    index.outb(15);
    unsigned int low = data.inb();

    index.outb(14);
    unsigned int high = data.inb();

    int pos = (high << 8) | low;

    x = pos % COLS;
    y = pos / COLS;
}

void CGA_Screen::print(char *text, int length, unsigned char attrib)
{
    int x_pos, y_pos;
    getpos(x_pos, y_pos);

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

        if (y_pos >= LINES)
        {
            for (int i = 2 * COLS; i < 2 * COLS * LINES; i += 2)
            {
                char c = *(VIDEO_BUFFER + i);
                *(VIDEO_BUFFER + i - 2 * COLS) = c;
            }

            for (int i = 2 * COLS * (LINES - 1); i < 2 * COLS * LINES; i += 2)
            {
                *(VIDEO_BUFFER + i) = 0;
                *(VIDEO_BUFFER + i + 1) = 0b00000111;
            }

            y_pos = LINES - 1;
        }
    }

    setpos(x_pos, y_pos);
}

void CGA_Screen::copy(unsigned char *src, int row_start, int row_end)
{
    int lines = row_end - row_start;

    unsigned char *start = (unsigned char *)(row_start * 80 * 2);
    // unsigned char *end = (unsigned char *) (start + (lines * 80 * 2));

    for (int i = 0; i < lines * 80; i += 2)
    {
        char c = src[i];
        unsigned char a = src[i + 1];

        start[i] = c;
        start[i + 1] = a;
    }
}
