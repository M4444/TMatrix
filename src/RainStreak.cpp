#include "RainStreak.h"
#include "Random.h"
#include "Terminal.h"

void RainStreak::Step()
{
	// Delete the tail MChar
	if (y >= Length) {
		if (!MChars.empty()) {
			MChars.pop_front();
		} else {
			OutOfScreen = true;
		}
	}
	// Remove glow from the previous MChar
	if (!MChars.empty()) {
		MChars.back().SetNotGlowing();
	}
	// Create a new MChar
	if (y < Terminal::getNumberOfRows()) {
		int UpdateRate = Random::Random(5, 7);
		int UpdateTimer = Random::Random(0, UpdateRate-1);

		MChars.push_back(MatrixChar(x, y, UpdateRate, UpdateTimer));
		MChars.back().Draw();
	}
	// Check if the tail MChar has entered the screen
	if (y >= Length) {
		FullyEnteredScreen = true;
	}
	y++;
}

void RainStreak::Update()
{
	if (!OutOfScreen) {
		// Move the rain streak
		for (int i = 0; i < Speed; i++) {
			Step();
		}
		// Update all the MChars
		for (MatrixChar &mc : MChars) {
			mc.Update();
		}
	}
}
