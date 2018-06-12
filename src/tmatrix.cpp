#include <time.h>
#include <sys/ioctl.h>
#include <unistd.h>

#ifdef HAVE_NCURSES_H
#include <ncurses.h>
#else
#include <curses.h>
#endif

#include "Rain.h"

#define RUN_SPEED 100

void init()
{
	initscr();
	savetty();
	nonl();
	cbreak();
	noecho();
	timeout(0);
	leaveok(stdscr, TRUE);
	curs_set(0);
}

void uninit()
{
	curs_set(1);
	clear();
	refresh();
	resetty();
	endwin();
}

int NumberOfRows, NumberOfColumns;

int main()
{
	struct winsize WindowSize;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &WindowSize);
	NumberOfRows = WindowSize.ws_row;
	NumberOfColumns = WindowSize.ws_col;

	srand (time(NULL));
	init();

	Rain rain = Rain();
	while (true) {
		usleep(1000*RUN_SPEED);

		rain.Update();
	}

	uninit();
	return 0;
}
