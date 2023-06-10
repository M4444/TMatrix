/*
 * Copyright (C) 2018-2023 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include "MatrixChar.h"
#include "Random.h"
#include "Terminal.h"

size_t MatrixChar::GetRandomMCharIndex()
{
	return static_cast<size_t>(Random::Random(ALL_MCHARS.size()));
}

void MatrixChar::SetRandomMChar()
{
	size_t newIndex {GetRandomMCharIndex()};
	while (MCharIndex == newIndex) {
		newIndex = GetRandomMCharIndex();
	}

	MCharIndex = newIndex;
}

void MatrixChar::Draw() const
{
	terminal->Draw(x, y, ALL_MCHARS[MCharIndex], ColorShade);
}

void MatrixChar::Erase() const
{
	terminal->Erase(x, y);
}

void MatrixChar::Update()
{
	if (UpdateTimer.IsZeroTimer()) {
		return;
	}

	if (UpdateTimer.HasExpired()) {
		UpdateTimer.Reset();
		SetRandomMChar();
		Draw();
	}
	UpdateTimer.Update();
}

void MatrixChar::SetColorShade(int colorShade)
{
	if (colorShade != ColorShade) {
		ColorShade = colorShade;
		Draw();
	}
}
