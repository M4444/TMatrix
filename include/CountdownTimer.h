/*
 * Copyright (C) 2018 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#ifndef _COUNTDOWN_TIMER_H_
#define _COUNTDOWN_TIMER_H_

class CountdownTimer : public Active {
	int StartingTime;
	int CurrentTime;
public:
	CountdownTimer(int ST) : StartingTime{ST}, CurrentTime{ST} {}
	CountdownTimer(int ST, int CT) : StartingTime{ST}, CurrentTime{CT} {}

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
