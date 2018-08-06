/*
 * Copyright (C) 2018 Miloš Stojanović
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

struct RainProperties {
	Range<int> RainColumnSpeed;
	Range<int> RainColumnStartingGap;
	Range<int> RainColumnGap;
	Range<int> RainStreakLength;
	Range<int> MCharUpdateRate;
};

class Rain : public Active {
	std::vector<RainColumn> RainColumns;
	const RainProperties Properties;

	int GetRandomSpeed();
	int GetRandomStartingGap();
public:
	static constexpr RainProperties DEFAULT_PROPERTIES {
		{1, 2}, {4, 9}, {4, 9}, {4, 20}, {5, 7}
	};
	static constexpr int MAX_FALL_SPEED {10};
	static constexpr int MIN_LENGTH {1};

	Rain(RainProperties RP);

	void Update();
	int GetRandomLength();
	int GetRandomGap();
	std::pair<int, int> GetRandomUpdateRateAndTime();
};

#endif
