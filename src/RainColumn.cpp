/*
 * Copyright (C) 2018-2019 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include "Rain.h"
#include "RainColumn.h"
#include "Terminal.h"

void RainColumn::Step()
{
	if (EmptyRainStreakSlot) {
		if (!GapTimer.HasExpired()) {
			GapTimer.Update();
		} else {
			// Create new streak
			RainStreaks.emplace_back(rain, x, rain->GetRandomLength());
			if (!CreatedRainStreak) {
				FirstRainStreak = &RainStreaks.back();
				CreatedRainStreak = true;
			}
			EmptyRainStreakSlot = false;
		}
	}

	if (!RainStreaks.empty()) {
		// Update all the RainStreaks
		for (RainStreak &rs : RainStreaks) {
			rs.Update();
		}

		const auto& Head {RainStreaks.back()};
		// Check if a title character needs to be drawn
		bool ContainsTitle {TitleChar != '\0'};
		if (ContainsTitle && FirstRainStreak &&
		    FirstRainStreak->HasReachedScreenMiddle() &&
		    !FirstRainStreak->HasLeftScreenMiddle() && TitleChar != ' ') {
			Terminal::Draw(x, Terminal::GetNumberOfRows()/2,
				       std::string(1, TitleChar), true);
		}
		// Check if an empty slot appeared
		if ((!ContainsTitle || !FirstRainStreak ||
		     FirstRainStreak->HasReachedScreenMiddle()) &&
		    Head.HasFullyEnteredScreen() && !EmptyRainStreakSlot) {
			EmptyRainStreakSlot = true;
			GapTimer.ResetWithStartingTime(rain->GetRandomGap());
		}

		// Delete RainStreaks that are out of screen
		while (!RainStreaks.empty() && RainStreaks.front().IsOutOfScreen()) {
			RainStreaks.pop_front();
			FirstRainStreak = nullptr;
		}
	}
}

void RainColumn::Update()
{
	for (int i = 0; i < Speed; i++) {
		Step();
	}
}
