#include "gaussian.h"
#include "structures/vector/vector.h"
#include "utils/math.h"
#include "utils/constants.h"
#include <cmath>
#include <memory>
#include <stdexcept>
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
Matrix GaussianSolver::get_identity_matrix(Matrix matrix)
{
	for (int i = 0; i < matrix.size().first; i++) {
		int max_line = i;
		double max_value = matrix[i][i];
		for (int line = i; line < matrix.size().first; line++)
			if (std::abs(matrix[line][i]) > std::abs(matrix[max_line][i])) {
				max_line = line;
				max_value = matrix[line][i];
			}

		std::swap(matrix[i], matrix[max_line]);
		if (matrix[i][i] == 0)
			throw std::invalid_argument("Gaussian method unused");

		for (int line = i + 1; line < matrix.size().first; line++) {
			double coeficient = -(matrix[line][i] / matrix[i][i]);
			matrix[line] += matrix[i] * coeficient;
		}
		matrix[i] = matrix[i] / matrix[i][i];
		history.push_back(matrix);
	}

	for (int i = 0; i < matrix.size().first - 1; i++)
		for (int j = i + 1; j < matrix.size().first; j++) {
			if (matrix[i][j] == 0)
				continue;

			double coeficient = -(matrix[i][j] / matrix[j][j]);
			matrix[i] += matrix[j] * coeficient;
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

	history.push_back(matrix);

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
	history.clear();
	BaseLinearSystemSolver::clear();
}
} // namespace linear_systems
