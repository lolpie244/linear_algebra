#pragma once

#include "vector.h"
#include <stdexcept>

namespace vector
{

using std::shared_ptr;

Vector::Vector(size_t size)
{
	this->resize(size);
}

// METHODS
void Vector::resize(size_t new_size)
{
	if (new_size == _size)
		return;

	auto old_values = values;
	auto old_size = _size;

	_size = new_size;
	values = shared_ptr<double[]>(new double[_size]);

	for (int i = 0; i < _size; i++) {
		if (i < old_size)
			values[i] = old_values[i];
		else
			values[i] = 0;
	}
}

void Vector::fill(size_t count, double value)
{
	_size = count;
	values = shared_ptr<double[]>(new double[_size]);

	for (int i = 0; i < this->size(); i++)
		values[i] = value;
}

void Vector::insert(size_t position, double value)
{
	if (this->size() < position)
		throw std::out_of_range("");

	auto old_values = values;
	values = shared_ptr<double[]>(new double[this->size() + 1]);

	int step = 0;

for (int i = 0; i < this->size(); i++) {
		if (i == position)
			step++;
		else
			values[i + step] = old_values[i];
	}
	values[position] = 0;
	_size++;
}

// GETTERS
size_t Vector::size() const
{
	return _size;
}

// OPERATORS
double& Vector::operator[](int id) const
{
	if (_size < id)
		throw std::out_of_range("");

	return values[id];
}

Vector Vector::operator=(Vector other_vector)
{

	values = shared_ptr<double[]>(new double[other_vector.size()]);
	_size = other_vector.size();

	for (int i = 0; i < this->size(); i++)
		values[i] = other_vector[i];

	return *this;
}

Vector Vector::operator+(Vector other_vector)
{
	if (this->size() != other_vector.size())
		throw std::invalid_argument("Vectors must be of the same length");

	Vector result(this->size());

	for (int i = 0; i < this->size(); i++)
		result[i] = values[i] + other_vector[i];

	return result;
}

Vector Vector::operator-(Vector other_vector)
{
	if (this->size() != other_vector.size())
		throw std::invalid_argument("Vectors must be of the same length");

	Vector result(this->size());

	for (int i = 0; i < this->size(); i++)
		result[i] = values[i] - other_vector[i];

	return result;
}

double Vector::operator*(Vector other_vector)
{
	if (this->size() != other_vector.size())
		throw std::invalid_argument("Vectors must be of the same length");

	double result = 0;

	for (int i = 0; i < this->size(); i++)
		result += values[i] * other_vector[i];

	return result;
}

} // namespace vector
