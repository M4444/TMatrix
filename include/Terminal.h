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
protected:
	int NumberOfRows {0};
	int NumberOfColumns {0};
public:
	Terminal();
	~Terminal();

	int GetNumberOfRows() { return NumberOfRows; }
	int GetNumberOfColumns() { return NumberOfColumns; }

	virtual void Reset() = 0;
	virtual void Draw(int x, int y, const char *mchar, int colorShade) = 0;
	virtual void Erase(int x, int y) = 0;
	virtual void DrawTitle(int x, int y, wchar_t tchar) = 0;
	virtual void Flush() = 0;
};

template <bool F>
class ColorTerminal : public Terminal {
	using TCharType = TerminalChar<F>;

	std::vector<TCharType> ScreenBuffer;
public:
	ColorTerminal<F>(const Color& color, const Color& background_color);

	void Reset();
	void Draw(int x, int y, const char *mchar, int colorShade);
	void Erase(int x, int y);
	void DrawTitle(int x, int y, wchar_t tchar);
	void Flush();
};

#endif
