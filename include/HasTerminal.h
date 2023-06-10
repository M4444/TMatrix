/*
 * Copyright (C) 2018-2023 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#ifndef HAS_TERMINAL_H
#define HAS_TERMINAL_H

class Terminal;

struct HasTerminal {
	static Terminal* terminal;
	static void SetTerminal(Terminal* term)
	{
		terminal = term;
	}
};

#endif
