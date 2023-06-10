/*
 * Copyright (C) 2018-2023 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#ifndef RAIN_COLUMN_H
#define RAIN_COLUMN_H

#include <list>
#include "Active.h"
#include "CountdownTimer.h"
#include "DecimalFraction.h"
#include "HasTerminal.h"
#include "RainStreak.h"
#include "Random.h"

class Rain;

class RainColumn final : public Active, public HasTerminal {
	const Rain *rain;
	const unsigned x;
	std::vector<int> Speeds;
	int SpeedIndex;
	CountdownTimer GapTimer;
	wchar_t TitleChar;
	const RainStreak *FirstRainStreak {nullptr};
	bool CreatedRainStreak {false};
	bool EmptyRainStreakSlot {true};
	std::list<RainStreak> RainStreaks;
public:
	RainColumn(const Rain *R, unsigned X, DecimalFraction S, int G, wchar_t TC) :
		rain{R}, x{X}, GapTimer{G}, TitleChar{TC}
	{
		GenerateSpeeds(S);
		SpeedIndex = Random::Random(Speeds.size());
	}

	void GenerateSpeeds(DecimalFraction Speed);

	void Step();
	void Update() final;
};

#endif
