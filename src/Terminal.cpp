#include <cstdio>
#include <ncurses.h>
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

	getmaxyx(stdscr, Terminal::NumberOfRows, Terminal::NumberOfColumns);
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
	printf("\033[%d;%dH%s\n", y, x, str.c_str());
}

void Terminal::Erase(int x, int y)
{
	printf("\033[%d;%dH%s\n", y, x, " ");
}
