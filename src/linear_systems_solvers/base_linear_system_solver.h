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
	vector::Vector constants_vector;

	BaseLinearSystemSolver(){}

	BaseLinearSystemSolver(const matrix::Matrix& coeficient_matrix, const vector::Vector& constant_vector);

	vector::Vector get_solution_vector() const;

	void clear();

	virtual void solve() = 0;
	virtual void inverse() = 0;

	virtual ~BaseLinearSystemSolver(){}
};
} // namespace linear_systems
