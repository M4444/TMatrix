/*
 * Copyright (C) 2018-2023 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include <random>
#include "Random.h"

namespace Random {
	static std::random_device RandomDevice {};
	static std::mt19937 RandomEngine {RandomDevice()};

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

	DecimalFraction Random(Range<DecimalFraction> range)
	{
		const DecimalFraction minDF {range.GetMin()};
		const DecimalFraction maxDF {range.GetMax()};
		const int min {minDF.GetIntegerPart() * 10 + minDF.GetFractionalPart()};
		const int max {maxDF.GetIntegerPart() * 10 + maxDF.GetFractionalPart()};
		const int random {Random(min, max)};
		return {random / 10, random % 10};
	}
}
