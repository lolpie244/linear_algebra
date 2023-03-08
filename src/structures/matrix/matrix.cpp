#pragma once

#include "matrix.h"
#include "structures/vector/vector.h"
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <utility>
#include <algorithm>
#include <cmath>

#include "matrix.h"
#include "utils/math.h"
#include <random>
namespace matrix
{

using std::pair;
using std::shared_ptr;
using vector::Vector;

Matrix::Matrix() {}

Matrix::Matrix(size_t lines_count)
{
	this->resize({lines_count, 0});
}
Matrix::Matrix(pair<size_t, size_t> size)
{
	this->resize(size);
}
// METHODS
void Matrix::resize(pair<size_t, size_t> new_size)
{
	if (new_size == _size)
		return;

	auto old_lines = lines;
	auto old_size = _size;

	_size = new_size;
	lines = shared_ptr<Vector[]>(new Vector[_size.first]);

	if (new_size.second == 0)
		return;


	for (int i = 0; i < _size.first; i++) {
		if (i < old_size.first)
			lines[i] = std::move(old_lines[i]);
		lines[i].resize(_size.second);
	}
}
void Matrix::insert_line(size_t position, const Vector &line)
{
	if (this->size().first < position)
		throw std::out_of_range("");

	if (this->size().second != line.size())
		throw std::invalid_argument(
		    "New line size does not match existing lines size.");

	auto old_lines = lines;
	lines = shared_ptr<Vector[]>(new Vector[this->size().first + 1]);

	int step = 0;

	for (int i = 0; i < this->size().first; i++) {
		if (i == position)
			step++;
		else
			lines[i + step] = std::move(old_lines[i]);
	}
	lines[position] = Vector(this->size().second);
	_size.first++;
}
void Matrix::insert_column(size_t position, const Vector &column)
{
	if (this->size().second < position)
		throw std::out_of_range("");
	if (this->size().first != column.size())
		throw std::invalid_argument(
		    "New column size does not match existing columns size.");

	for (int i = 0; i < this->size().first; i++)
		lines[i].insert(position, column[i]);

	_size.second++;
}

// GETTERS
pair<size_t, size_t> Matrix::size() const
{
	return _size;
}
Vector Matrix::get_column(int id) const
{
	if (_size.second <= id)
		throw std::out_of_range("");

	Vector result(_size.first);
	for (int i = 0; i < this->size().first; i++)
		result[i] = lines[i][id];

	return result;
}
double Matrix::get_norm() const
{
	double result = 0;
	for(int i = 0; i < this->size().first; i++)
		for(int j = 0; j < this->size().second; j++)
			result = std::max(result, std::abs(lines[i][j]));
	return result;
}

// OPERATORS
Vector &Matrix::operator[](int id) const
{
	if (_size.first <= id)
		throw std::out_of_range("");
	return lines[id];
}

Matrix Matrix::operator=(const Matrix &other_matrix)
{
	lines = shared_ptr<Vector[]>(new Vector[other_matrix.size().first]);
	_size = other_matrix.size();

	for (int i = 0; i < this->size().first; i++)
		lines[i] = other_matrix[i];

	return *this;
}
Matrix Matrix::operator+(const Matrix &other_matrix) const
{
	if (this->size() != other_matrix.size())
		throw std::invalid_argument("Matrices must have the same sizes");

	Matrix result(this->size().first);

	for (int i = 0; i < this->size().first; i++)
		result[i] = lines[i] + other_matrix[i];

	return result;
}

Matrix Matrix::operator-(const Matrix &other_matrix) const
{
	if (this->size() != other_matrix.size())
		throw std::invalid_argument("Matrices must have the same sizes");

	Matrix result(this->size().first);

	for (int i = 0; i < this->size().first; i++)
		result[i] = lines[i] - other_matrix[i];

	return result;
}
Matrix Matrix::operator*(const Matrix &other_matrix) const
{
	if (this->size().second != other_matrix.size().first)
		throw std::invalid_argument(
		    "Number of columns in first matrix must match number of rows in "
		    "the second matrix");

	pair<size_t, size_t> size = {this->size().first, other_matrix.size().second};

	Matrix result(size);

	for (int i = 0; i < size.first; i++)
		for (int j = 0; j < size.second; j++)
			result[i][j] = lines[i] * other_matrix.get_column(j);

	return result;
}

Matrix Matrix::get_random(pair<size_t, size_t> size, double min_value,
                          double max_value)
{
	std::uniform_real_distribution<double> random(min_value, max_value);

	std::default_random_engine engine;

	Matrix result(size);
	for (int i = 0; i < size.first; i++)
		for (int j = 0; j < size.second; j++)
			result[i][j] = utils::round(random(engine), 3);

	return result;
}
} // namespace matrix
