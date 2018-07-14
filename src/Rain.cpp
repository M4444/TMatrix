/*
 * Copyright (C) 2018 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include <memory>
#include "Rain.h"
#include "Random.h"
#include "Terminal.h"

Rain::Rain(RainProperties RP) : properties{RP}
{
	// Create all the rain columns
	std::shared_ptr<Rain> rain {this};
	int NumberOfColumns {Terminal::getNumberOfColumns()};

	RainColumns.reserve(NumberOfColumns);
	for (int i = 0; i < NumberOfColumns; i++) {
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
	return Random::Random(properties.Speed);
}

int Rain::GetRandomLength()
{
	return Random::Random(properties.RainStreakLength);
}

int Rain::GetRandomStartingGap()
{
	return Random::Random(properties.RainColumnStartingGap);
}

int Rain::GetRandomGap()
{
	return Random::Random(properties.RainColumnGap);
}

std::pair<int, int> Rain::GetRandomUpdateRateAndTime()
{
	int UpdateRate {Random::Random(properties.MCharUpdateRate)};
	int UpdateTime {Random::Random(UpdateRate)};
	return {UpdateRate, UpdateTime};
}
