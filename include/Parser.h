/*
 * Copyright (C) 2018-2019 Miloš Stojanović
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
	constexpr int MAX_LINE_LENGTH {80};
	constexpr int SHORT_GAP_PREFIX {2};
	constexpr int LONG_GAP_PREFIX {6};
	constexpr std::string_view SEPARATOR {"  - "};

	enum OptionType { VERSION, HELP, MODE, NUMERIC, RANGE, COLOR, TEXT };
	struct Option {
		const OptionType Type;
		const std::string ShortLiteral;
		const std::string LongLiteral;
		const std::vector<std::string> HelpText;
		const std::function<void(std::string_view, int &, RainProperties &)> ProcessArgument;

		static std::string GetValueName(OptionType type);
		std::string GetUsage() const;
		std::string GetLiterals() const;
		bool HasShortLiteral() const { return (ShortLiteral.length() != 0); }
		bool MatchesArgument (std::string_view argument) const;
		std::pair<std::string_view, std::string_view> GetPrefixSuffixSplit(std::string_view argument) const;
	};

	//---Parser-functions---------------------------------------------------
	bool StartsWith(std::string_view str, std::string_view prefix);
	bool ParseCmdLineArgs(std::vector<std::string_view> arguments,
			      int &stepsPerSecond, RainProperties &rainProperties);
	void PrintInvalidValue(std::string_view prefix, std::string_view suffix);

	void ParseRuntimeInput(char c, bool &paused);

	//---VERSION------------------------------------------------------------
	void PrintVersion();
	//---HELP---------------------------------------------------------------
	void PrintUsage(bool full);
	std::vector<std::string> CreateUsageHeader();
	std::size_t FindLongestLiteralsLength();
	void PrintUsageLine(const Option &option, std::size_t longestLiterals);
	void PrintSpecificOptionType(OptionType type, std::size_t longestLiterals);
	//---STEPS-PER-SECONDS--------------------------------------------------
	void SetStepsPerSecond(std::string_view value, int &stepsPerSecond);
	int ReturnValidNumber(std::string_view value);
	//----------------------------------------------------------------------
	void SetRainProperties(std::string_view mode, RainProperties &rainProperties);
	//---RANGE--------------------------------------------------------------
	Range<int> SplitRange(std::string_view range);
	//---SPEED--------------------------------------------------------------
	void SetSpeedRange(std::string_view range, RainProperties &rainProperties);
	//---LENGTH-------------------------------------------------------------
	void SetLengthRange(std::string_view range, RainProperties &rainProperties);
	//---STARTING-GAP-RANGE-------------------------------------------------
	void SetStartingGapRange(std::string_view range, RainProperties &rainProperties);
	//---GAP-RANGE----------------------------------------------------------
	void SetGapRange(std::string_view range, RainProperties &rainProperties);
	//---CHARACTER-UPDATE-RATE----------------------------------------------
	void SetCharUpdateRateRange(std::string_view range, RainProperties &rainProperties);
	//---COLOR--------------------------------------------------------------
	void SetColor(std::string_view color, RainProperties &rainProperties);
	//---BACKGROUND-COLOR---------------------------------------------------
	void SetBackgroundColor(std::string_view color, RainProperties &rainProperties);
	//---TITLE--------------------------------------------------------------
	void SetTitle(std::string_view title, RainProperties &rainProperties);

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
			MODE, "", "--mode",
			{
				"Set the mode of the rain",
				"Available modes: default, dense"
			},
			[](std::string_view mode, int &, RainProperties &rainProperties)
			{
				SetRainProperties(mode, rainProperties);
			}
		},
		Option{
			NUMERIC, "-s", "--steps-per-sec",
			{
				"Run this many steps per second",
				"<value> can range from " + std::to_string(MIN_STEPS_PER_SECOND) +
					" to " + std::to_string(MAX_STEPS_PER_SECOND),
				"Default: " + std::to_string(DEFAULT_STEPS_PER_SECOND)
			},
			[](std::string_view value, int &stepsPerSecond, RainProperties &)
			{
				SetStepsPerSecond(value, stepsPerSecond);
			}
		},
		Option{
			RANGE, "-f", "--fall-speed",
			{
				"Set the range for the fall speed",
				"The maximal fall speed value is " + std::to_string(Rain::MAX_FALL_SPEED),
				"Default: " +
					std::to_string(Rain::DEFAULT_PROPERTIES.RainColumnSpeed.GetMin()) + ',' +
					std::to_string(Rain::DEFAULT_PROPERTIES.RainColumnSpeed.GetMax())

			},
			[](std::string_view range, int &, RainProperties &rainProperties)
			{
				SetSpeedRange(range, rainProperties);
			}
		},
		Option{
			RANGE, "-G", "--start-gap",
			{
				"Set the range for the starting gaps",
				"Default: " +
					std::to_string(Rain::DEFAULT_PROPERTIES.RainColumnStartingGap.GetMin()) + ',' +
					std::to_string(Rain::DEFAULT_PROPERTIES.RainColumnStartingGap.GetMax())
			},
			[](std::string_view range, int &, RainProperties &rainProperties)
			{
				SetStartingGapRange(range, rainProperties);
			}
		},
		Option{
			RANGE, "-g", "--gap",
			{
				"Set the range for the gaps between streaks",
				"Default: " +
					std::to_string(Rain::DEFAULT_PROPERTIES.RainColumnGap.GetMin()) + ',' +
					std::to_string(Rain::DEFAULT_PROPERTIES.RainColumnGap.GetMax())
			},
			[](std::string_view range, int &, RainProperties &rainProperties)
			{
				SetGapRange(range, rainProperties);
			}
		},
		Option{
			RANGE, "-l", "",
			{
				"Set the range for the length of rain streaks",
				"The minimal length value is " + std::to_string(Rain::MIN_LENGTH),
				"Default: " +
					std::to_string(Rain::DEFAULT_PROPERTIES.RainStreakLength.GetMin()) + ',' +
					std::to_string(Rain::DEFAULT_PROPERTIES.RainStreakLength.GetMax())
			},
			[](std::string_view range, int &, RainProperties &rainProperties)
			{
				SetLengthRange(range, rainProperties);
			}
		},
		Option{
			RANGE, "-r", "",
			{
				"Set the range for the update rate of the",
				"Matrix characters",
				"The values correspond to the number of steps",
				"before the change and 0 represents no change",
				"Default: " +
					std::to_string(Rain::DEFAULT_PROPERTIES.MCharUpdateRate.GetMin()) + ',' +
					std::to_string(Rain::DEFAULT_PROPERTIES.MCharUpdateRate.GetMax())
			},
			[](std::string_view range, int &, RainProperties &rainProperties)
			{
				SetCharUpdateRateRange(range, rainProperties);
			}
		},
		Option{
			COLOR, "-C", "--color",
			{
				"Set the color of the Matrix characters",
				"Available colors: default, white, gray, black,",
				"red, green, yellow, blue, magenta, cyan",
				"Default: green"
			},
			[](std::string_view color, int &, RainProperties &rainProperties)
			{
				SetColor(color, rainProperties);
			}
		},
		Option{
			COLOR, "-c", "--bakcground",
			{
				"Set the color of the background",
				"Available colors: default, white, gray, black,",
				"red, green, yellow, blue, magenta, cyan"
			},
			[](std::string_view color, int &, RainProperties &rainProperties)
			{
				SetBackgroundColor(color, rainProperties);
			}
		},
		Option{
			TEXT, "-t", "--title",
			{
				"Set the title that appears in the rain",
				"Note: the title needs to fit within the",
				"terminal window in order to be displayed"
			},
			[](std::string_view title, int &, RainProperties &rainProperties)
			{
				SetTitle(title, rainProperties);
			}
		}
	};
}

#endif
