#pragma once
#include <cmath>

namespace utils {
	inline bool max_abs_comparator(double a, double b)
	{
		return std::abs(a) > std::abs(b);
	}

	inline bool max_comparator(double a, double b)
	{
		return a > b;
	}

	inline bool min_comparator(double a, double b)
	{
		return a < b;
	}
}
