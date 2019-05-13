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
	// Terminal foreground color escape sequences
	static constexpr char DEFAULT_COLOR[] {"\033[39m"};
	static constexpr char WHITE_COLOR[]   {"\033[97m"};
	static constexpr char GRAY_COLOR[]    {"\033[90m"};
	static constexpr char BLACK_COLOR[]   {"\033[30m"};
	static constexpr char RED_COLOR[]     {"\033[31m"};
	static constexpr char GREEN_COLOR[]   {"\033[32m"};
	static constexpr char YELLOW_COLOR[]  {"\033[33m"};
	static constexpr char BLUE_COLOR[]    {"\033[34m"};
	static constexpr char MAGENTA_COLOR[] {"\033[35m"};
	static constexpr char CYAN_COLOR[]    {"\033[36m"};

	static constexpr std::size_t PREFIX_SIZE {sizeof(DEFAULT_COLOR)-1};

	static const char *GLOWING_COLOR_ESC_SEQ;
	static const char *NORMAL_COLOR_ESC_SEQ;

	static void SetColor(const char *color)
	{
		NORMAL_COLOR_ESC_SEQ = color;
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

	Terminal(const char *color);
	~Terminal();
public:
	Terminal(Terminal const&) = delete;
	void operator=(Terminal const&)	= delete;

	static Terminal& getInstance(const char *color)
	{
		static Terminal instance {color};
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
