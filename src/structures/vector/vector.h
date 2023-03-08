#pragma once

#include <memory>

namespace vector
{

using std::shared_ptr;

class Vector
{
private:
	size_t _size = 0;
	shared_ptr<double[]> values;

public:
	Vector() {}
	Vector(size_t size);
	// METHODS
	void resize(size_t new_size);

	void fill(size_t count, double value);

	void insert(size_t position, double value);

	// GETTERS
	size_t size() const;


	// OPERATORS
	double &operator[](int id) const;

	Vector operator=(Vector other_vector);

	Vector operator+(Vector other_vector);

	Vector operator-(Vector other_vector);

	double operator*(Vector other_vector);

};
} // namespace vector
