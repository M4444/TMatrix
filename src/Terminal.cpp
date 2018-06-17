#include <iostream>
#include <ncurses.h>
#include "Terminal.h"

int Terminal::NumberOfRows = 0;
int Terminal::NumberOfColumns = 0;
std::vector<std::string> Terminal::Screen;

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

	Screen = std::vector<std::string>(NumberOfColumns*NumberOfRows, " ");
}

Terminal::~Terminal() {
	curs_set(1);
	clear();
	refresh();
	resetty();
	endwin();
}

void Terminal::Draw(int x, int y, const std::string &str)
{
	Screen[y*NumberOfColumns + x] = str;
}

void Terminal::Erase(int x, int y)
{
	Draw(x, y, " ");
}

void Terminal::Flush()
{
	for (const auto &c : Screen) {
		std::cout << c;
	}
	std::cout << std::flush;
	std::cout << "\033[0;0H";
}
