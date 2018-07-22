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
	Range<int> Speed;
	Range<int> RainStreakLength;
	Range<int> RainColumnStartingGap;
	Range<int> RainColumnGap;
	Range<int> MCharUpdateRate;
};

class Rain : public Active {
	std::vector<RainColumn> RainColumns;
	const RainProperties Properties;

	int GetRandomSpeed();
public:
	Rain(RainProperties RP);

	void Update();
	int GetRandomLength();
	int GetRandomStartingGap();
	int GetRandomGap();
	std::pair<int, int> GetRandomUpdateRateAndTime();
};

#endif
