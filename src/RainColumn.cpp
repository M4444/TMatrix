#include "RainColumn.h"

void RainColumn::Update()
{
	// Update all the RainStreaks
	for (RainStreak &rs : RainStreaks) {
		rs.Update();
	}
	// Delete RainStreaks that are out of screen
	if (!RainStreaks.empty() && RainStreaks.front().IsOutOfScreen()) {
		RainStreaks.pop_front();
	}

	if (EmptyRainSlot && UpdateTimer > 0) {
		UpdateTimer--;
	} else if (EmptyRainSlot && UpdateTimer <= 0) {
		// Create new streak
		int RandomLength = rand() % 16 + 4;

		RainStreaks.push_back(RainStreak(x, RandomLength, Speed));

		EmptyRainSlot = false;
	} else if (RainStreaks.back().HasFullyEnteredScreen()) {
		EmptyRainSlot = true;
		UpdateTimer = rand() % 6 + 4;
	}
}
