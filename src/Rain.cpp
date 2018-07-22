/*
 * Copyright (C) 2018 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include <memory>
#include "Rain.h"
#include "Random.h"
#include "Terminal.h"

Rain::Rain(RainProperties RP) : Properties{RP}
{
	// Create all the rain columns
	std::shared_ptr<Rain> rain {this};
	int numberOfColumns {Terminal::getNumberOfColumns()};

	RainColumns.reserve(numberOfColumns);
	for (int i = 0; i < numberOfColumns; i++) {
		RainColumns.emplace_back(rain, i, GetRandomSpeed());
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
	return Random::Random(Properties.Speed);
}

int Rain::GetRandomLength()
{
	return Random::Random(Properties.RainStreakLength);
}

int Rain::GetRandomStartingGap()
{
	return Random::Random(Properties.RainColumnStartingGap);
}

int Rain::GetRandomGap()
{
	return Random::Random(Properties.RainColumnGap);
}

std::pair<int, int> Rain::GetRandomUpdateRateAndTime()
{
	int UpdateRate {Random::Random(Properties.MCharUpdateRate)};
	int UpdateTime {Random::Random(UpdateRate)};
	return {UpdateRate, UpdateTime};
}
