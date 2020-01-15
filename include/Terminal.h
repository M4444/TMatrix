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

class Terminal {
	int NumberOfRows {0};
	int NumberOfColumns {0};
	std::vector<TerminalChar> ScreenBuffer;
public:
	Terminal(const Color& color, const Color& background_color);
	~Terminal();

	static Terminal& getInstance(const Color& color, const Color& background_color)
	{
		static Terminal instance {color, background_color};
		return instance;
	}

	int GetNumberOfRows() { return NumberOfRows; }
	int GetNumberOfColumns() { return NumberOfColumns; }

	void Reset();
	void Draw(int x, int y, const char *mchar, bool isGlowing);
	void Erase(int x, int y);
	void DrawTitle(int x, int y, char tchar);
	void Flush();
};

#endif
