/*
 * Copyright (C) 2018 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include "MatrixChar.h"
#include "Random.h"
#include "Terminal.h"

int MatrixChar::GetRandomMCharIndex()
{
	return Random::Random(0, ALL_MCHARS.size()-1);
}

void MatrixChar::SetRandomMChar()
{
	int NewIndex {GetRandomMCharIndex()};
	while (MCharIndex == NewIndex) {
		NewIndex = GetRandomMCharIndex();
	}

	MCharIndex = NewIndex;
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
	if (UpdateTimer.HasExpired()) {
		UpdateTimer.Reset();
		SetRandomMChar();
		Draw();
	}
	UpdateTimer.Update();
}

void MatrixChar::SetNotGlowing()
{
	Glowing = false;
	Draw();
}
