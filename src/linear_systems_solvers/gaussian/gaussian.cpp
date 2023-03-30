#include "gaussian.h"
#include "structures/vector/vector.h"
#include "utils/constants.h"
#include "utils/math.h"
#include <cmath>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

namespace linear_systems
{
using constants::DOUBLE_MIN;
using matrix::Matrix;
using vector::Vector;

std::pair<std::vector<Matrix>, std::vector<Matrix>> GaussianSolver::get_history() const
{
	return {lower_history, upper_history};
}
void check_matrix_line(const Matrix &matrix, int line)
{
	if (matrix[line][line] == 0) {
		if (matrix[line][matrix.size().first] != 0) {
			for (int i = 0; i < matrix.size().first; i++)
				if (utils::round(matrix[line][i], 15) != 0)
					goto singular;

			throw std::invalid_argument(
			    "Error: The matrix is inconsistent (no solution)");
		}
singular:
		throw std::invalid_argument(
		    "Error: The matrix is singular (more than one solution)");
	}
}
std::pair<Matrix, Matrix> GaussianSolver::direct_move(Matrix matrix)
{
	Matrix upper = std::move(matrix);
	Matrix lower = Matrix::get_identity(matrix.size().first);
	std::vector<std::pair<int, int>> swap_history;

	for (int i = 0; i < upper.size().first; i++) {
		int max_line = i;
		for (int line = i; line < upper.size().first; line++)
			if (std::abs(upper[line][i]) > std::abs(upper[max_line][i])) {
				max_line = line;
			}

		std::swap(upper[i], upper[max_line]);
		std::swap(lower[i], lower[max_line]);

		check_matrix_line(upper, i);

		for (int line = i + 1; line < upper.size().first; line++) {
			auto coef = -(upper[line][i] / upper[i][i]);
			upper[line] += upper[i] * coef;
			lower[line] += lower[line] * coef;
		}
		upper_history.push_back(upper);
		lower_history.push_back(lower);
	}
	return {lower, upper};
}
Matrix GaussianSolver::reverse_move(Matrix matrix)
{
	matrix[0] = matrix[0] / matrix[0][0];
	for (int column = matrix.size().first - 1; column > 0; column--) {
		matrix[column] = matrix[column] / matrix[column][column];
		check_matrix_line(matrix, column);
		for (int line = column - 1; line >= 0; line--) {

			if (matrix[line][column] != 0) {
				double coeficient = -matrix[line][column];
				matrix[line] += matrix[column] * coeficient;

				upper_history.push_back(matrix);
			}
		}
	}
	return matrix;
}
Matrix GaussianSolver::get_identity_matrix(Matrix matrix)
{
	return this->reverse_move(this->direct_move(matrix).second);
}
void GaussianSolver::solve()
{
	this->clear();

	Matrix matrix = this->coeficient_matrix;
	Vector result;
	result.fill(constants_vector.size(), DOUBLE_MIN);

	matrix.insert_column(matrix.size().second, constants_vector);
	matrix = this->get_identity_matrix(matrix);

	for (int line = 0; line < result.size(); line++) {
		result[line] =
		    (matrix[line][matrix.size().second - 1]) / matrix[line][line];
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

	upper_history.push_back(matrix);

	matrix = this->get_identity_matrix(matrix);

	coeficient_matrix =
	    matrix.slice({0, this->coeficient_matrix.size().second}, matrix.size());
}
double GaussianSolver::get_measurement_error()
{
	if (this->solution_vector.size() == 0)
		throw std::invalid_argument("Solution vector is empty");

	double result = 0;

	for (int i = 0; i < this->solution_vector.size(); i++) {
		double error = -this->constants_vector[i];
		for (int j = 0; j < this->coeficient_matrix.size().second; j++)
			error += this->coeficient_matrix[i][j] * this->solution_vector[j];

		result += utils::round(error * error, 10);
	}
	return std::sqrt(result);
}
void GaussianSolver::clear()
{
	upper_history.clear();
	lower_history.clear();
	BaseLinearSystemSolver::clear();
}
} // namespace linear_systems
