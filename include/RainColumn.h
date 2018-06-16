#ifndef _RAIN_COLUMN_H_
#define _RAIN_COLUMN_H_

#include <list>
#include "Active.h"
#include "RainStreak.h"
#include "Random.h"

class RainColumn : public Active {
	int x;
	int Speed;
	int UpdateTimer;
	bool EmptyRainSlot;
	std::list<RainStreak> RainStreaks;
public:
	RainColumn(int X, int S) : x(X), Speed(S), EmptyRainSlot(true) {
		UpdateTimer = Random::Random(4, 9);
	}

	void Update();
};

#endif
