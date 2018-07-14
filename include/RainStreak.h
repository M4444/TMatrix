/*
 * Copyright (C) 2018 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#ifndef RAIN_STREAK_H
#define RAIN_STREAK_H

#include <deque>
#include <memory>
#include "Active.h"
#include "MatrixChar.h"

class Rain;

class RainStreak : public Active {
	const std::shared_ptr<Rain> rain;
	const int x;
	int y {0};
	const int Length;
	const int Speed;
	bool FullyEnteredScreen {false};
	bool OutOfScreen {false};
	std::deque<MatrixChar> MChars;
public:
	RainStreak(const std::shared_ptr<Rain> &R, int col, int Len, int S) :
		rain{R}, x{col}, Length{Len}, Speed{S} {}

	bool IsOutOfScreen() const { return OutOfScreen; }
	bool HasFullyEnteredScreen() const { return FullyEnteredScreen; }

	void Step();
	void Update();
};

#endif
