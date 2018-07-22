/*
 * Copyright (C) 2018 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include "Rain.h"
#include "RainColumn.h"

RainColumn::RainColumn(const std::shared_ptr<Rain> &R, int X, int S) : rain{R},
	x{X}, Speed{S}, GapTimer{R->GetRandomStartingGap()} {}

void RainColumn::Step()
{
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
	}
}

void RainColumn::Update()
{
	for (int i = 0; i < Speed; i++) {
		Step();
	}
}
