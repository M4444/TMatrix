#ifndef _RAIN_STREAK_H_
#define _RAIN_STREAK_H_

#include <deque>
#include "Active.h"
#include "MatrixChar.h"

class RainStreak : public Active {
	int x;
	int y;
	int Length;
	int Speed;
	bool FullyEnteredScreen;
	bool OutOfScreen;
	std::deque<MatrixChar> MChars;
public:
	RainStreak(int col, int Len, int S) : x(0), y(col), Length(Len),
		Speed(S), FullyEnteredScreen(false), OutOfScreen(false) {}

	bool IsOutOfScreen() { return OutOfScreen; }
	bool HasFullyEnteredScreen() { return FullyEnteredScreen; }

	void Step();
	void Update();
};

#endif
