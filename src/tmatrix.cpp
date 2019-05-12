/*
 * Copyright (C) 2018-2019 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include <chrono>
#include <string_view>
#include <thread>
#include <vector>
#include "Parser.h"
#include "Rain.h"
#include "Terminal.h"
#include "tmatrix.h"

using namespace std::chrono_literals;

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
			std::this_thread::sleep_for(1.0s/stepsPerSecond);
		}
	}
}
