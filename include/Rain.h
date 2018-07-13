/*
 * Copyright (C) 2018 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#ifndef RAIN_H
#define RAIN_H

#include <vector>
#include "Active.h"
#include "RainColumn.h"

class Rain : public Active {
	std::vector<RainColumn> RainColumns;
public:
	Rain();

	void Update();
};

#endif
