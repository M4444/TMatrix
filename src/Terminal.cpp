/*
 * Copyright (C) 2018-2020 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include <iostream>
#include <ncurses.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "Terminal.h"

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

	// Disable C stream sync
	std::ios::sync_with_stdio(false);

	// Calling this here first prevents delay in the main loop.
	getch();
}

Terminal::~Terminal()
{
	curs_set(1);
	clear();
	refresh();
	resetty();
	endwin();
}

template <bool F>
ColorTerminal<F>::ColorTerminal(const Color& color, const Color& background_color)
{
	// Set bold style
	std::cout << "\033[1m";
	// Set foreground color
	TCharType::SetColor(color);
	// Set background color
	std::cout << background_color.Background;

	Reset();
}

// Instantiate both versions of the constructor
template ColorTerminal<true>::ColorTerminal(const Color& color, const Color& background_color);
template ColorTerminal<false>::ColorTerminal(const Color& color, const Color& background_color);

template <bool F>
void ColorTerminal<F>::Reset()
{
	struct winsize windowSize;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &windowSize);
	NumberOfRows = windowSize.ws_row;
	NumberOfColumns = windowSize.ws_col;

	ScreenBuffer = std::vector(static_cast<std::size_t>(NumberOfColumns*NumberOfRows),
				   TCharType());
}

template <bool F>
void ColorTerminal<F>::Draw(unsigned x, unsigned y, const char *mchar, int colorShade)
{
	// Assumes that x and y are in bounds
	ScreenBuffer[y*NumberOfColumns + x].SetFullMChar(mchar, colorShade);
}

template <bool F>
void ColorTerminal<F>::Erase(unsigned x, unsigned y)
{
	// Assumes that x and y are in bounds
	ScreenBuffer[y*NumberOfColumns + x].Clear();
}

template <bool F>
void ColorTerminal<F>::DrawTitle(unsigned x, unsigned y, wchar_t tchar)
{
	// Assumes that x and y are in bounds
	ScreenBuffer[y*NumberOfColumns + x].SetFullTitleChar(tchar);
}

template <bool F>
void ColorTerminal<F>::Flush()
{
	std::cout.write(reinterpret_cast<char*>(ScreenBuffer.data()),
			static_cast<std::streamsize>(ScreenBuffer.size() * sizeof(TCharType)));
	std::cout << std::flush;
	// Move cursor to the start of the screen
	std::cout << "\033[0;0H";
}
