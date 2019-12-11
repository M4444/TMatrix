/*
 * Copyright (C) 2018-2019 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#ifndef COLOR_H
#define COLOR_H

#include <cstring>
#include <stdexcept>
#include <string_view>

struct Color {
	const char* Foreground;
	const char* Background;

	static constexpr std::size_t LONGEST_COLOR_SIZE {sizeof("\033[39m")};

	static constexpr Color GetColor(std::string_view color) {
		if (color == "default") {
			return Color {"\033[39m", "\033[49m" };
		} else if (color == "white") {
			return Color {"\033[97m", "\033[107m"};
		} else if (color == "gray") {
			return Color {"\033[90m", "\033[100m"};
		} else if (color == "black") {
			return Color {"\033[30m", "\033[40m" };
		} else if (color == "red") {
			return Color {"\033[31m", "\033[41m" };
		} else if (color == "green") {
			return Color {"\033[92m", "\033[42m" };
		} else if (color == "yellow") {
			return Color {"\033[33m", "\033[43m" };
		} else if (color == "blue") {
			return Color {"\033[34m", "\033[44m" };
		} else if (color == "magenta") {
			return Color {"\033[35m", "\033[45m" };
		} else if (color == "cyan") {
			return Color {"\033[36m", "\033[46m" };
		} else {
			throw std::invalid_argument("Color isn't valid.");
		}
	}
};

#endif
