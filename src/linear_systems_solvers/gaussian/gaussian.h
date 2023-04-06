#pragma once
#include "../base_linear_system_solver.h"
#include <unordered_set>
#include <vector>

namespace linear_systems
{
using matrix::Matrix;

class GaussianSolver : public BaseLinearSystemSolver
{
	using BaseLinearSystemSolver::BaseLinearSystemSolver;

private:
	std::vector<Matrix> upper_history;
	std::vector<Matrix> lower_history;
	Matrix get_identity_matrix(Matrix matrix);
	std::pair<Matrix, Matrix> direct_move(Matrix matrix);
	Matrix reverse_move(Matrix matrix);
	double get_measurement_error();

public:
	void solve();
	void inverse();
	void clear();
	std::pair<std::vector<Matrix>, std::vector<Matrix>> get_history() const;
	std::vector<Matrix> get_inversed_coeficient_matrix() const;
};
} // namespace linear_systems
