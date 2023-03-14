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
using vector::Vector;

std::vector<Matrix> GaussianSolver::get_history() const
{
	return history;
}
Matrix GaussianSolver::get_triangle(Matrix matrix)
{
	for (int i = 0; i < matrix.size().first; i++) {
		int max_line = i;
		double max_value = matrix[i][i];
		for (int line = i; line < matrix.size().first; line++) {
			double a = matrix[line][i];
			double b = matrix[max_line][i];
			if (std::abs(matrix[line][i]) > std::abs(matrix[max_line][i])) {
				max_line = line;
				max_value = matrix[line][i];
			}
		}

		std::swap(matrix[i], matrix[max_line]);

		for (int line = i + 1; line < matrix.size().first; line++) {
			double coeficient = -(matrix[line][i] / matrix[i][i]);
			matrix[line] += matrix[i] * coeficient;
		}
		matrix[i] = matrix[i] / matrix[i][i];
		history.push_back(matrix);
	}
	return matrix;
}
void GaussianSolver::solve()
{
	this->clear();
	Matrix matrix = this->coeficient_matrix;
	Vector result;
	result.fill(constants_vector.size(), DOUBLE_MIN);

	matrix.insert_column(matrix.size().second, constants_vector);
	matrix = std::move(this->get_triangle(matrix));

	for (int line = matrix.size().first - 1; line >= 0; line--) {
		double sum = 0;
		for (int i = line + 1; i < matrix.size().first; i++) {
			if (result[i] != DOUBLE_MIN)
				sum += matrix[line][i] * result[i];
		}
		result[line] =
		    (matrix[line][matrix.size().second - 1] - sum) / matrix[line][line];
	}
	solution_vector = std::move(result);
}
void GaussianSolver::inverse()
{
	this->clear();
	Matrix matrix = this->coeficient_matrix;
	matrix.resize({matrix.size().first, matrix.size().second * 2});
	for (int i = 0; i < matrix.size().first; i++)
		matrix[i][matrix.size().first + i] = 1;

	history.push_back(matrix);

	matrix = std::move(this->get_triangle(matrix));

	for (int i = 0; i < this->coeficient_matrix.size().first - 1; i++)
		for (int j = i + 1; j < this->coeficient_matrix.size().second; j++) {
			if (matrix[i][j] == 0)
				continue;

			double coeficient = -(matrix[i][j] / matrix[j][j]);
			matrix[i] += matrix[j] * coeficient;
			history.push_back(matrix);
		}

	coeficient_matrix =
	    matrix.slice({0, this->coeficient_matrix.size().second}, matrix.size());
}
void GaussianSolver::clear()
{
	history.clear();
	BaseLinearSystemSolver::clear();
}
} // namespace linear_systems
