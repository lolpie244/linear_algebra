#include "jacobi.h"
#include <array>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <stdexcept>
#include "utils/constants.h"

namespace linear_systems
{
	using vector::Vector;

	void JacobiSolver::check_coeficient_matrix()
	{
		for (int i = 0; i < coeficient_matrix.size().first; i++) {
			double sum = 0;
			for (int j = 0; j < coeficient_matrix.size().second; j++) {
				if (i != j)
					sum += std::abs(coeficient_matrix[i][j]);
			}
			if (std::abs(coeficient_matrix[i][i]) <= sum)
				throw std::invalid_argument("Jacobi method diverges");
		}
	}

	void JacobiSolver::solve()
	{
		check_coeficient_matrix();
		Vector result(constants_vector.size());
		Vector new_result(constants_vector.size());

		while (true) {
			double eps = 0;

			for (int i = 0; i < result.size(); i++) {
				double sum = 0;
				for (int j = 0; j < coeficient_matrix.size().second; j++) {
					if (i != j)
						sum += coeficient_matrix[i][j] * result[j];
				}

				new_result[i] = (constants_vector[i] - sum) / coeficient_matrix[i][i];
				eps = std::max(eps, std::abs(new_result[i] - result[i]));
			}
			std::swap(new_result, result);
			iterations_count++;
			eps_history.push_back(eps);
			if(eps < constants::EPS)
				break;
		}
		solution_vector = std::move(result);
	}
	void JacobiSolver::clear()
	{
		eps_history.clear();
		iterations_count = 0;
		BaseLinearSystemSolver::clear();
	}
	std::map<std::string, std::string> JacobiSolver::get_information()
	{
		auto result = BaseLinearSystemSolver::get_information();
		if(iterations_count)
			result["Iterations count"] = std::to_string(iterations_count);

		std::cout << iterations_count << '\n';

		return result;
	}

	std::vector<double> JacobiSolver::get_eps_history() const
	{
		return eps_history;
	}
}
