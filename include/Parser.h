/*
 * Copyright (C) 2018-2023 Miloš Stojanović
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
	constexpr size_t SHORT_GAP_PREFIX {2};
	constexpr size_t LONG_GAP_PREFIX {6};
	constexpr std::string_view SEPARATOR {"    "};

	struct OutputVariables {
		int& stepsPerSecond;
		RainProperties& rainProperties;
		std::wstring& title;
	};

	enum OptionType { VERSION, HELP, BOOL, MODE, NUMERIC, RANGE, COLOR, TEXT };
	struct Option {
		const OptionType Type;
		const std::string ShortLiteral;
		const std::string LongLiteral;
		const std::vector<std::string> HelpText;
		const std::function<void(std::string_view, const OutputVariables& out)> ProcessArgument;

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
			      const OutputVariables& out);
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
	//---FADE---------------------------------------------------------------
	void SetFade(bool fade, RainProperties &rainProperties);
	//---COLOR--------------------------------------------------------------
	void SetColor(std::string_view color, RainProperties &rainProperties);
	//---BACKGROUND-COLOR---------------------------------------------------
	void SetBackgroundColor(std::string_view color, RainProperties &rainProperties);
	//---TITLE--------------------------------------------------------------
	void SetTitle(std::string_view title, RainProperties& rainProperties, std::wstring& wtitle);

	const std::array Options {
		Option{
			VERSION, "", "--version",
			{ "Output version information and exit "},
			[](std::string_view, const OutputVariables&) { PrintVersion(); }
		},
		Option{
			HELP, "", "--help",
			{ "Display this help and exit "},
			[](std::string_view, const OutputVariables&) { PrintUsage(true); }
		},
		Option{
			MODE, "", "--mode",
			{
				"Set the mode of the rain",
				"Available modes: default, dense"
			},
			[](std::string_view mode, const OutputVariables& out)
			{
				SetRainProperties(mode, out.rainProperties);
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
			[](std::string_view value, const OutputVariables& out)
			{
				SetStepsPerSecond(value, out.stepsPerSecond);
			}
		},
		Option{
			RANGE, "-f", "--fall-speed",
			{
				"Set the range for the fall speed",
				"The speeds can have decimal parts (e.g. 1.2)",
				"with increment of 0.1",
				"The maximal fall speed value is " + Rain::MAX_FALL_SPEED.to_string(),
				"Default: " +
					Rain::DEFAULT_PROPERTIES.RainColumnSpeed.GetMin().to_string() + ',' +
					Rain::DEFAULT_PROPERTIES.RainColumnSpeed.GetMax().to_string()

			},
			[](std::string_view range, const OutputVariables& out)
			{
				SetSpeedRange(range, out.rainProperties);
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
			[](std::string_view range, const OutputVariables& out)
			{
				SetStartingGapRange(range, out.rainProperties);
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
			[](std::string_view range, const OutputVariables& out)
			{
				SetGapRange(range, out.rainProperties);
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
			[](std::string_view range, const OutputVariables& out)
			{
				SetLengthRange(range, out.rainProperties);
			}
		},
		Option{
			RANGE, "-r", "",
			{
				"Set the range for the character update rate",
				"The values correspond to the number of steps",
				"before the change and 0 represents no change",
				"Default: " +
					std::to_string(Rain::DEFAULT_PROPERTIES.MCharUpdateRate.GetMin()) + ',' +
					std::to_string(Rain::DEFAULT_PROPERTIES.MCharUpdateRate.GetMax())
			},
			[](std::string_view range, const OutputVariables& out)
			{
				SetCharUpdateRateRange(range, out.rainProperties);
			}
		},
		Option{
			BOOL, "", "--fade",
			{
				"Enable fading characters (Default)"
			},
			[](std::string_view, const OutputVariables& out)
			{
				SetFade(true, out.rainProperties);
			}
		},
		Option{
			BOOL, "", "--no-fade",
			{
				"Disable fading characters"
			},
			[](std::string_view, const OutputVariables& out)
			{
				SetFade(false, out.rainProperties);
			}
		},
		Option{
			COLOR, "-C", "--color",
			{
				"Set the color of the characters",
				"Available colors: default, white, gray, black,",
				"red, green, yellow, blue, magenta, cyan",
				"Default: green"
			},
			[](std::string_view color, const OutputVariables& out)
			{
				SetColor(color, out.rainProperties);
			}
		},
		Option{
			COLOR, "-c", "--background",
			{
				"Set the color of the background",
				"Available colors: default, white, gray, black,",
				"red, green, yellow, blue, magenta, cyan"
			},
			[](std::string_view color, const OutputVariables& out)
			{
				SetBackgroundColor(color, out.rainProperties);
			}
		},
		Option{
			TEXT, "-t", "--title",
			{
				"Set the title that appears in the rain",
				"Note: the title needs to fit within the",
				"terminal window in order to be displayed"
			},
			[](std::string_view title, const OutputVariables& out)
			{
				SetTitle(title, out.rainProperties, out.title);
			}
		}
	};
}

#endif
