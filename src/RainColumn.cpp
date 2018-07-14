/*
 * Copyright (C) 2018 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include "Rain.h"
#include "RainColumn.h"

RainColumn::RainColumn(const std::shared_ptr<Rain> &R, int X, int S) : rain{R},
	x{X}, Speed{S}, GapTimer{R->GetRandomStartingGap()} {}

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
			RainStreaks.emplace_back(rain, x, rain->GetRandomLength(), Speed);
			EmptyRainStreakSlot = false;
		}
	} else if (RainStreaks.back().HasFullyEnteredScreen()) {
		EmptyRainStreakSlot = true;
		GapTimer.ResetWithStartingTime(rain->GetRandomGap());
	}
}
