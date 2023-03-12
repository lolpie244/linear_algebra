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
	Matrix get_triangle(Matrix matrix);

public:
	void solve();
	std::vector<Matrix> get_history() const;
};
} // namespace linear_systems
