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
	Rain(RainProperties RP);

	void Update();
	int GetRandomLength();
	int GetRandomGap();
	std::pair<int, int> GetRandomUpdateRateAndTime();
};

#endif
