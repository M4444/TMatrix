/*
 * Copyright (C) 2018 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#ifndef RAIN_COLUMN_H
#define RAIN_COLUMN_H

#include <list>
#include "Active.h"
#include "CountdownTimer.h"
#include "RainStreak.h"
#include "Random.h"

class RainColumn : public Active {
	const int x;
	const int Speed;
	CountdownTimer GapTimer {Random::Random(4, 9)};
	bool EmptyRainStreakSlot {true};
	std::list<RainStreak> RainStreaks;
public:
	RainColumn(int X, int S) : x{X}, Speed{S} {}

	void Update();
};

#endif
