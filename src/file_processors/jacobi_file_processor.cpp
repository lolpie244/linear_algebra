#include "file_processors.h"
#include "linear_systems_solvers/jacobi/jacobi.h"
#include <memory>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace file_processor
{
using linear_systems::BaseLinearSystemSolver;
using linear_systems::JacobiSolver;
using matrix::Matrix;
using std::shared_ptr;

shared_ptr<BaseLinearSystemSolver>
JacobiFileProcessor::from_string_stream(stringstream &text)
{
    auto [matrix, vector] = linear_system_from_string_stream(text);
    return shared_ptr<linear_systems::BaseLinearSystemSolver>(
               new JacobiSolver(matrix, vector));
}

stringstream JacobiFileProcessor::to_string_stream(
    const shared_ptr<BaseLinearSystemSolver> &base_jacobi)
{
    stringstream result;
    Matrix extended_matrix;
    JacobiSolver *jacobi = dynamic_cast<JacobiSolver *>(base_jacobi.get());

    extended_matrix = jacobi->coeficient_matrix;
    extended_matrix.insert_column(extended_matrix.size().second,
                                  jacobi->constants_vector);
    result << "Input extended matrix:\n";
    result << extended_matrix.size().first << ' ' << extended_matrix.size().second
           << '\n'
           << extended_matrix;

    result << "\n====================\n";
    result << "Result:\n" << jacobi->get_solution_vector();

    result << "\n====================\n";
    result << "Mesurments errors:\n";

    auto eps_history = jacobi->get_eps_history();
    for (int i = 0; i < eps_history.size(); i++)
        result << "Iteration №" << i + 1 << ": " << eps_history[i] << '\n';

    return result;
}
} // namespace file_processor
