#ifndef _MATRIX_CHAR_H_
#define _MATRIX_CHAR_H_

#include <cstring>
#include <string>
#include <array>
#include "Active.h"

class MatrixChar : public Active {
	// Array of all the characters
	static constexpr std::array ALL_MCHARS = {
		"ﾊ", "ﾐ", "ﾋ", "ｰ", "ｳ", "ｼ", "ﾅ", "ﾓ", "ﾆ", "ｻ",
		"ﾜ", "ﾂ", "ｵ", "ﾘ", "ｱ", "ﾎ", "ﾃ", "ﾏ" ,"ｹ" ,"ﾒ",
		"ｴ", "ｶ", "ｷ", "ﾑ", "ﾕ", "ﾗ", "ｾ", "ﾈ", "ｽ", "ﾀ",
		"ﾇ", "ﾍ", "𐌇", "0", "1", "2", "3", "4", "5", "7",
		"8", "9", "Z", ":", ".", "･", "=", "*", "+", "-",
		"<", ">", "¦", "|", "╌", " ", "\""
	};

	// Coordinates
	const int x;
	const int y;
	const int UpdateRate;	// Usually ~5-7
	int UpdateTimer;
	int MCharIndex;
	bool Glowing;

	void SetRandomMatrixChar();
public:
	MatrixChar(int X, int Y, int UR, int UT) : x(X), y(Y), UpdateRate(UR),
		UpdateTimer(UT), MCharIndex(-1), Glowing(true) {
		SetRandomMatrixChar();
	}
	~MatrixChar() {
		Erase();
	}

	void Draw() const;
	void Erase() const;
	void Update();
	void SetNotGlowing();

	static constexpr std::size_t GetMaxMCharSize()
	{
		std::size_t longest = 0;
		for (const auto &MChar : ALL_MCHARS) {
			std::size_t current = std::strlen(MChar);
			if (current > longest) {
				longest = current;
			}
		}
		return longest;
	}
};

#endif
