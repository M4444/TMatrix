/*
 * Copyright (C) 2018-2020 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include <random>
#include <stdexcept>
#include "Random.h"

namespace Random {
	std::random_device RandomDevice {};
	std::mt19937 RandomEngine {RandomDevice()};

	int Random(int min, int max)
	{
		if (min > max) {
			throw std::range_error("Min is greater than max.");
		}

		std::uniform_int_distribution<> distribution {min, max};
		return distribution(RandomEngine);
	}

	int Random(Range<int> range)
	{
		return Random(range.GetMin(), range.GetMax());
	}

	int Random(int range)
	{
		return Random(0, range-1);
	}
}
