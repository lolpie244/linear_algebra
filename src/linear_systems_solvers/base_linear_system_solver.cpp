#include "base_linear_system_solver.h"

namespace linear_systems
{

BaseLinearSystemSolver::BaseLinearSystemSolver(
    const matrix::Matrix &coeficient_matrix,
    const vector::Vector &constant_vector)
{
	this->coeficient_matrix = coeficient_matrix;
	this->constants_vector = constant_vector;
}

vector::Vector BaseLinearSystemSolver::get_solution_vector() const {
	return solution_vector;
}

void BaseLinearSystemSolver::clear()
{
	solution_vector = std::move(vector::Vector());
}
} // namespace linear_systems
