#pragma once
#include "../base_linear_system_solver.h"
#include <vector>

namespace linear_systems
{

class JacobiSolver : public BaseLinearSystemSolver
{
	using BaseLinearSystemSolver::BaseLinearSystemSolver;

private:
	std::vector<double> eps_history;
	int iterations_count;
	void check_coeficient_matrix();

public:
	std::vector<double> get_eps_history() const;
	void solve();
	void clear();
	std::map<std::string, std::string> get_information();
};
} // namespace linear_systems
