/*
 * Copyright (C) 2018-2021 Miloš Stojanović
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
	unsigned NumberOfRows {0};
	unsigned NumberOfColumns {0};
public:
	Terminal();
	virtual ~Terminal();

	unsigned GetNumberOfRows() { return NumberOfRows; }
	unsigned GetNumberOfColumns() { return NumberOfColumns; }

	virtual void Reset() = 0;
	virtual void Draw(unsigned x, unsigned y, const char *mchar, int colorShade) = 0;
	virtual void Erase(unsigned x, unsigned y) = 0;
	virtual void DrawTitle(unsigned x, unsigned y, wchar_t tchar) = 0;
	virtual void Flush() = 0;
};

template <bool F>
class ColorTerminal : public Terminal {
	using TCharType = TerminalChar<F>;

	std::vector<TCharType> ScreenBuffer;
public:
	ColorTerminal<F>(const Color& color, const Color& background_color);

	void Reset();
	void Draw(unsigned x, unsigned y, const char *mchar, int colorShade);
	void Erase(unsigned x, unsigned y);
	void DrawTitle(unsigned x, unsigned y, wchar_t tchar);
	void Flush();
};

#endif
