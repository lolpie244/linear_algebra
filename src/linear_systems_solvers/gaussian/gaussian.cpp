#include "gaussian.h"
#include "utils/constants.h"

namespace linear_systems
{
using matrix::Matrix;
using std::swap;
using constants::DOUBLE_MIN;
using vector::Vector;

void GaussianSolver::to_triangle_matrix(Matrix &matrix)
{
	for (int zero_pos = 0; zero_pos < matrix.size().first; zero_pos++) {

		int line_to_add = 0;
		for (line_to_add = 0; line_to_add < zero_pos + 1; line_to_add++)
			if (matrix[line_to_add][zero_pos] != 0)
				break;

		for (int line = zero_pos + 1; line < matrix.size().first; line++) {
			for (int i = line; i < matrix.size().first; i++) {
				if (matrix[i][zero_pos] != 0) {
					if (i != line)
						swap(matrix[i], matrix[line]);
					break;
				}
			}

			if (matrix[line][zero_pos] == 0)
				continue;

			double coef = -matrix[line][zero_pos] / matrix[line_to_add][zero_pos];

			for (int i = 0; i < matrix.size().second; i++)
				matrix[line][i] += matrix[line_to_add][i] * coef;
		}
	}
}

void GaussianSolver::solve()
{
	auto matrix = this->coeficient_matrix;
	Vector result;
	result.fill(constant_vector.size(), DOUBLE_MIN);

	matrix.insert_column(matrix.size().second, constant_vector);
	to_triangle_matrix(matrix);

	for (int line = matrix.size().first - 1; line >= 0; line--) {
		double sum = 0;
		for (int i = line + 1; i < matrix.size().second - 1; i++) {
			if (result[i] != DOUBLE_MIN)
				sum += matrix[line][i] * result[i];
		}
		result[line] =
		    (matrix[line][matrix.size().second - 1] - sum) / matrix[line][line];
	}
	solution_vector = result;
}
} // namespace linear_systems
