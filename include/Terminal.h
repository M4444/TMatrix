/*
 * Copyright (C) 2018-2019 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#ifndef TERMINAL_H
#define TERMINAL_H

#include <cstring>
#include <vector>
#include "Color.h"
#include "MatrixChar.h"

struct TerminalChar {
	static constexpr std::size_t PREFIX_SIZE {Color::LONGEST_COLOR_SIZE-1};

	static const char *GLOWING_COLOR_ESC_SEQ;
	static const char *NORMAL_COLOR_ESC_SEQ;

	static void SetColor(const Color& color)
	{
		NORMAL_COLOR_ESC_SEQ = color.Foreground;
	}

	// Non-static members
	char prefix[PREFIX_SIZE];
	char MChar[MatrixChar::MCHAR_SIZE];

	TerminalChar()
	{
		Clear();
	}

	void SetFullMChar(const char *mchar, bool isGlowing)
	{
		if (isGlowing) {
			std::memcpy(&prefix, GLOWING_COLOR_ESC_SEQ, PREFIX_SIZE);
		} else {
			std::memcpy(&prefix, NORMAL_COLOR_ESC_SEQ, PREFIX_SIZE);
		}
		std::memcpy(&MChar, mchar, MatrixChar::MCHAR_SIZE);
	}

	void Clear()
	{
		std::memcpy(&prefix, NORMAL_COLOR_ESC_SEQ, PREFIX_SIZE);
		std::memcpy(&MChar, MatrixChar::GetEmptyMChar(), MatrixChar::MCHAR_SIZE);
	}

	void SetFullTitleChar(char tchar)
	{
		std::memcpy(&prefix, GLOWING_COLOR_ESC_SEQ, PREFIX_SIZE);
		std::memset(&MChar, '\0', MatrixChar::MCHAR_SIZE);
		MChar[0] = tchar;
	}
};

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
