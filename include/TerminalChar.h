/*
 * Copyright (C) 2018-2019 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#ifndef TERMINAL_CHAR_H
#define TERMINAL_CHAR_H

#include <cstring>
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

template <bool F>
struct TerminalChar;

template <>
struct TerminalChar<true> : public BaseTerminalChar<true> {
	static const char *NORMAL_COLOR_ESC_SEQ_2;
	static const char *NORMAL_COLOR_ESC_SEQ_3;
	static const char *NORMAL_COLOR_ESC_SEQ_4;

	static void SetColor(const Color& color)
	{
		NORMAL_COLOR_ESC_SEQ = color.Shade1;
		NORMAL_COLOR_ESC_SEQ_2 = color.Shade2;
		NORMAL_COLOR_ESC_SEQ_3 = color.Shade3;
		NORMAL_COLOR_ESC_SEQ_4 = color.Shade4;
	}

	void SetFullMChar(const char *mchar, int colorShade)
	{
		switch (colorShade) {
		case 0:
			std::memcpy(&prefix, GLOWING_COLOR_ESC_SEQ, PREFIX_SIZE);
			break;
		case 1:
		default:
			std::memcpy(&prefix, NORMAL_COLOR_ESC_SEQ, PREFIX_SIZE);
			break;
		case 2:
			std::memcpy(&prefix, NORMAL_COLOR_ESC_SEQ_2, PREFIX_SIZE);
			break;
		case 3:
			std::memcpy(&prefix, NORMAL_COLOR_ESC_SEQ_3, PREFIX_SIZE);
			break;
		case 4:
			std::memcpy(&prefix, NORMAL_COLOR_ESC_SEQ_4, PREFIX_SIZE);
			break;
		}
		std::memcpy(&MChar, mchar, MatrixChar::MCHAR_SIZE);
	}
};

template <>
struct TerminalChar<false> : public BaseTerminalChar<false> {
	static void SetColor(const Color& color)
	{
		GLOWING_COLOR_ESC_SEQ = Color::GetColor("white").Foreground;
		NORMAL_COLOR_ESC_SEQ = color.Foreground;
	}

	void SetFullMChar(const char *mchar, int colorShade)
	{
		switch (colorShade) {
		case 0:
			std::memcpy(&prefix, GLOWING_COLOR_ESC_SEQ, PREFIX_SIZE);
			break;
		case 1:
		default:
			std::memcpy(&prefix, NORMAL_COLOR_ESC_SEQ, PREFIX_SIZE);
			break;
		}
		std::memcpy(&MChar, mchar, MatrixChar::MCHAR_SIZE);
	}
};

#endif
