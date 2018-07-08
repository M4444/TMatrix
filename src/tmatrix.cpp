/*
 * Copyright (C) 2018 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include <unistd.h>
#include "Parser.h"
#include "Rain.h"
#include "Terminal.h"

#define RUN_SPEED 100

int main(int argc, char *argv[])
{
	if (Parser::ParseCmdLineArgs(argc, argv)) {
		Terminal::getInstance();

		Rain rain {};
		while (true) {
			Parser::Parse(Terminal::ReadInputChar());
			usleep(1000*RUN_SPEED);

			rain.Update();
			Terminal::Flush();
		}
	}
}
