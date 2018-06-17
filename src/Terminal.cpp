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

	// Set black background
	//std::cout << "\033[40m";
	// Set bold style
	std::cout << "\033[1m";
	// Set green foreground
	std::cout << "\033[32m";
}

Terminal::~Terminal() {
	curs_set(1);
	clear();
	refresh();
	resetty();
	endwin();
}

void Terminal::Draw(int x, int y, const std::string &str, bool isGlowing)
{
	// Set the color to white if MChar is glowing
	Screen[y*NumberOfColumns + x] = isGlowing ? "\033[97m" + str + "\033[32m" : str;
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
