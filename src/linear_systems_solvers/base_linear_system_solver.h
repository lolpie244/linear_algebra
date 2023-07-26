#pragma once

#include "structures/matrix/matrix.h"
#include "structures/vector/vector.h"
#include <string>
#include <map>

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

	virtual void clear();

	virtual void solve() = 0;
	virtual void inverse()
	{
		throw std::logic_error("Not implemented");
	}

	virtual std::map<std::string, std::string> get_information()
	{
		return std::map<std::string, std::string>();
	}
	virtual ~BaseLinearSystemSolver(){}
};
} // namespace linear_systems
