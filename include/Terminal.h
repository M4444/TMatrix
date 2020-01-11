/*
 * Copyright (C) 2018-2020 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#ifndef TERMINAL_H
#define TERMINAL_H

#include <vector>
#include "Color.h"
#include "TerminalChar.h"

// Singleton
class Terminal {
	static int NumberOfRows;
	static int NumberOfColumns;
	static std::vector<TerminalChar> ScreenBuffer;

	Terminal(const Color& color, const Color& background_color);
	~Terminal();
public:
	Terminal(Terminal const&) = delete;
	void operator=(Terminal const&)	= delete;

	static Terminal& getInstance(const Color& color, const Color& background_color)
	{
		static Terminal instance {color, background_color};
		return instance;
	}

	static int GetNumberOfRows() { return NumberOfRows; }
	static int GetNumberOfColumns() { return NumberOfColumns; }

	static void Reset();
	static void Draw(int x, int y, const char *mchar, bool isGlowing);
	static void Erase(int x, int y);
	static void DrawTitle(int x, int y, char tchar);
	static void Flush();
	static char ReadInputChar();
};

#endif
