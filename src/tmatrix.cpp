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

int StepsPerSecond {DEFAULT_STEPS_PER_SECOND};

int main(int argc, char *argv[])
{
	if (Parser::ParseCmdLineArgs(argc, argv)) {
		Terminal::getInstance();

		Rain rain {{ {1, 2}, {4, 20}, {4, 9}, {4, 9}, {5, 7} }};
		while (true) {
			Parser::Parse(Terminal::ReadInputChar());
			usleep(1000*1000/StepsPerSecond);

			rain.Update();
			Terminal::Flush();
		}
	}
}
