/*
 * Copyright (C) 2018 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#ifndef _PARSER_H_
#define _PARSER_H_

namespace Parser {
	bool ParseCmdLineArgs(int argc, char *argv[]);
	void Parse(char c);
	void PrintUsage(bool full);
}

#endif
