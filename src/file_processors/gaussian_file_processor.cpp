#include "file_processors.h"
#include <sstream>
#include <utility>
#include <memory>
#include <stdexcept>

namespace file_processor
{
using matrix::Matrix;
using linear_systems::GaussianSolver;
using linear_systems::BaseLinearSystemSolver;
using std::pair;
using std::shared_ptr;

shared_ptr<BaseLinearSystemSolver> GaussianFileProcessor::from_string_stream(stringstream &text)
{
	pair<size_t, size_t> size;
	text >> size.first >> size.second;

	if(size.second - 1 != size.first)
		throw std::invalid_argument("Incorrect matrix size");

	Matrix matrix(size);
	text >> matrix;
	auto vector = matrix.erase_column(matrix.size().second - 1);

	return shared_ptr<linear_systems::BaseLinearSystemSolver>(new GaussianSolver(matrix, vector));
}

stringstream GaussianFileProcessor::to_string_stream(const shared_ptr<BaseLinearSystemSolver>& base_gaussian)
{
	stringstream result;
	Matrix extended_matrix;
	GaussianSolver* gaussian = dynamic_cast<GaussianSolver*>(base_gaussian.get());

	extended_matrix = gaussian->coeficient_matrix;
	extended_matrix.insert_column(extended_matrix.size().second, gaussian->constants_vector);
	result << "Input extended matrix:\n";
	result << extended_matrix.size().first << ' ' << extended_matrix.size().second << '\n' << extended_matrix;

	auto [lower_history, upper_history] = gaussian->get_history();

	if(upper_history.empty())
		return result;

	result << "\n====================\n";
	result << "Intermediate matrices: (direct move)\n";
	int i = 0;
	for(i = 0; i < lower_history.size(); i++)
		result << "Lower:\n" << lower_history[i] << "\nUpper:\n" << upper_history[i] << "-------------\n";

	result << "\n====================\n";
	result << "Intermediate matrices: (reverse move)\n";
	for(; i < upper_history.size(); i++)
		result << upper_history[i] << "-------------\n";

	result << "\n======================\n";
	result << "Solution vector:\n" << gaussian->get_solution_vector();

	return result;
}
} // namespace file_processor
