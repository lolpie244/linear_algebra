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
void GaussianSolver::add_to_history(
    const Matrix &matrix, const std::unordered_set<int> &ignored_lines,
    const std::unordered_set<int> &ignored_columns)
{

	Matrix history_matrix({matrix.size().first - ignored_lines.size(),
	                       matrix.size().second - ignored_columns.size()});
	std::shared_ptr<int[]> line_steps(new int[matrix.size().first]);
	std::shared_ptr<int[]> column_steps(new int[matrix.size().first]);

	int k = 0;
	for (int i = 0; i < matrix.size().first; i++) {
		if (ignored_lines.count(i))
			k++;
		line_steps[i] = k;
	}

	k = 0;
	for (int i = 0; i < matrix.size().second; i++) {
		if (ignored_columns.count(i))
			k++;
		column_steps[i] = k;
	}

	for (int i = 0; i < matrix.size().first; i++) {
		if (ignored_lines.count(i))
			continue;
		for (int j = 0; j < matrix.size().second; j++) {
			if (ignored_columns.count(j))
				continue;

			history_matrix[i - line_steps[i]][j - column_steps[j]] = matrix[i][j];
		}
	}
	history.push_back(history_matrix);
}
Matrix GaussianSolver::get_triangle(Matrix matrix)
{
	std::unordered_set<int> ignored_columns;
	std::unordered_set<int> ignored_lines;

	while (ignored_lines.size() + 1 < matrix.size().first) {
		pair<size_t, size_t> main_element = {0, 0};
		for (int i = 0; i < matrix.size().first; i++) {
			if (ignored_lines.count(i))
				continue;

			for (int j = 0; j < matrix.size().second - 1; j++) {
				if (!ignored_columns.count(j) &&
				        std::abs(matrix[i][j]) >
				        std::abs(matrix[main_element.first][main_element.second]))
					main_element = pair(i, j);
			}
		}
		for (int i = 0; i < matrix.size().first; i++) {
			if (i == main_element.first || ignored_lines.count(i))
				continue;
			double coeficient = -(matrix[i][main_element.second] /
			                      matrix[main_element.first][main_element.second]);

			for (int j = 0; j < matrix.size().second; j++)
				if (!ignored_columns.count(j))
					matrix[i][j] += matrix[main_element.first][j] * coeficient;
		}
		add_to_history(matrix, ignored_lines, ignored_columns);
		ignored_lines.insert(main_element.first);
		ignored_columns.insert(main_element.second);
	}

	add_to_history(matrix, ignored_lines, ignored_columns);
	return matrix;
}
std::vector<int> GaussianSolver::sort_matrix(Matrix &matrix)
{
	std::vector<pair<int, int>> zeros_count(matrix.size().first);

	for (int i = 0; i < matrix.size().first; i++) {
		int count = 0;
		for (int j = matrix.size().second - 2; j >= 0 && matrix[i][j] == 0; j--)
			count++;
		zeros_count[i] = {count, i};
	}
	std::sort(zeros_count.begin(), zeros_count.end(),
	          std::greater<pair<int, int>>());

	Matrix result(matrix.size());

	std::vector<int> original_positions(zeros_count.size());
	for (int i = 0; i < zeros_count.size(); i++) {
		result[i] = std::move(matrix[zeros_count[i].second]);
		original_positions[i] = zeros_count[i].second;
	}
	matrix = std::move(result);
	return original_positions;
}
void GaussianSolver::solve()
{
	history.clear();
	Matrix matrix = this->coeficient_matrix;
	Vector result;
	result.fill(constants_vector.size(), DOUBLE_MIN);

	matrix.insert_column(matrix.size().second, constants_vector);
	auto triangle_matrix = get_triangle(matrix);

	std::cout << triangle_matrix << "\n\n";
	auto original_positions = sort_matrix(triangle_matrix);

	for (int line = 0; line < triangle_matrix.size().first; line++) {
		double sum = 0;
		for (int i = 0; i < line; i++) {
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
