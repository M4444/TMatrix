/*
 * Copyright (C) 2018-2021 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#ifndef RAIN_COLUMN_H
#define RAIN_COLUMN_H

#include <list>
#include "Active.h"
#include "CountdownTimer.h"
#include "HasTerminal.h"
#include "RainStreak.h"

class Rain;

class RainColumn : public Active, public HasTerminal {
	const Rain *rain;
	const unsigned x;
	const int Speed;
	CountdownTimer GapTimer;
	wchar_t TitleChar;
	const RainStreak *FirstRainStreak {nullptr};
	bool CreatedRainStreak {false};
	bool EmptyRainStreakSlot {true};
	std::list<RainStreak> RainStreaks;
public:
	RainColumn(const Rain *R, unsigned X, int S, int G, wchar_t TC) :
		rain{R}, x{X}, Speed{S}, GapTimer{G}, TitleChar{TC} {}

	void Step();
	void Update();
};

#endif
