#include <sys/ioctl.h>
#include <unistd.h>

#ifdef HAVE_NCURSES_H
#include <ncurses.h>
#else
#include <curses.h>
#endif

#include "Terminal.h"

int Terminal::NumberOfRows = 0;
int Terminal::NumberOfColumns = 0;

Terminal::Terminal() {
	initscr();
	savetty();
	nonl();
	cbreak();
	noecho();
	timeout(0);
	leaveok(stdscr, TRUE);
	curs_set(0);

	struct winsize WindowSize;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &WindowSize);
	Terminal::NumberOfRows = WindowSize.ws_row;
	Terminal::NumberOfColumns = WindowSize.ws_col;
}

Terminal::~Terminal() {
	curs_set(1);
	clear();
	refresh();
	resetty();
	endwin();
}

void Terminal::Draw(int x, int y, std::string &str)
{
	printf("\033[%d;%dH%s\n", x, y, str.c_str());
}

void Terminal::Erase(int x, int y)
{
	printf("\033[%d;%dH%s\n", x, y, " ");
}
