#ifndef _MATRIX_CHAR_H_
#define _MATRIX_CHAR_H_

#include <string>
#include "Active.h"

#define NUM_OF_CHARS 57

class MatrixChar : public Active {
	// Array of all the characters
	static std::string ALL_MCHARS[NUM_OF_CHARS];
	// Coordinates
	int x;
	int y;
	int UpdateRate;	// Usually ~5-7
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

	void Draw();
	void Erase();
	void Update();
	void SetNotRainStreakHead();
};

#endif
