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

class Rain : public Active {
	std::vector<RainColumn> RainColumns;

	int GetRandomSpeed();
public:
	Rain();

	void Update();
	int GetRandomLength();
	int GetRandomStartingGap();
	int GetRandomGap();
	std::pair<int, int> GetRandomUpdateRateAndTime();
};

#endif
