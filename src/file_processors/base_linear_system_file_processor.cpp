#include "file_processors.h"
#include <sstream>
#include <utility>
#include <memory>
#include <stdexcept>

namespace file_processor
{
using std::pair;

pair<matrix::Matrix, vector::Vector> BaseLinearSystemFileProcessor::linear_system_from_string_stream(stringstream &text)
{
	pair<size_t, size_t> size;
	text >> size.first >> size.second;

	if(size.second - 1 != size.first)
		throw std::invalid_argument("Incorrect matrix size");

	matrix::Matrix matrix(size);
	text >> matrix;
	auto vector = matrix.erase_column(matrix.size().second - 1);

	return {matrix, vector};
}

} // namespace file_processor
