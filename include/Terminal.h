/*
 * Copyright (C) 2018-2019 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#ifndef TERMINAL_H
#define TERMINAL_H

#include <cstring>
#include <vector>
#include "MatrixChar.h"

struct TerminalChar {
	// White foreground
	static constexpr char GLOWING_COLOR_ESC_SEQ[] {"\033[97m"};
	// Green foreground
	static constexpr char NORMAL_COLOR_ESC_SEQ[] {"\033[32m"};
	static constexpr std::size_t PREFIX_SIZE {sizeof(NORMAL_COLOR_ESC_SEQ)-1};

	char prefix[PREFIX_SIZE] { '\033', '[', '3', '2', 'm'};
	char MChar[MatrixChar::MCHAR_SIZE] { ' ' };

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

	Terminal();
	~Terminal();
public:
	Terminal(Terminal const&) = delete;
	void operator=(Terminal const&)	= delete;

	static Terminal& getInstance()
	{
		static Terminal instance;
		return instance;
	}

	static int GetNumberOfRows() { return NumberOfRows; }
	static int GetNumberOfColumns() { return NumberOfColumns; }

	static void Draw(int x, int y, const char *mchar, bool isGlowing);
	static void Erase(int x, int y);
	static void DrawTitle(int x, int y, char tchar);
	static void Flush();
	static char ReadInputChar();
};

#endif
