/*
 * Copyright (C) 2018 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#include <algorithm>
#include <cctype>
#include <csignal>
#include <cstdlib>
#include <iostream>
#include "Parser.h"
#include "tmatrix.h"

namespace Parser {
	bool ParseCmdLineArgs(int argc, char *argv[], int &StepsPerSecond)
	{
		for (int i = 1; i < argc; i++) {
			std::string_view argument {argv[i]};

			if (argument == "--version") {
				std::cout << "tmatrix version " << VERSION << '\n';
				std::cout << '\n';
				std::cout << "Copyright (C) 2018 Miloš Stojanović" << '\n';
				std::cout << "SPDX-License-Identifier: GPL-2.0-only" << '\n';
				return false;
			} else if (argument == "--help") {
				PrintUsage(true);
				return false;
			} else if (argument.substr(0, 2) == "-s") {
				std::string_view value;
				if (argument.length() == 2) {
					value = argv[++i];
				} else {
					value = argument.substr(2);
				}

				if (!SetStepsPerSecond(value, "-s", StepsPerSecond)) {
					return false;
				}
			} else if (argument.substr(0, 19) == "--steps-per-second=") {
				if (!SetStepsPerSecond(argument.substr(19), "--steps-per-second", StepsPerSecond)) {
					return false;
				}
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
		std::cout << "Usage: tmatrix [--version] [--help] [-s<value> | --steps-per-second=<value>]" << '\n';
		if (full) {
			std::cout << "Simulates the digital rain effect from The Matrix." << '\n';
			std::cout << '\n';
			std::cout << "  -s, --steps-per-second=<value>  - Run this many steps per second" << '\n';
			std::cout << "                                    <value> can range from ";
			std::cout << MIN_STEPS_PER_SECOND << " to " << MAX_STEPS_PER_SECOND << '\n';
			std::cout << "                                    The default value is ";
			std::cout << DEFAULT_STEPS_PER_SECOND << '\n';
			std::cout << "      --help                      - Display this help and exit" << '\n';
			std::cout << "      --version                   - Output version information and exit" << '\n';
		}
	}

	bool SetStepsPerSecond(std::string_view value, std::string_view option, int &StepsPerSecond)
	{
		if (value == nullptr) {
			std::cout << "No value specified for " << option << '.' << '\n';
			PrintUsage(false);
			return false;
		}

		try {
			StepsPerSecond = ReturnValidNumber(value);
			if (StepsPerSecond < MIN_STEPS_PER_SECOND ||
			    StepsPerSecond > MAX_STEPS_PER_SECOND) {
				throw std::out_of_range("");
			}
		} catch (const std::out_of_range&) {
			std::cout << "Invalid value '" << value << "' specified for " << option << '.' << '\n';
			std::cout << "Try 'tmatrix --help' for more information." << '\n';
			return false;
		}
		return true;
	}

	int ReturnValidNumber(std::string_view value)
	{
		if (std::any_of(value.begin(), value.end(),
		    [](unsigned char c) { return !std::isdigit(c); })) {
			return 0;
		}

		return std::atoi(value.data());
	}
}
