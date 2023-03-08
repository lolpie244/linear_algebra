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
	for(int i = 0; i < size.first; i++)
		for(int j = 0; j < size.second; j++)
			text >> result[i][j];

	return result;
}
stringstream MatrixFileProcessor::to_string_stream(const Matrix& matrix)
{
	stringstream result;
	result << matrix.size().first << ' ' << matrix.size().second << '\n';
	for(int i = 0; i < matrix.size().first; i++)
	{
		for(int j = 0; j < matrix.size().second; j++)
			result << matrix[i][j] << ' ';
		result << '\n';
	}
	return result;
}
} // namespace file_processor
