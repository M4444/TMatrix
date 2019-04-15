/*
 * Copyright (C) 2018-2019 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include <string_view>
#include <unistd.h>
#include <vector>
#include "Parser.h"
#include "Rain.h"
#include "Terminal.h"
#include "tmatrix.h"

int main(int argc, char *argv[])
{
	bool paused {false};
	int stepsPerSecond {DEFAULT_STEPS_PER_SECOND};
	RainProperties rainProperties;

	if (Parser::ParseCmdLineArgs(std::vector<std::string_view>(argv+1, argv+argc),
				     stepsPerSecond, rainProperties)) {
		Terminal::getInstance();

		Rain rain {rainProperties};
		while (true) {
			if (!paused) {
				rain.Update();
				Terminal::Flush();
			}
			Parser::ParseRuntimeInput(Terminal::ReadInputChar(), paused);
			usleep(1000*1000/stepsPerSecond);
		}
	}
}
