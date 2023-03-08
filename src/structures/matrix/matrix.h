#pragma once

#include "structures/vector/vector.h"
#include "utils/constants.h"
#include <cstddef>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>

namespace matrix
{

using std::pair;
using std::shared_ptr;
using vector::Vector;

class Matrix
{
private:
	pair<size_t, size_t> _size = {0, 0};
	shared_ptr<Vector[]> lines;

public:
	// constructors
	Matrix();
	Matrix(size_t lines_count);
	Matrix(pair<size_t, size_t> size);

	// METHODS
	void resize(pair<size_t, size_t> new_size);
	void insert_line(size_t position, const Vector &line);
	void insert_column(size_t position, const Vector &column);

	// GETTERS
	pair<size_t, size_t> size() const;
	Vector get_column(int id) const;
	double get_norm() const;

	// OPERATORS
	Vector &operator[](int id) const;
	Matrix operator=(const Matrix &other_matrix);
	Matrix operator+(const Matrix &other_matrix) const;
	Matrix operator-(const Matrix &other_matrix) const;
	Matrix operator*(const Matrix &other_matrix) const;

	// randomizer
	static Matrix get_random(pair<size_t, size_t> size,
	                         double min_value = constants::DOUBLE_MIN,
	                         double max_value = constants::DOUBLE_MAX);
};
} // namespace matrix
