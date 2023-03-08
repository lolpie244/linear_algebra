#pragma once

#include "structures/matrix/matrix.h"
#include "structures/vector/vector.h"

namespace linear_systems
{
class BaseLinearSystemSolver
{
protected:
	vector::Vector solution_vector;

public:
	matrix::Matrix coeficient_matrix;
	vector::Vector constant_vector;

	BaseLinearSystemSolver(const matrix::Matrix& coeficient_matrix, const vector::Vector& constant_vector)
	{
		this->coeficient_matrix = coeficient_matrix;
		this->constant_vector = constant_vector;
	}

	vector::Vector get_solution_vector()
	{
		return solution_vector;
	}

	virtual void solve() = 0;
};
} // namespace linear_systems
