/*
 * Copyright (C) 2018-2023 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#ifndef RANGE_H
#define RANGE_H

#include <stdexcept>

template <typename T>
class Range {
	T min;
	T max;
public:
	constexpr Range() = default;
	constexpr Range(T Min, T Max) : min{Min}, max{Max} {
		if (Min > Max) {
			throw std::range_error("Min is greater than max.");
		}
	}
	constexpr Range(T range) : min{0}, max{range-1} {
		if (range == 0) {
			throw std::range_error("range can't be zero.");
		}
	}

	T GetMin() const { return min; }
	T GetMax() const { return max; }
};

template <typename T> Range(T, T) -> Range<T>;

#endif
