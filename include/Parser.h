/*
 * Copyright (C) 2018 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#ifndef PARSER_H
#define PARSER_H

#include <array>
#include <functional>
#include <string>
#include <string_view>
#include <utility>
#include <vector>
#include "Rain.h"
#include "tmatrix.h"

namespace Parser {
	const int MAX_LINE_LENGTH {80};
	const int SHORT_GAP_PREFIX {2};
	const int LONG_GAP_PREFIX {6};
	const std::string SEPARATOR {"  - "};

	enum OptionType { VERSION, HELP, NUMERIC };
	struct Option {
		OptionType Type;
		std::string ShortLiteral;
		std::string LongLiteral;
		std::vector<std::string> HelpText;
		std::function<void(std::string_view, int &, RainProperties &)> ProcessArgument;

		std::string GetUsage() const;
		std::string GetLiterals() const;
		bool HasShortLiteral() const { return (ShortLiteral.length() != 0); }
		bool MatchesArgument (std::string_view argument) const;
		std::pair<std::string_view, std::string_view> GetPrefixSuffixSplit(std::string_view argument) const;
	};

	bool StartsWith(std::string_view str, std::string_view prefix);
	bool ParseCmdLineArgs(int argc, char *argv[], int &stepsPerSecond, RainProperties &rainProperties);
	void Parse(char c);

	//---VERSION------------------------------------------------------------
	void PrintVersion();
	//---HELP---------------------------------------------------------------
	void PrintUsage(bool full);
	std::vector<std::string> CreateUsageHeader();
	std::size_t FindLongestLiteralsLength();
	void PrintUsageLine(const Option &option, std::size_t longestLiterals);
	void PrintSpecificOptionType(OptionType type, std::size_t longestLiterals);
	//---SPTES-PER-SECONDS--------------------------------------------------
	void SetStepsPerSecond(std::string_view value, int &stepsPerSecond);
	int ReturnValidNumber(std::string_view value);
	//----------------------------------------------------------------------
	void SetRainProperties(RainProperties &rainProperties);

	const std::array Options {
		Option{
			VERSION, "", "--version",
			{ "Output version information and exit "},
			[](std::string_view, int &, RainProperties &) { PrintVersion(); }
		},
		Option{
			HELP, "", "--help",
			{ "Display this help and exit "},
			[](std::string_view, int &, RainProperties &) { PrintUsage(true); }
		},
		Option{
			NUMERIC, "-s", "--steps-per-second",
			{
				"Run this many steps per second",
				"<value> can range from " + std::to_string(MIN_STEPS_PER_SECOND) +
					" to " + std::to_string(MAX_STEPS_PER_SECOND),
				"The default value is " + std::to_string(DEFAULT_STEPS_PER_SECOND)
			},
			[](std::string_view value, int &stepsPerSecond, RainProperties &)
			{
				SetStepsPerSecond(value, stepsPerSecond);
			}
		}
	};
}

#endif
