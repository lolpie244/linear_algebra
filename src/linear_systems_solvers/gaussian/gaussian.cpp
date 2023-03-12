#include "gaussian.h"
#include "structures/vector/vector.h"
#include "utils/comparators.h"
#include "utils/constants.h"
#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <unordered_set>
#include <utility>

namespace linear_systems
{
using constants::DOUBLE_MIN;
using matrix::Matrix;
using std::pair;
using vector::Vector;
using std::shared_ptr;

std::vector<Matrix> GaussianSolver::get_history() const
{
	return history;
}
pair<Matrix, shared_ptr<int[]>> GaussianSolver::get_triangle(Matrix matrix)
{
	shared_ptr<int[]> original_positions(new int[matrix.size().first]);
	for(int i = 0; i < matrix.size().first; i++)
		original_positions[i] = i;

	for (int i = 0; i < matrix.size().first; i++) {
		int max_line = i;
		for (int line = i; line < matrix.size().first; line++)
			if (std::abs(matrix[line][i]) > std::abs(matrix[max_line][i])) {
				max_line = line;
			}
		std::swap(matrix[i], matrix[max_line]);
		std::swap(original_positions[i], original_positions[max_line]);

		for (int line = i + 1; line < matrix.size().first; line++) {
			double coeficient = -(matrix[line][i] / matrix[i][i]);
			matrix[line] += matrix[i] * coeficient;
		}
		matrix[i] = matrix[i] / matrix[i][i];
		history.push_back(matrix);
	}
	return {matrix, original_positions};
}
void GaussianSolver::solve()
{
	history.clear();
	Matrix matrix = this->coeficient_matrix;
	Vector result;
	result.fill(constants_vector.size(), DOUBLE_MIN);

	matrix.insert_column(matrix.size().second, constants_vector);
	auto [triangle_matrix, original_positions] = get_triangle(matrix);

	for (int line = triangle_matrix.size().first - 1; line >= 0; line--) {
		double sum = 0;
		for (int i = line + 1; i < triangle_matrix.size().first; i++) {
			if (result[i] != DOUBLE_MIN)
				sum += triangle_matrix[line][i] * result[i];
		}
		result[line] =
		    (triangle_matrix[line][triangle_matrix.size().second - 1] - sum) /
		    triangle_matrix[line][line];
	}
	solution_vector.resize(result.size());
	for (int i = 0; i < result.size(); i++)
		solution_vector[original_positions[i]] = result[i];
}
} // namespace linear_systems
