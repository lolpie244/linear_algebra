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
	std::vector<Matrix> history;
	std::pair<Matrix, std::shared_ptr<int[]>> get_triangle(Matrix matrix);

public:
	void solve();
	std::vector<Matrix> get_history() const;
	std::vector<Matrix> get_inversed_coeficient_matrix() const;
};
} // namespace linear_systems
