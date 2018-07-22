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
#include <stdexcept>
#include "Parser.h"

namespace Parser {
	std::string Option::GetUsage() const
	{
		switch (Type) {
		case VERSION:
		case HELP:
			return "[" + LongLiteral + ']';
			break;
		case NUMERIC:
			if (ShortLiteral != "" && LongLiteral != "") {
				return "[" + ShortLiteral + "<value> | " + LongLiteral + "=<value>]";
			} else if (ShortLiteral != "") {
				return "[" + ShortLiteral + "<value>]";
			} else {
				return "[" + LongLiteral + "=<value>]";
			}
			break;
		}
		return "";
	}

	std::string Option::GetLiterals() const
	{
		switch (Type) {
		case VERSION:
		case HELP:
			return LongLiteral;
			break;
		case NUMERIC:
			if (ShortLiteral != "" && LongLiteral != "") {
				return ShortLiteral + ", " + LongLiteral + "=<value>";
			} else if (ShortLiteral != "") {
				return ShortLiteral;
			} else {
				return LongLiteral + "=<value>";
			}
			break;
		}
		return "";
	}

	std::pair<std::string_view, std::string_view> Option::GetPrefixSuffixSplit(std::string_view argument) const
	{
		std::string literal;
		if (StartsWith(argument, "--")) {
			literal = LongLiteral;
			if (Type == NUMERIC) {
				literal += '=';
			}
		} else {
			literal = ShortLiteral;
		}

		if (argument.size() < literal.size()) {
			return {"", ""};
		}
		std::string_view prefix = argument.substr(0, literal.length());
		std::string_view suffix = argument.substr(literal.length());
		if (prefix != literal) {
			// The prefix doesn't match so the split is invalid
			return {"", ""};
		}
		return {prefix, suffix};
	}

	bool Option::MatchesArgument (std::string_view argument) const
	{
		auto [prefix, suffix] = GetPrefixSuffixSplit(argument);
		return (prefix != "");
	}

	//---Parser-functions---------------------------------------------------
	bool StartsWith(std::string_view str, std::string_view prefix) {
		return (str.substr(0, prefix.length()) == prefix);
	}

	bool ParseCmdLineArgs(int argc, char *argv[], int &stepsPerSecond, RainProperties &rainProperties)
	{
		SetRainProperties(rainProperties);
		for (int i = 1; i < argc; i++) {
			std::string_view argument {argv[i]};

			bool matched {false};
			for (const Option &option : Options) {
				if (!option.MatchesArgument(argument)) {
					continue;
				}
				auto [prefix, suffix] = option.GetPrefixSuffixSplit(argument);
				matched = true;
				switch(option.Type) {
				case VERSION:
				case HELP:
					if (suffix != "") {
						matched = false;
						break;
					}
					option.ProcessArgument(argument, stepsPerSecond, rainProperties);
					return false;
					break;
				case NUMERIC:
					if (suffix == "") {
						suffix = argv[++i];
						if (suffix == nullptr || StartsWith(prefix, "--")) {
							std::cout << "No value specified for " << argument << '\n';
							PrintUsage(false);
							return false;
						}
					}

					try {
						option.ProcessArgument(suffix, stepsPerSecond, rainProperties);
					} catch (const std::out_of_range&) {
						std::cout << "Invalid value '" << suffix;
						std::cout << "' specified for " << prefix << '\n';
						std::cout << "Try 'tmatrix --help' for more information." << '\n';
						return false;
					}
					break;
				}
			}
			if (!matched) {
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

	//---VERSION------------------------------------------------------------
	void PrintVersion()
	{
		std::cout << "tmatrix version " << VERSION_NUMBER << '\n';
		std::cout << '\n';
		std::cout << "Copyright (C) 2018 Miloš Stojanović" << '\n';
		std::cout << "SPDX-License-Identifier: GPL-2.0-only" << '\n';
	}

	//---HELP---------------------------------------------------------------
	void PrintUsage(bool full)
	{
		std::vector<std::string> header {CreateUsageHeader()};
		for (std::string_view line : header) {
			std::cout << line << '\n';
		}

		if (full) {
			std::cout << "Simulates the digital rain effect from The Matrix." << '\n';
			std::cout << '\n';

			std::size_t longestLiterals {FindLongestLiteralsLength()};
			for (const Option &option : Options) {
				if (option.Type != HELP && option.Type != VERSION) {
					PrintUsageLine(option, longestLiterals);
				}
			}
			// Print help and version at the end
			PrintSpecificOptionType(HELP, longestLiterals);
			PrintSpecificOptionType(VERSION, longestLiterals);
		}
	}

	std::vector<std::string> CreateUsageHeader()
	{
		std::vector<std::string> usage {"Usage: tmatrix"};
		const int USAGE_START_LENGTH = usage.back().length();

		for (const Option &option : Options) {
			if (usage.back().length() + 1 + option.GetUsage().length() > MAX_LINE_LENGTH) {
				usage.emplace_back(USAGE_START_LENGTH, ' ');
			}
			usage.back() += ' ' + option.GetUsage();
		}

		return usage;
	}

	std::size_t FindLongestLiteralsLength()
	{
		std::size_t longest {0};
		for (const Option &option : Options) {
			std::size_t current {option.GetLiterals().length()};
			current += option.HasShortLiteral() ? SHORT_GAP_PREFIX : LONG_GAP_PREFIX;
			if (current > longest) {
				longest = current;
			}
		}

		return longest;
	}

	void PrintUsageLine(const Option &option, std::size_t longestLiterals)
	{
		int gapSize {option.HasShortLiteral() ? SHORT_GAP_PREFIX : LONG_GAP_PREFIX};
		std::string line(gapSize, ' ');
		line += option.GetLiterals();
		line += std::string(longestLiterals-line.length(), ' ');
		line += SEPARATOR;
		for (std::size_t i = 0; i < option.HelpText.size(); i++) {
			if (i != 0) {
				line += std::string(longestLiterals+SEPARATOR.length(), ' ');
			}
			line += option.HelpText[i];
			line += '\n';
		}
		std::cout << line;
	}

	void PrintSpecificOptionType(OptionType type, std::size_t longestLiterals)
	{
		for (const Option &option : Options) {
			if (option.Type == type) {
				PrintUsageLine(option, longestLiterals);
			}
		}
	}

	//---SPTES-PER-SECONDS--------------------------------------------------
	void SetStepsPerSecond(std::string_view value, int &stepsPerSecond)
	{
		stepsPerSecond = ReturnValidNumber(value);
		if (stepsPerSecond < MIN_STEPS_PER_SECOND ||
		    stepsPerSecond > MAX_STEPS_PER_SECOND) {
			throw std::out_of_range("");
		}
	}

	int ReturnValidNumber(std::string_view value)
	{
		if (value.length() == 0 ||
		    std::any_of(value.begin(), value.end(),
		    [](unsigned char c) { return !std::isdigit(c); })) {
			return 0;
		}

		return std::atoi(value.data());
	}

	//----------------------------------------------------------------------
	void SetRainProperties(RainProperties &rainProperties)
	{
		rainProperties = { {1, 2}, {4, 20}, {4, 9}, {4, 9}, {5, 7} };
	}
}
