#ifndef _MATRIX_CHAR_H_
#define _MATRIX_CHAR_H_

#include <string>
#include <vector>
#include "Active.h"

class MatrixChar : public Active {
	// Array of all the characters
	static const std::vector<std::string> ALL_MCHARS;
	// Coordinates
	const int x;
	const int y;
	const int UpdateRate;	// Usually ~5-7
	int UpdateTimer;
	int MCharIndex;
	bool RainStreakHead;

	void SetRandomMatrixChar();
public:
	MatrixChar(int X, int Y, int UR, int UT) : x(X), y(Y), UpdateRate(UR),
		UpdateTimer(UT), MCharIndex(-1), RainStreakHead(true) {
		SetRandomMatrixChar();
	}
	~MatrixChar() {
		Erase();
	}

	void Draw() const;
	void Erase() const;
	void Update();
	void SetNotRainStreakHead();
};

#endif
