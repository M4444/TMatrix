/*
 * Copyright (C) 2018-2023 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include <cmath>
#include "Rain.h"
#include "Random.h"
#include "Terminal.h"

Rain::Rain(const RainProperties& RP, Terminal* T) : Properties{RP}, terminal{T}
{
	RainColumn::SetTerminal(T);
	RainStreak::SetTerminal(T);
	MatrixChar::SetTerminal(T);
	Reset();
}

void Rain::Reset()
{
	// Create all the rain columns
	unsigned numberOfColumns {terminal->GetNumberOfColumns()};
	size_t titleLength {Properties.Title.length()};

	size_t titleCharIndex {0};
	RainColumns.clear();
	RainColumns.reserve(numberOfColumns);
	for (unsigned i = 0; i < numberOfColumns; i++) {
		bool titleColumn {numberOfColumns >= titleLength && titleLength > 0 &&
				  i + std::ceil(titleLength/2.0) >= numberOfColumns/2 &&
				  i < numberOfColumns/2 + std::floor(titleLength/2.0)};
		wchar_t titleChar {titleColumn ? Properties.Title[titleCharIndex++] : '\0'};
		RainColumns.emplace_back(this, i, GetRandomSpeed(), GetRandomStartingGap(),
					 titleChar);
	}
}

void Rain::Update()
{
	for (RainColumn &rc : RainColumns) {
		rc.Update();
	}
}

DecimalFraction Rain::GetRandomSpeed() const
{
	return Random::Random(Properties.RainColumnSpeed);
}

int Rain::GetRandomStartingGap() const
{
	return Random::Random(Properties.RainColumnStartingGap);
}

int Rain::GetRandomLength() const
{
	return Random::Random(Properties.RainStreakLength);
}

int Rain::GetRandomGap() const
{
	return Random::Random(Properties.RainColumnGap);
}

std::pair<int, int> Rain::GetRandomUpdateRateAndTime() const
{
	int UpdateRate {Random::Random(Properties.MCharUpdateRate)};
	int UpdateTime {UpdateRate ? Random::Random(UpdateRate) : 0};
	return {UpdateRate, UpdateTime};
}

void FadingRain::UpdateStreakColors(RainStreak& rainStreak) const
{
	rainStreak.UpdateShadeColors();
}

void NonFadingRain::UpdateStreakColors(RainStreak& rainStreak) const
{
	rainStreak.RemoveGlowFromPreviousHead();
}
