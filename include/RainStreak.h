/*
 * Copyright (C) 2018-2022 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#ifndef RAIN_STREAK_H
#define RAIN_STREAK_H

#include <deque>
#include "Active.h"
#include "HasTerminal.h"
#include "MatrixChar.h"

class Rain;

class RainStreak final : public Active, public HasTerminal {
	const Rain *rain;
	const unsigned x;
	unsigned y {0};
	const unsigned Length;
	bool FullyEnteredScreen {false};
	bool ReachedScreenMiddle {false};
	bool LeftScreenMiddle {false};
	bool OutOfScreen {false};
	std::deque<MatrixChar> MChars;
public:
	RainStreak(const Rain *R, unsigned col, unsigned len) :
		rain{R}, x{col}, Length{len} {}

	bool HasFullyEnteredScreen() const { return FullyEnteredScreen; }
	bool HasReachedScreenMiddle() const { return ReachedScreenMiddle; }
	bool HasLeftScreenMiddle() const { return LeftScreenMiddle; }
	bool IsOutOfScreen() const { return OutOfScreen; }
	void Update() final;
	void UpdateShadeColors();
	void RemoveGlowFromPreviousHead();
};

#endif
