/*
 * Copyright (C) 2018-2020 Miloš Stojanović
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
	int numberOfRows {Terminal::GetNumberOfRows()};
	// Create a new head MChar
	if (y < numberOfRows) {
		auto [updateRate, updateTime] { rain->GetRandomUpdateRateAndTime() };

		MChars.emplace_front(x, y, updateRate, updateTime);
	}
	// Advance position
	y++;
	// Check if the tail MChar has entered the screen
	if (y >= Length) {
		FullyEnteredScreen = true;
	}
	// Check if the head MChar has reached the screen middle
	if (y > numberOfRows/2) {
		ReachedScreenMiddle = true;
		if (y-Length-1 > numberOfRows/2) {
			LeftScreenMiddle = true;
		}
	}
	// Update all the MChars
	for (MatrixChar &mc : MChars) {
		mc.Update();
	}
}
