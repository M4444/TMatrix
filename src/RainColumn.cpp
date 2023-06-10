/*
 * Copyright (C) 2018-2023 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include <string>
#include "Rain.h"
#include "RainColumn.h"
#include "Terminal.h"

void RainColumn::GenerateSpeeds(DecimalFraction speed)
{
	// Generates an array of integer speeds whose cumulative average is equal
	// to the specified speed. The order is also such that the average of any
	// sampled subset should be as close to the specified speed as possible
	// to create a nice, consistent visual.
	DecimalFraction speedAproximation {speed};
	DecimalFraction trueSum {speed};
	DecimalFraction sumOfIntegerSpeeds {0};
	while (true) {
		DecimalFraction integerSpeed {speedAproximation.GetFloor()};
		Speeds.emplace_back(integerSpeed.GetIntegerPart());
		if (integerSpeed == speedAproximation)
			return;
		sumOfIntegerSpeeds += integerSpeed;
		trueSum += speed;
		speedAproximation = trueSum - sumOfIntegerSpeeds;
	}
}

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
			terminal->DrawTitle(x, terminal->GetNumberOfRows()/2, TitleChar);
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
	for (int i = 0; i < Speeds[SpeedIndex]; i++) {
		Step();
	}
	SpeedIndex = (SpeedIndex + 1) % Speeds.size();
}
