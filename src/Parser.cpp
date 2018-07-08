/*
 * Copyright (C) 2018 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include <csignal>

namespace Parser {
	void Parse(char c)
	{
		switch (c) {
		case 'q':
		case 'Q':
			std::raise(SIGINT);
		}
	}
}
