/*
 * Copyright (C) 2018-2019 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#ifndef TERMINAL_H
#define TERMINAL_H

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <string>
#include <string_view>
#include <vector>
#include "MatrixChar.h"

struct TerminalChar {
	static constexpr char GLOW_SEQ[] { '\033', '[', '9', '7', 'm' };
	static constexpr char GLOW_END_SEQ[] { '\033', '[', '3', '2', 'm' };
	static constexpr std::size_t PREFIX_SIZE {sizeof(GLOW_SEQ)};
	static constexpr std::size_t MCHAR_SIZE {MatrixChar::GetMaxMCharSize()};
	static constexpr std::size_t SUFFIX_SIZE {sizeof(GLOW_END_SEQ)};

	char prefix[PREFIX_SIZE] { '\0' };
	char MChar[MCHAR_SIZE] { ' ' };
	char suffix[SUFFIX_SIZE] { '\0' };

	void SetFullMChar(std::string_view str, bool isGlowing)
	{
		std::memset(&prefix, '\0', sizeof(*this));
		std::memcpy(&MChar, str.data(), std::min(str.length(), MCHAR_SIZE));
		if (isGlowing) {
			std::memcpy(&prefix, GLOW_SEQ, PREFIX_SIZE);
			std::memcpy(&suffix, GLOW_END_SEQ, SUFFIX_SIZE);
		}
	}

	void Clear()
	{
		std::memset(&prefix, '\0', sizeof(*this));
		MChar[0] = ' ';
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

	static void Draw(int x, int y, std::string_view str, bool isGlowing = false);
	static void Erase(int x, int y);
	static void Flush();
	static char ReadInputChar();
};

#endif
