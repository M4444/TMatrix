/*
 * Copyright (C) 2018-2021 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <string>
#include "TerminalChar.h"

template <>
const char *BaseTerminalChar<true>::GLOWING_COLOR_ESC_SEQ {Color::GetColor("white").Shade1};
template <>
const char *BaseTerminalChar<true>::NORMAL_COLOR_ESC_SEQ {nullptr};
template <>
const char *BaseTerminalChar<false>::GLOWING_COLOR_ESC_SEQ {Color::GetColor("white").Foreground};
template <>
const char *BaseTerminalChar<false>::NORMAL_COLOR_ESC_SEQ {nullptr};

const char *TerminalChar<true>::NORMAL_COLOR_ESC_SEQ_2 {nullptr};
const char *TerminalChar<true>::NORMAL_COLOR_ESC_SEQ_3 {nullptr};
const char *TerminalChar<true>::NORMAL_COLOR_ESC_SEQ_4 {nullptr};

template <bool F>
void BaseTerminalChar<F>::Clear()
{
	std::memcpy(&prefix, NORMAL_COLOR_ESC_SEQ, PREFIX_SIZE);
	std::memcpy(&MChar, MatrixChar::GetEmptyMChar(), MatrixChar::MCHAR_SIZE);
}
// Instantiate both versions of the Clear()
template void BaseTerminalChar<true>::Clear();
template void BaseTerminalChar<false>::Clear();

template <bool F>
void BaseTerminalChar<F>::SetFullTitleChar(wchar_t tchar)
{
	std::memcpy(&prefix, GLOWING_COLOR_ESC_SEQ, PREFIX_SIZE);
	std::memset(&MChar, '\0', MatrixChar::MCHAR_SIZE);

	// Convert wchar to (const char *)
	std::string tchar_buffer(MB_CUR_MAX, '\0');
	int tchar_size = std::wctomb(&tchar_buffer[0], tchar);
	if (tchar_size > 0) {
		std::memcpy(&MChar, tchar_buffer.data(),
			    std::min(static_cast<std::size_t>(tchar_size),
			    MatrixChar::MCHAR_SIZE));
	}
}
// Instantiate both versions of the SetFullTitleChar()
template void BaseTerminalChar<true>::SetFullTitleChar(wchar_t tchar);
template void BaseTerminalChar<false>::SetFullTitleChar(wchar_t tchar);

void TerminalChar<true>::SetColor(const Color& color)
{
	NORMAL_COLOR_ESC_SEQ = color.Shade1;
	NORMAL_COLOR_ESC_SEQ_2 = color.Shade2;
	NORMAL_COLOR_ESC_SEQ_3 = color.Shade3;
	NORMAL_COLOR_ESC_SEQ_4 = color.Shade4;
}

void TerminalChar<true>::SetFullMChar(const char *mchar, int colorShade)
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

void TerminalChar<false>::SetColor(const Color& color)
{
	GLOWING_COLOR_ESC_SEQ = Color::GetColor("white").Foreground;
	NORMAL_COLOR_ESC_SEQ = color.Foreground;
}

void TerminalChar<false>::SetFullMChar(const char *mchar, int colorShade)
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
