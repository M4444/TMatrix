/*
 * Copyright (C) 2018-2019 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include "Rain.h"
#include "RainStreak.h"
#include "Terminal.h"

void RainStreak::Update()
{
	if (FullyEnteredScreen) {
		if (!MChars.empty()) {
			// Delete the tail MChar
			MChars.pop_back();
		} else {
			OutOfScreen = true;
		}
	}
	// Remove glow from the previous head MChar
	if (!MChars.empty()) {
		MChars.front().SetNotGlowing();
	}
	// Create a new head MChar
	if (y < Terminal::getNumberOfRows()) {
		auto [updateRate, updateTime] { rain->GetRandomUpdateRateAndTime() };

		MChars.emplace_front(x, y, updateRate, updateTime);
	}
	// Advance position
	y++;
	// Check if the tail MChar has entered the screen
	if (y >= Length) {
		FullyEnteredScreen = true;
	}
	// Update all the MChars
	for (MatrixChar &mc : MChars) {
		mc.Update();
	}
}
