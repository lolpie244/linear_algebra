#include "src/file_processors/base_file_processor.h"
#include "src/linear_systems_solvers/base_linear_system_solver.h"
#include <map>
#include <memory>
#include <string>

namespace linear_systems_solvers_list
{
using file_processor::BaseFileProcessor;
using linear_systems::BaseLinearSystemSolver;
using std::shared_ptr;
using std::string;

using FileProcessorForLinear =
    BaseFileProcessor<shared_ptr<BaseLinearSystemSolver>>;

class LinearSystemMethodsInfo
{

public:
	class LinearSystemMethod
	{
	public:
		shared_ptr<BaseLinearSystemSolver> solver;
		shared_ptr<FileProcessorForLinear> file_processor;
		LinearSystemMethod() {}

		template <typename Solver, typename FileProcessor>
		LinearSystemMethod(Solver *solver, FileProcessor *file_processor)
		{
			this->solver = std::make_shared<Solver>();
			this->file_processor = std::make_shared<FileProcessor>();
		}
	};

	LinearSystemMethod get(string name);
	std::map<string, LinearSystemMethod> methods_list();
};


} // namespace linear_systems_solvers_list
