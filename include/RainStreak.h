#ifndef _RAIN_STREAK_H_
#define _RAIN_STREAK_H_

#include <deque>
#include "Active.h"
#include "MatrixChar.h"

class RainStreak : public Active {
	const int x;
	int y;
	const int Length;
	const int Speed;
	bool FullyEnteredScreen;
	bool OutOfScreen;
	std::deque<MatrixChar> MChars;
public:
	RainStreak(int col, int Len, int S) : x(col), y(0), Length(Len),
		Speed(S), FullyEnteredScreen(false), OutOfScreen(false) {}

	bool IsOutOfScreen() const { return OutOfScreen; }
	bool HasFullyEnteredScreen() const { return FullyEnteredScreen; }

	void Step();
	void Update();
};

#endif
