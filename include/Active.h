/*
 * Copyright (C) 2018-2021 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#ifndef ACTIVE_H
#define ACTIVE_H

class Active {
public:
	virtual ~Active() = default;
	virtual void Update() = 0;
};

#endif
