#include "RainStreak.h"
#include "Terminal.h"

void RainStreak::Step()
{
	x++;
	// Delete the tail MChar
	if (x > Length) {
		if (!MChars.empty()) {
			MChars.front().Erase();
			MChars.pop_front();
		} else {
			OutOfScreen = true;
		}
	}
	// Create a new MChar
	// FIXME: last row of the screen shouldn't be empty
	if (x < Terminal::getNumberOfRows()) {
		int UpdateRate = rand() % 3 + 5;
		int UpdateTimer = rand() % UpdateRate;

		MChars.push_back(MatrixChar(x, y, UpdateRate, UpdateTimer));
		MChars.back().Draw();
	}
	// Check if the tail MChar has entered the screen
	if (x >= Length) {
		FullyEnteredScreen = true;
	}
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
