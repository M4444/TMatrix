/*
 * Copyright (C) 2018 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#ifndef _RANDOM_H_
#define _RANDOM_H_

namespace Random {
	// Returns a random integer in the range [min, max]
	int Random(int min, int max);
	// Returns a random integer in the range [0, range-1]
	int Random(int range);
}

#endif
