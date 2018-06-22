#include "MatrixChar.h"
#include "Random.h"
#include "Terminal.h"

void MatrixChar::SetRandomMatrixChar()
{
	int RandomIndex;

	// Get a random index different from the current one
	do {
		RandomIndex = Random::Random(0, ALL_MCHARS.size()-1);
	} while (RandomIndex == MCharIndex);
	MCharIndex = RandomIndex;
}

void MatrixChar::Draw() const
{
	Terminal::Draw(x, y, ALL_MCHARS[MCharIndex], Glowing);
}

void MatrixChar::Erase() const
{
	Terminal::Erase(x, y);
}

void MatrixChar::Update()
{
	// When the timer expires restart it and change the MChar
	if (UpdateTimer <= 0) {
		SetRandomMatrixChar();
		UpdateTimer = UpdateRate;
		Draw();
	}
	UpdateTimer--;
}

void MatrixChar::SetNotGlowing()
{
	Glowing = false;
	Draw();
}
