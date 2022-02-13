/*
 * Copyright (C) 2018-2022 Miloš Stojanović
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#ifndef DECIMAL_FRACTION_H
#define DECIMAL_FRACTION_H

#include <stdexcept>
#include <string>

class DecimalFraction {
	// For example 1.2 is represented as 12.
	int Representation;
public:
	constexpr DecimalFraction() : Representation{0} {}
	constexpr DecimalFraction(const DecimalFraction& DF) :
		Representation{DF.Representation} {}
	constexpr DecimalFraction(int IntegerPart, int FractionalPart = 0) :
		Representation{
			IntegerPart * 10 + (IntegerPart < 0 ? - FractionalPart : FractionalPart)
		}
	{
		if (FractionalPart > 9 || FractionalPart < 0) {
			throw std::invalid_argument("Fractional part must to be in range 0-9.");
		}
	}

	constexpr int GetIntegerPart() const { return Representation / 10; }
	constexpr int GetFractionalPart() const { return Representation % 10; }

	constexpr DecimalFraction GetFloor() const { return Representation / 10; }

	constexpr bool operator>(const DecimalFraction& DF) const
	{
		return Representation > DF.Representation;
	}

	constexpr bool operator==(const DecimalFraction& DF) const
	{
		return Representation == DF.Representation;
	}

	constexpr DecimalFraction& operator+=(const DecimalFraction& DF)
	{
		Representation += DF.Representation;
		return *this;
	}

	constexpr DecimalFraction operator-(const DecimalFraction& DF) const
	{
		int result {Representation - DF.Representation};
		return {result / 10, result % 10};
	}

	constexpr DecimalFraction& operator=(const DecimalFraction& DF)
	{
		Representation = DF.Representation;
		return *this;
	}

	std::string to_string() const
	{
		return std::to_string(Representation / 10) + "." + std::to_string(Representation % 10);
	}
};

#endif
