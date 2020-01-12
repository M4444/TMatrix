/*
 * Copyright (C) 2018-2020 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#ifndef RAIN_H
#define RAIN_H

#include <utility>
#include <vector>
#include "Active.h"
#include "Color.h"
#include "RainColumn.h"
#include "RainStreak.h"
#include "Range.h"
#include "Terminal.h"

struct RainProperties {
	Range<int> RainColumnSpeed;
	Range<int> RainColumnStartingGap;
	Range<int> RainColumnGap;
	Range<int> RainStreakLength;
	Range<int> MCharUpdateRate;
	bool Fade;
	Color CharacterColor;
	Color BackgroundColor;
	const char *Title;
};

class Rain : public Active {
	std::vector<RainColumn> RainColumns;
	const RainProperties Properties;
	Terminal* terminal;

	int GetRandomSpeed() const;
	int GetRandomStartingGap() const;
public:
	static constexpr RainProperties DEFAULT_PROPERTIES {
		{1, 1}, {10, 50}, {0, 40}, {1, 30}, {10, 20},
		true, Color::GetColor("green"), Color::GetColor("black"),
		" T M A T R I X "
	};
	static constexpr RainProperties DENSE_PROPERTIES {
		{1, 2}, {4, 9}, {4, 9}, {4, 20}, {5, 7},
		false, Color::GetColor("green"), Color::GetColor("default"),
		" T M A T R I X "
	};
	static constexpr int MAX_FALL_SPEED {10};
	static constexpr int MIN_LENGTH {1};

	Rain(RainProperties RP, Terminal* T);

	void Reset();
	void Update();
	virtual void UpdateStreakColors(RainStreak& rainStreak) const = 0;
	int GetRandomLength() const;
	int GetRandomGap() const;
	std::pair<int, int> GetRandomUpdateRateAndTime() const;
};

class FadingRain : public Rain {
public:
	FadingRain(RainProperties RP, Terminal* T) : Rain(RP, T) {};
	void UpdateStreakColors(RainStreak& rainStreak) const;
};

class NonFadingRain : public Rain {
public:
	NonFadingRain(RainProperties RP, Terminal* T) : Rain(RP, T) {};
	void UpdateStreakColors(RainStreak& rainStreak) const;
};

#endif
