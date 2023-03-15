#pragma once
#include <cmath>
namespace utils
{
	inline double round(double value, int count)
	{
		double pow_10 = std::pow(10.0, (float)count);
		return std::round(value * pow_10) / pow_10;
	}
} // namespace utils
