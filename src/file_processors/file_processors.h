#include "base_file_processor.h"
#include "structures/matrix/matrix.h"

namespace file_processor
{

class MatrixFileProcessor : public BaseFileProcessor<matrix::Matrix>
{

protected:
	matrix::Matrix from_string_stream(stringstream &text);
	stringstream to_string_stream(const matrix::Matrix &obj);
};

} // namespace file_processor
