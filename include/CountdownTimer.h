/*
 * Copyright (C) 2018 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#ifndef COUNTDOWN_TIMER_H
#define COUNTDOWN_TIMER_H

#include <stdexcept>
#include "Active.h"

class CountdownTimer : public Active {
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

	void Update()
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
