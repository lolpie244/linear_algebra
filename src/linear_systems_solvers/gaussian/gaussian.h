#pragma once
#include "../base_linear_system_solver.h"

namespace linear_systems
{
using matrix::Matrix;

class GaussianSolver: public BaseLinearSystemSolver
{
private:
	void to_triangle_matrix(Matrix &matrix);
public:
	void solve();
};
} // namespace linear_systems
