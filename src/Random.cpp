/*
 * Copyright (C) 2018-2020 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include <random>
#include "Random.h"

namespace Random {
	std::random_device RandomDevice {};
	std::mt19937 RandomEngine {RandomDevice()};

	int Random(Range<int> range)
	{
		std::uniform_int_distribution<> distribution {range.GetMin(), range.GetMax()};
		return distribution(RandomEngine);
	}

	int Random(int min, int max)
	{
		return Random(Range(min, max));
	}

	int Random(int range)
	{
		return Random(Range(range));
	}
}
