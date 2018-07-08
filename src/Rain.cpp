/*
 * Copyright (C) 2018 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include "Rain.h"
#include "Random.h"
#include "Terminal.h"

Rain::Rain()
{
	// Create all the rain columns
	int NumberOfColumns {Terminal::getNumberOfColumns()};

	RainColumns.reserve(NumberOfColumns);
	for (int i = 0; i < NumberOfColumns; i++) {
		int Speed {Random::Random(1, 2)};
		RainColumns.emplace_back(i, Speed);
	}
}

void Rain::Update()
{
	for (RainColumn &rc : RainColumns) {
		rc.Update();
	}
}
