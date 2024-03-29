#pragma once
#include "base_file_processor.h"
#include "structures/matrix/matrix.h"
#include "linear_systems_solvers/gaussian/gaussian.h"
#include <memory>


namespace file_processor
{
using std::shared_ptr;

class MatrixFileProcessor : public BaseFileProcessor<matrix::Matrix>
{
protected:
	matrix::Matrix from_string_stream(stringstream &text);
	stringstream to_string_stream(const matrix::Matrix &obj);
};

class BaseLinearSystemFileProcessor : public BaseFileProcessor<shared_ptr<linear_systems::BaseLinearSystemSolver>>
{
protected:
	std::pair<matrix::Matrix, vector::Vector> linear_system_from_string_stream(stringstream &text);
};

class GaussianFileProcessor : public BaseLinearSystemFileProcessor
{
protected:
	shared_ptr<linear_systems::BaseLinearSystemSolver> from_string_stream(stringstream &text);
	stringstream to_string_stream(const shared_ptr<linear_systems::BaseLinearSystemSolver>& obj);
};

class JacobiFileProcessor : public BaseLinearSystemFileProcessor
{
protected:
	shared_ptr<linear_systems::BaseLinearSystemSolver> from_string_stream(stringstream &text);
	stringstream to_string_stream(const shared_ptr<linear_systems::BaseLinearSystemSolver>& obj);
};

} // namespace file_processor
