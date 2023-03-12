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

std::vector<Matrix> GaussianSolver::get_history() const
{
	return history;
}
Matrix GaussianSolver::get_triangle(Matrix matrix)
{
	for (int i = 0; i < matrix.size().first; i++) {
		int max_line = 0;
		for (int line = 0; line < matrix.size().first; line++)
			if (std::abs(matrix[line][i]) > std::abs(matrix[max_line][i])) {
				max_line = line;
			}

		std::swap(matrix[i], matrix[max_line]);
		for (int line = i + 1; line < matrix.size().first; line++) {
			double coeficient = -(matrix[line][i] / matrix[i][i]);
			matrix[line] += matrix[i] * coeficient;
		}
		history.push_back(matrix);
	}
	return matrix;
}
void GaussianSolver::solve()
{
	history.clear();
	Matrix matrix = this->coeficient_matrix;
	Vector result;
	result.fill(constants_vector.size(), DOUBLE_MIN);

	matrix.insert_column(matrix.size().second, constants_vector);
	auto triangle_matrix = get_triangle(matrix);

	// auto original_positions = sort_matrix(triangle_matrix);
	std::cout << triangle_matrix << '\n';
	return;

	// for (int line = 0; line < triangle_matrix.size().first; line++) {
	// 	double sum = 0;
	// 	for (int i = 0; i < line; i++) {
	// 		if (result[i] != DOUBLE_MIN)
	// 			sum += triangle_matrix[line][i] * result[i];
	// 	}
	// 	result[line] =
	// 	    (triangle_matrix[line][triangle_matrix.size().second - 1] - sum) /
	// 	    triangle_matrix[line][line];
	// }
	// solution_vector.resize(result.size());
	// for (int i = 0; i < result.size(); i++)
	// 	solution_vector[original_positions[i]] = result[i];
}
} // namespace linear_systems
