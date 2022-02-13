/*
 * Copyright (C) 2018-2022 Miloš Stojanović
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
	rain->UpdateStreakColors(*this);
	unsigned numberOfRows {terminal->GetNumberOfRows()};
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
		if (y > numberOfRows/2 + Length + 1) {
			LeftScreenMiddle = true;
		}
	}
	// Update all the MChars
	for (MatrixChar &mc : MChars) {
		mc.Update();
	}
}

void RainStreak::UpdateShadeColors()
{
	if (!MChars.empty()) {
		for (MatrixChar &mc : MChars) {
			unsigned position = mc.GetVerticalOffset(y);
			if (position < Length/2) {
				mc.SetColorShade(1);
			} else if (position < (3*Length)/4) {
				mc.SetColorShade(2);
			} else if (position <= (7*Length)/8) {
				mc.SetColorShade(3);
			} else {
				mc.SetColorShade(4);
			}
		}
	}
}

void RainStreak::RemoveGlowFromPreviousHead()
{
	if (!MChars.empty()) {
		MChars.front().SetColorShade(1);
	}
}
