#include "file_processors.h"
#include <sstream>
#include <utility>

namespace file_processor
{
using matrix::Matrix;
using std::pair;

Matrix MatrixFileProcessor::from_string_stream(stringstream &text)
{
	pair<size_t, size_t> size;
	text >> size.first >> size.second;

	Matrix result(size);
	text >> result;
	return result;
}
stringstream MatrixFileProcessor::to_string_stream(const Matrix& matrix)
{
	stringstream result;
	result << matrix.size().first << ' ' << matrix.size().second << '\n';
	result << matrix;
	return result;
}
} // namespace file_processor
