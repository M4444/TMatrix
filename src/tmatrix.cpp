/*
 * Copyright (C) 2018 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include <unistd.h>
#include "Parser.h"
#include "Rain.h"
#include "Terminal.h"
#include "tmatrix.h"

int main(int argc, char *argv[])
{
	int stepsPerSecond {DEFAULT_STEPS_PER_SECOND};
	RainProperties rainProperties;

	if (Parser::ParseCmdLineArgs(argc, argv, stepsPerSecond, rainProperties)) {
		Terminal::getInstance();

		Rain rain {rainProperties};
		while (true) {
			Parser::Parse(Terminal::ReadInputChar());
			usleep(1000*1000/stepsPerSecond);

			rain.Update();
			Terminal::Flush();
		}
	}
}
