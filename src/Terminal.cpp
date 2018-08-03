/*
 * Copyright (C) 2018 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include <iostream>
#include <ncurses.h>
#include "Terminal.h"

int Terminal::NumberOfRows {0};
int Terminal::NumberOfColumns {0};
std::vector<TerminalChar> Terminal::ScreenBuffer {};

Terminal::Terminal()
{
	initscr();
	savetty();
	nonl();
	cbreak();
	noecho();
	timeout(0);
	leaveok(stdscr, TRUE);
	curs_set(0);

	getmaxyx(stdscr, Terminal::NumberOfRows, Terminal::NumberOfColumns);

	ScreenBuffer = std::vector(NumberOfColumns*NumberOfRows, TerminalChar());

	// Disable C stream sync
	std::ios::sync_with_stdio(false);

	// Set black background
	//std::cout << "\033[40m";
	// Set bold style
	std::cout << "\033[1m";
	// Set green foreground
	std::cout << "\033[32m";
}

Terminal::~Terminal()
{
	curs_set(1);
	clear();
	refresh();
	resetty();
	endwin();
}

void Terminal::Draw(int x, int y, std::string_view str, bool isGlowing)
{
	if (x < 0 || x > NumberOfColumns-1 || y < 0 || y > NumberOfRows-1) {
		return;
	}

	ScreenBuffer[y*NumberOfColumns + x].SetFullMChar(str, isGlowing);
}

void Terminal::Erase(int x, int y)
{
	if (x < 0 || x > NumberOfColumns-1 || y < 0 || y > NumberOfRows-1) {
		return;
	}

	ScreenBuffer[y*NumberOfColumns + x].Clear();
}

void Terminal::Flush()
{
	std::cout.write(reinterpret_cast<char*>(ScreenBuffer.data()),
			ScreenBuffer.size() * sizeof(decltype(ScreenBuffer)::value_type));
	std::cout << std::flush;
	// Move cursor to the start of the screen
	std::cout << "\033[0;0H";
}

char Terminal::ReadInputChar()
{
	return getch();
}
