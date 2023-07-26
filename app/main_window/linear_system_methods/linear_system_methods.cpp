#include "linear_system_methods.h"
#include "file_processors/file_processors.h"
#include "linear_systems_solvers/gaussian/gaussian.h"
#include "linear_systems_solvers/jacobi/jacobi.h"
#include <string>
namespace linear_systems_solvers_list
{
using LinearSystemMethod = LinearSystemMethodsInfo::LinearSystemMethod;

LinearSystemMethod LinearSystemMethodsInfo::get(string name)
{
	auto list = this->methods_list();
	return list[name];
}
std::map<string, LinearSystemMethod> LinearSystemMethodsInfo::methods_list()
{
	return {
		{"Gaussian",
			LinearSystemMethod(new linear_systems::GaussianSolver,
			                   new file_processor::GaussianFileProcessor)
		},
		{"Jacobi",
			LinearSystemMethod(new linear_systems::JacobiSolver,
			                   new file_processor::JacobiFileProcessor)
		}};
}
} // namespace linear_systems_solvers_list
