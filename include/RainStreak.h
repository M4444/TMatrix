/*
 * Copyright (C) 2018 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#ifndef _RAIN_STREAK_H_
#define _RAIN_STREAK_H_

#include <deque>
#include "Active.h"
#include "MatrixChar.h"

class RainStreak : public Active {
	const int x;
	int y {0};
	const int Length;
	const int Speed;
	bool FullyEnteredScreen {false};
	bool OutOfScreen {false};
	std::deque<MatrixChar> MChars;
public:
	RainStreak(int col, int Len, int S) : x{col}, Length{Len}, Speed{S} {}

	bool IsOutOfScreen() const { return OutOfScreen; }
	bool HasFullyEnteredScreen() const { return FullyEnteredScreen; }

	void Step();
	void Update();
};

#endif
