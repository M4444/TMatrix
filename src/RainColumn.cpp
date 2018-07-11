/*
 * Copyright (C) 2018 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include "RainColumn.h"

void RainColumn::Update()
{
	if (!RainStreaks.empty()) {
		// Update all the RainStreaks
		for (RainStreak &rs : RainStreaks) {
			rs.Update();
		}
		// Delete RainStreaks that are out of screen
		if (RainStreaks.front().IsOutOfScreen()) {
			RainStreaks.pop_front();
		}
	}

	if (EmptyRainStreakSlot) {
		if (!GapTimer.HasExpired()) {
			GapTimer.Update();
		} else {
			// Create new streak
			int RandomLength = Random::Random(4, 20);

			RainStreaks.emplace_back(x, RandomLength, Speed);
			EmptyRainStreakSlot = false;
		}
	} else if (RainStreaks.back().HasFullyEnteredScreen()) {
		EmptyRainStreakSlot = true;
		GapTimer.ResetWithStartingTime(Random::Random(4, 9));
	}
}
