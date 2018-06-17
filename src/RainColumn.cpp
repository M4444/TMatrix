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
		if (GapTimer > 0) {
			GapTimer--;
		} else {
			// Create new streak
			int RandomLength = Random::Random(4, 20);

			RainStreaks.push_back(RainStreak(x, RandomLength, Speed));
			EmptyRainStreakSlot = false;
		}
	} else if (RainStreaks.back().HasFullyEnteredScreen()) {
		EmptyRainStreakSlot = true;
		GapTimer = Random::Random(4, 9);
	}
}
