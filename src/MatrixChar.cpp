#include "MatrixChar.h"
#include "Random.h"
#include "Terminal.h"

const std::vector<std::string> MatrixChar::ALL_MCHARS = {
	"ﾊ", "ﾐ", "ﾋ", "ｰ", "ｳ", "ｼ", "ﾅ", "ﾓ", "ﾆ", "ｻ",
	"ﾜ", "ﾂ", "ｵ", "ﾘ", "ｱ", "ﾎ", "ﾃ", "ﾏ" ,"ｹ" ,"ﾒ",
	"ｴ", "ｶ", "ｷ", "ﾑ", "ﾕ", "ﾗ", "ｾ", "ﾈ", "ｽ", "ﾀ",
	"ﾇ", "ﾍ", "𐌇", "0", "1", "2", "3", "4", "5", "7",
	"8", "9", "Z", ":", ".", "･", "=", "*", "+", "-",
	"<", ">", "¦", "|", "╌", " ", "\""
};

void MatrixChar::SetRandomMatrixChar()
{
	int RandomIndex;

	do {
		RandomIndex = Random::Random(0, ALL_MCHARS.size()-1);
	} while (RandomIndex == MCharIndex);
	MCharIndex = RandomIndex;
}

void MatrixChar::Draw()
{
	Terminal::Draw(x, y, ALL_MCHARS[MCharIndex], RainStreakHead);
}

void MatrixChar::Erase()
{
	Terminal::Erase(x, y);
}


void MatrixChar::Update()
{
	if (UpdateTimer <= 0) {
		SetRandomMatrixChar();
		UpdateTimer = UpdateRate;
		Draw();
	}
	UpdateTimer--;
}

void MatrixChar::SetNotRainStreakHead()
{
	RainStreakHead = false;
	Draw();
}
