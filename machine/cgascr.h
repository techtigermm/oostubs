#ifndef __screen_include__
#define __screen_include__

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

#include "machine/io_port.h"
#include "machine/io_port.h"

#define VIDEO_BUFFER (unsigned char *)0xB8000
#define LINES 25
#define COLS 80

class CGA_Screen
{
private:
	IO_Port index;
	IO_Port data;

public:
	CGA_Screen(const CGA_Screen &copy) = delete; // prevent copying
	CGA_Screen() : index(IO_Port(0x3D4)),
				   data(IO_Port(0x3D5))

	{
		for (int i = 0; i < LINES * COLS; i += 2)
		{
			*(VIDEO_BUFFER + i) = 0;
			// *(VIDEO_BUFFER + i + 1) = 0;
		}

		setpos(0, 0);
	}

	void show(int x, int y, char c, unsigned char attrib);
	virtual void setpos(int x, int y);
	virtual void getpos(int &x, int &y);
	void print(char *text, int length, unsigned char attrib);

	void copy(unsigned char *src, int row_start, int row_end);
};

#endif
