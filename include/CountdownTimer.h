/*
 * Copyright (C) 2018-2023 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#ifndef COUNTDOWN_TIMER_H
#define COUNTDOWN_TIMER_H

#include <stdexcept>
#include "Active.h"

class CountdownTimer final : public Active {
	int StartingTime;
	int CurrentTime;
public:
	CountdownTimer(int ST) : StartingTime{ST}, CurrentTime{ST} {}
	CountdownTimer(int ST, int CT) : StartingTime{ST}, CurrentTime{CT} {
		if (CT > ST) {
			throw std::invalid_argument("Current time is greater than starting time.");
		}
	}

	bool HasExpired() const { return CurrentTime <= 0; }
	bool IsZeroTimer() const { return StartingTime == 0; }

	void Update() final
	{
		CurrentTime--;
	}
	void Reset()
	{
		CurrentTime = StartingTime;
	}
	void ResetWithStartingTime(int ST)
	{
		StartingTime = ST;
		Reset();
	}
};

#endif
