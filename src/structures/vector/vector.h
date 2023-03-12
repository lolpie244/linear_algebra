#pragma once

#include <functional>
#include <memory>

namespace vector
{

using std::shared_ptr;

class Vector
{
private:
	size_t _size = 0;
	shared_ptr<double[]> values;
	void copy_from(const Vector& other_vector);

public:
	Vector() {}
	Vector(const Vector &other_vector);
	Vector(size_t size);
	// METHODS
	void resize(size_t new_size);
	void fill(size_t count, double value);
	void insert(size_t position, double value);
	double erase(size_t position);
	//
	// GETTERS
	size_t size() const;

	// OPERATORS
	double &operator[](int id) const;
	Vector& operator=(Vector other_vector);
	void operator+=(Vector other_vector);
	Vector operator+(Vector other_vector) const;
	Vector operator-(Vector other_vector) const;
	double operator*(Vector other_vector) const;
	Vector operator*(double coeficient) const;
	Vector operator/(double coeficient) const;
	friend std::istream& operator>>(std::istream& stream, Vector& vector);
	friend std::ostream& operator<<(std::ostream& stream, const Vector& vector);
};
} // namespace vector
