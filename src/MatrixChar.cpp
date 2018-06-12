#include "MatrixChar.h"

std::string MatrixChar::ALL_MCHARS[NUM_OF_CHARS] = {
	"ﾊ", "ﾐ", "ﾋ", "ｰ", "ｳ", "ｼ", "ﾅ", "ﾓ", "ﾆ", "ｻ",
	"ﾜ", "ﾂ", "ｵ", "ﾘ", "ｱ", "ﾎ", "ﾃ", "ﾏ" ,"ｹ" ,"ﾒ",
	"ｴ", "ｶ", "ｷ", "ﾑ", "ﾕ", "ﾗ", "ｾ", "ﾈ", "ｽ", "ﾀ",
	"ﾇ", "ﾍ", "𐌇", "0", "1", "2", "3", "4", "5", "7",
	"8", "9", "Z", ":", ".", "･", "=", "*", "+", "-",
	"<", ">", "¦", "|", "╌", " ", "\""
};

void MatrixChar::SetRandomMatrixChar() {
	int RandomIndex;

	do {
		RandomIndex = rand() % NUM_OF_CHARS;
	} while (RandomIndex == MCharIndex);
	MCharIndex = RandomIndex;
}

void MatrixChar::Draw()
{
        printf("\033[%d;%dH%s\n", x, y, ALL_MCHARS[MCharIndex].c_str());
}

void MatrixChar::Erase()
{
        printf("\033[%d;%dH%s\n", x, y, " ");
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
