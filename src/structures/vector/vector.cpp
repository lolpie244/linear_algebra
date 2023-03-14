#include "vector.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <unordered_set>

namespace vector
{

using std::shared_ptr;

void Vector::copy_from(const Vector &other_vector)
{
	values = shared_ptr<double[]>(new double[other_vector.size()]);
	_size = other_vector.size();

	for (int i = 0; i < this->size(); i++)
		values[i] = other_vector[i];
}

Vector::Vector(const Vector &other_vector)
{
	this->copy_from(other_vector);
}

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

	for (int i = 0; i < this->size() + 1; i++) {
		if (i == position)
			step++;
		else
			values[i] = old_values[i - step];
	}
	values[position] = value;
	_size++;
}

double Vector::erase(size_t position)
{
	if (this->size() <= position)
		throw std::out_of_range("");

	auto old_values = values;
	double result = values[position];

	values = shared_ptr<double[]>(new double[this->size() - 1]);

	int step = 0;

	for (int i = 0; i < this->size(); i++) {
		if (i == position)
			step++;
		else
			values[i - step] = old_values[i];
	}
	_size--;
	return result;
}

Vector Vector::slice(size_t begin, size_t end) const
{
	if (end < begin)
		throw std::invalid_argument("Invalid range");

	if (this->size() < end)
		throw std::out_of_range("");

	Vector result(end - begin);
	for (int i = begin; i < end; i++)
		result[i - begin] = values[i];
	return result;
}

// GETTERS
size_t Vector::size() const
{
	return _size;
}

// OPERATORS
double &Vector::operator[](int id) const
{
	if (_size < id)
		throw std::out_of_range("");

	return values[id];
}

Vector &Vector::operator=(Vector other_vector)
{
	this->copy_from(other_vector);
	return *this;
}
void Vector::operator+=(Vector other_vector)
{
	*this = *this + other_vector;
}

Vector Vector::operator+(Vector other_vector) const
{
	if (this->size() != other_vector.size())
		throw std::invalid_argument("Vectors must be of the same length");

	Vector result(this->size());

	for (int i = 0; i < this->size(); i++)
		result[i] = values[i] + other_vector[i];

	return result;
}

Vector Vector::operator-(Vector other_vector) const
{
	if (this->size() != other_vector.size())
		throw std::invalid_argument("Vectors must be of the same length");

	Vector result(this->size());

	for (int i = 0; i < this->size(); i++)
		result[i] = values[i] - other_vector[i];

	return result;
}

double Vector::operator*(Vector other_vector) const
{
	if (this->size() != other_vector.size())
		throw std::invalid_argument("Vectors must be of the same length");

	double result = 0;

	for (int i = 0; i < this->size(); i++)
		result += values[i] * other_vector[i];

	return result;
}

Vector Vector::operator*(double coeficient) const
{
	Vector result(this->size());

	for (int i = 0; i < this->size(); i++)
		result[i] = values[i] * coeficient;

	return result;
}

Vector Vector::operator/(double coeficient) const
{
	return *this * (1 / coeficient);
}

std::istream &operator>>(std::istream &stream, Vector &vector)
{
	for (int i = 0; i < vector.size(); i++)
		stream >> vector[i];
	return stream;
}

std::ostream &operator<<(std::ostream &stream, const Vector &vector)
{
	if (vector.size() == 0)
		return stream;

	for (int i = 0; i < vector.size() - 1; i++)
		stream << vector[i] << ' ';
	stream << vector[vector.size() - 1];
	return stream;
}

} // namespace vector
