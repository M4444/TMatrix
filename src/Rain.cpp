/*
 * Copyright (C) 2018-2019 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include <cmath>
#include <memory>
#include "Rain.h"
#include "Random.h"
#include "Terminal.h"

Rain::Rain(RainProperties RP) : Properties{RP}
{
	// Create all the rain columns
	std::shared_ptr<Rain> rain {this};
	int numberOfColumns {Terminal::GetNumberOfColumns()};
	int titleLength {static_cast<int>(std::strlen(Properties.Title))};

	int titleCharIndex {0};
	RainColumns.reserve(numberOfColumns);
	for (int i = 0; i < numberOfColumns; i++) {
		bool titleColumn {numberOfColumns >= titleLength && titleLength > 0 &&
				  i >= numberOfColumns/2 - std::ceil(titleLength/2.0) &&
				  i < numberOfColumns/2 + std::floor(titleLength/2.0)};
		char titleChar {titleColumn ? Properties.Title[titleCharIndex++] : '\0'};
		RainColumns.emplace_back(rain, i, GetRandomSpeed(), GetRandomStartingGap(),
					 titleChar);
	}
}

void Rain::Update()
{
	for (RainColumn &rc : RainColumns) {
		rc.Update();
	}
}

int Rain::GetRandomSpeed()
{
	return Random::Random(Properties.RainColumnSpeed);
}

int Rain::GetRandomStartingGap()
{
	return Random::Random(Properties.RainColumnStartingGap);
}

int Rain::GetRandomLength()
{
	return Random::Random(Properties.RainStreakLength);
}

int Rain::GetRandomGap()
{
	return Random::Random(Properties.RainColumnGap);
}

std::pair<int, int> Rain::GetRandomUpdateRateAndTime()
{
	int UpdateRate {Random::Random(Properties.MCharUpdateRate)};
	int UpdateTime {UpdateRate ? Random::Random(UpdateRate) : 0};
	return {UpdateRate, UpdateTime};
}
