/*
 * Copyright (C) 2018-2026 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#ifndef MATRIX_CHAR_H
#define MATRIX_CHAR_H

#include <array>
#include "Active.h"
#include "CountdownTimer.h"
#include "HasTerminal.h"

class MatrixChar final : public Active, public HasTerminal {
	const unsigned x;
	const unsigned y;
	CountdownTimer UpdateTimer;
	std::size_t MCharIndex {GetRandomMCharIndex()};
	int ColorShade {0};

	static std::size_t GetRandomMCharIndex();
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
	static constexpr char EMPTY_MCHAR[MCHAR_SIZE+1] {" "};

	MatrixChar(unsigned X, unsigned Y, int UpdateRate, int UpdateTime) : x{X}, y{Y},
		UpdateTimer{UpdateRate, UpdateTime} {
		Draw();
	}
	~MatrixChar() {
		Erase();
	}

	static constexpr const char *GetMChar(std::size_t index)
	{
		return ALL_MCHARS[index];
	}

	static constexpr const char *GetEmptyMChar()
	{
		return EMPTY_MCHAR;
	}

	unsigned GetVerticalOffset(unsigned verticalPosition) {
		return verticalPosition - y;
	}

	void Update() final;
	void SetColorShade(int colorShade);
};

#endif
