/*
 * Copyright (C) 2018 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include "Rain.h"
#include "RainColumn.h"

void RainColumn::Step()
{
	if (EmptyRainStreakSlot) {
		if (!GapTimer.HasExpired()) {
			GapTimer.Update();
		} else {
			// Create new streak
			RainStreaks.emplace_back(rain, x, rain->GetRandomLength(), Speed);
			EmptyRainStreakSlot = false;
		}
	}

	if (!RainStreaks.empty()) {
		// Update all the RainStreaks
		for (RainStreak &rs : RainStreaks) {
			rs.Update();
		}

		// Check if an empty slot appeared
		if (RainStreaks.back().HasFullyEnteredScreen() && !EmptyRainStreakSlot) {
			EmptyRainStreakSlot = true;
			GapTimer.ResetWithStartingTime(rain->GetRandomGap());
		}

		// Delete RainStreaks that are out of screen
		while (!RainStreaks.empty() && RainStreaks.front().IsOutOfScreen()) {
			RainStreaks.pop_front();
		}
	}
}

void RainColumn::Update()
{
	for (int i = 0; i < Speed; i++) {
		Step();
	}
}
