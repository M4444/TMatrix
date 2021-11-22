/*
 * Copyright (C) 2018-2021 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#ifndef RAIN_H
#define RAIN_H

#include <string_view>
#include <utility>
#include <vector>
#include "Active.h"
#include "Color.h"
#include "DecimalFraction.h"
#include "RainColumn.h"
#include "RainStreak.h"
#include "Range.h"
#include "Terminal.h"

struct RainProperties {
	Range<DecimalFraction> RainColumnSpeed;
	Range<int> RainColumnStartingGap;
	Range<int> RainColumnGap;
	Range<int> RainStreakLength;
	Range<int> MCharUpdateRate;
	bool Fade;
	Color CharacterColor;
	Color BackgroundColor;
	std::wstring_view Title;
};

class Rain : public Active {
	std::vector<RainColumn> RainColumns;
	const RainProperties Properties;
	Terminal* terminal;

	DecimalFraction GetRandomSpeed() const;
	int GetRandomStartingGap() const;
public:
	static constexpr RainProperties DEFAULT_PROPERTIES {
		{{0, 5}, {1, 5}}, {10, 30}, {0, 40}, {1, 30}, {10, 20},
		true, Color::GetColor("green"), Color::GetColor("black"),
		L" T M A T R I X "
	};
	static constexpr RainProperties DENSE_PROPERTIES {
		{1, 2}, {4, 9}, {4, 9}, {4, 20}, {5, 7},
		false, Color::GetColor("green"), Color::GetColor("default"),
		L" T M A T R I X "
	};
	static constexpr DecimalFraction MAX_FALL_SPEED {10};
	static constexpr int MIN_LENGTH {1};

	Rain(const RainProperties& RP, Terminal* T);

	void Reset();
	void Update() final;
	virtual void UpdateStreakColors(RainStreak& rainStreak) const = 0;
	int GetRandomLength() const;
	int GetRandomGap() const;
	std::pair<int, int> GetRandomUpdateRateAndTime() const;
};

class FadingRain final : public Rain {
public:
	using Rain::Rain;
	void UpdateStreakColors(RainStreak& rainStreak) const;
};

class NonFadingRain final : public Rain {
public:
	using Rain::Rain;
	void UpdateStreakColors(RainStreak& rainStreak) const;
};

#endif
