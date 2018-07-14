/*
 * Copyright (C) 2018 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include <memory>
#include "Rain.h"
#include "Random.h"
#include "Terminal.h"

Rain::Rain()
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
	return Random::Random(1, 2);
}

int Rain::GetRandomLength()
{
	return Random::Random(4, 20);
}

int Rain::GetRandomStartingGap()
{
	return Random::Random(4, 9);
}

int Rain::GetRandomGap()
{
	return Random::Random(4, 9);
}

std::pair<int, int> Rain::GetRandomUpdateRateAndTime()
{
	int UpdateRate {Random::Random(5, 7)};
	int UpdateTime {Random::Random(UpdateRate)};
	return {UpdateRate, UpdateTime};
}
