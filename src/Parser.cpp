/*
 * Copyright (C) 2018 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include <csignal>
#include <iostream>
#include <string_view>
#include "Parser.h"

namespace Parser {
	bool ParseCmdLineArgs(int argc, char *argv[])
	{
		for (int i = 1; i < argc; i++) {
			std::string_view argument {argv[i]};

			if (argument == "--version") {
				std::cout << "tmatrix version 0.8" << '\n';
				std::cout << '\n';
				std::cout << "Copyright (C) 2018 Miloš Stojanović" << '\n';
				std::cout << "SPDX-License-Identifier: GPL-2.0-only" << '\n';
				return false;
			} else if (argument == "--help") {
				PrintUsage(true);
				return false;
			} else {
				std::cout << "Unknown option: " << argument << '\n';
				PrintUsage(false);
				return false;
			}
		}
		return true;
	}

	void Parse(char c)
	{
		switch (c) {
		case 'q':
		case 'Q':
			std::raise(SIGINT);
		}
	}

	void PrintUsage(bool full)
	{
		std::cout << "Usage: tmatrix [--version] [--help]" << '\n';
		if (full) {
			std::cout << "Simulates the digital rain effect from The Matrix." << '\n';
			std::cout << '\n';
			std::cout << "      --help     - Display this help and exit" << '\n';
			std::cout << "      --version  - Output version information and exit" << '\n';
		}
	}
}
