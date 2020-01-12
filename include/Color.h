/*
 * Copyright (C) 2018-2020 Miloš Stojanović
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
	const char* Shade1;
	const char* Shade2;
	const char* Shade3;
	const char* Shade4;

	static constexpr std::size_t GetPrefixSize(bool isFade)
	{
		return isFade ? sizeof("\033[38;5;234m") : sizeof("\033[100m");
	};

	static constexpr Color GetColor(std::string_view color) {
		if (color == "default") {
			return Color {"\033[39m", "\033[49m",
				      "\033[38;5;10m", "\033[38;5;28m",
				      "\033[38;5;22m", "\033[38;5;234m" };
		} else if (color == "white") {
			return Color {"\033[97m", "\033[107m",
				      "\033[38;5;15m", "\033[38;5;246m",
				      "\033[38;5;240m", "\033[38;5;234m" };
		} else if (color == "gray") {
			return Color {"\033[90m", "\033[100m",
				      "\033[38;5;10m", "\033[38;5;28m",
				      "\033[38;5;22m", "\033[38;5;234m" };
		} else if (color == "black") {
			return Color {"\033[30m", "\033[40m",
				      "\033[38;5;10m", "\033[38;5;28m",
				      "\033[38;5;22m", "\033[38;5;234m" };
		} else if (color == "red") {
			return Color {"\033[31m", "\033[41m",
				      "\033[38;5;10m", "\033[38;5;28m",
				      "\033[38;5;22m", "\033[38;5;234m" };
		} else if (color == "green") {
			return Color {"\033[92m", "\033[42m",
				      "\033[38;5;10m", "\033[38;5;28m",
				      "\033[38;5;22m", "\033[38;5;234m" };
		} else if (color == "yellow") {
			return Color {"\033[33m", "\033[43m",
				      "\033[38;5;10m", "\033[38;5;28m",
				      "\033[38;5;22m", "\033[38;5;234m" };
		} else if (color == "blue") {
			return Color {"\033[34m", "\033[44m",
				      "\033[38;5;10m", "\033[38;5;28m",
				      "\033[38;5;22m", "\033[38;5;234m" };
		} else if (color == "magenta") {
			return Color {"\033[35m", "\033[45m",
				      "\033[38;5;10m", "\033[38;5;28m",
				      "\033[38;5;22m", "\033[38;5;234m" };
		} else if (color == "cyan") {
			return Color {"\033[36m", "\033[46m",
				      "\033[38;5;10m", "\033[38;5;28m",
				      "\033[38;5;22m", "\033[38;5;234m" };
		} else {
			throw std::invalid_argument("Color isn't valid.");
		}
	}
};

#endif
