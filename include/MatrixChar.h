/*
 * Copyright (C) 2018-2020 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#ifndef MATRIX_CHAR_H
#define MATRIX_CHAR_H

#include <array>
#include "Active.h"
#include "CountdownTimer.h"
#include "HasTerminal.h"

class MatrixChar : public Active, public HasTerminal {
	const int x;
	const int y;
	CountdownTimer UpdateTimer;
	int MCharIndex {GetRandomMCharIndex()};
	bool Glowing {true};

	static int GetRandomMCharIndex();
	void SetRandomMChar();
	void Draw() const;
	void Erase() const;
public:
	static constexpr std::size_t MCHAR_SIZE {sizeof("𐌇")-1};
	static constexpr std::size_t ALL_MCHARS_LENGTH {57};
	static constexpr std::array<const char [MCHAR_SIZE+1], ALL_MCHARS_LENGTH> ALL_MCHARS {
		"ﾊ", "ﾐ", "ﾋ", "ｰ", "ｳ", "ｼ", "ﾅ", "ﾓ", "ﾆ", "ｻ",
		"ﾜ", "ﾂ", "ｵ", "ﾘ", "ｱ", "ﾎ", "ﾃ", "ﾏ", "ｹ", "ﾒ",
		"ｴ", "ｶ", "ｷ", "ﾑ", "ﾕ", "ﾗ", "ｾ", "ﾈ", "ｽ", "ﾀ",
		"ﾇ", "ﾍ", "𐌇", "0", "1", "2", "3", "4", "5", "7",
		"8", "9", "Z", ":", ".", "･", "=", "*", "+", "-",
		"<", ">", "¦", "|", "╌", " ", "\""
	};

	MatrixChar(int X, int Y, int UpdateRate, int UpdateTime) : x{X}, y{Y},
		UpdateTimer{UpdateRate, UpdateTime} {
		Draw();
	}
	~MatrixChar() {
		Erase();
	}

	static const char *GetMChar(std::size_t index)
	{
		return ALL_MCHARS[index];
	}

	static const char *GetEmptyMChar()
	{
		return ALL_MCHARS[ALL_MCHARS_LENGTH-2];
	}

	void Update();
	void SetNotGlowing();
};

#endif
