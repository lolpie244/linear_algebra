#pragma once
#include <limits>

namespace constants {

	constexpr double DOUBLE_MIN = std::numeric_limits<double>::min();
	constexpr double DOUBLE_MAX = std::numeric_limits<double>::max();
	constexpr double EPS = 0.001;
}
