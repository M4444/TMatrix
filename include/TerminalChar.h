/*
 * Copyright (C) 2018-2023 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#ifndef TERMINAL_CHAR_H
#define TERMINAL_CHAR_H

#include "Color.h"
#include "MatrixChar.h"

template <bool F>
struct BaseTerminalChar {
	static constexpr std::size_t PREFIX_SIZE {Color::GetPrefixSize(F)-1};

	static const char *GLOWING_COLOR_ESC_SEQ;
	static const char *NORMAL_COLOR_ESC_SEQ;

	// Non-static members
	char prefix[PREFIX_SIZE];
	char MChar[MatrixChar::MCHAR_SIZE];

	BaseTerminalChar()
	{
		Clear();
	}

	void Clear();

	void SetFullTitleChar(wchar_t tchar);
};

template <bool F>
struct TerminalChar;

template <>
struct TerminalChar<true> : public BaseTerminalChar<true> {
	static const char *NORMAL_COLOR_ESC_SEQ_2;
	static const char *NORMAL_COLOR_ESC_SEQ_3;
	static const char *NORMAL_COLOR_ESC_SEQ_4;

	static void SetColor(const Color& color);

	void SetFullMChar(const char *mchar, int colorShade);
};

template <>
struct TerminalChar<false> : public BaseTerminalChar<false> {
	static void SetColor(const Color& color);

	void SetFullMChar(const char *mchar, int colorShade);
};

#endif
