/*
 * Copyright (C) 2018-2019 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#ifndef RAIN_H
#define RAIN_H

#include <utility>
#include <vector>
#include "Active.h"
#include "RainColumn.h"
#include "Range.h"
#include "Terminal.h"

struct RainProperties {
	Range<int> RainColumnSpeed;
	Range<int> RainColumnStartingGap;
	Range<int> RainColumnGap;
	Range<int> RainStreakLength;
	Range<int> MCharUpdateRate;
	const char *Color;
	const char *BackgroundColor;
	const char *Title;
};

class Rain : public Active {
	std::vector<RainColumn> RainColumns;
	const RainProperties Properties;

	int GetRandomSpeed() const;
	int GetRandomStartingGap() const;
public:
	static constexpr RainProperties DEFAULT_PROPERTIES {
		{1, 1}, {10, 50}, {0, 40}, {1, 30}, {10, 20},
		TerminalChar::GREEN_COLOR,
		TerminalChar::DEFAULT_BACKGROUND_COLOR,
		" T M A T R I X "
	};
	static constexpr RainProperties DENSE_PROPERTIES {
		{1, 2}, {4, 9}, {4, 9}, {4, 20}, {5, 7},
		TerminalChar::GREEN_COLOR,
		TerminalChar::DEFAULT_BACKGROUND_COLOR,
		" T M A T R I X "
	};
	static constexpr int MAX_FALL_SPEED {10};
	static constexpr int MIN_LENGTH {1};

	Rain(RainProperties RP);

	void Reset();
	void Update();
	int GetRandomLength() const;
	int GetRandomGap() const;
	std::pair<int, int> GetRandomUpdateRateAndTime() const;
};

#endif
