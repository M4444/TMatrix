/*
 * Copyright (C) 2018 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#ifndef PARSER_H
#define PARSER_H

#include <string_view>
#include "Rain.h"

namespace Parser {
	bool ParseCmdLineArgs(int argc, char *argv[], int &StepsPerSecond, RainProperties &rainProperties);
	void Parse(char c);
	void PrintUsage(bool full);
	bool SetStepsPerSecond(std::string_view value, std::string_view option, int &SpepsPerSecond);
	int ReturnValidNumber(std::string_view value);
	void SetRainProperties(RainProperties &rainProperties);
}

#endif
