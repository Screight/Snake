#include "vector2D.h"
#include <random>

Vector2D::Vector2D() {

	_componentX = 0;
	_componentY = 0;
}

 Vector2D::Vector2D(int _componentX, int _componentY) {
	this->_componentX = _componentX;
	this->_componentY = _componentY;
}

Vector2D operator*(int scalar, Vector2D vector) {

	vector._componentX = vector._componentX * scalar;
	vector._componentY = vector._componentY * scalar;

	return vector;
}

Vector2D operator+(Vector2D vector1, Vector2D vector2) {

	Vector2D result;

	result._componentX = vector1._componentX + vector2._componentX;
	result._componentY = vector1._componentY + vector2._componentY;

	return result;
}

Vector2D operator-(Vector2D vector1, Vector2D vector2) {

	return vector1 + (-1 * vector2);
}

bool operator==(Vector2D vector_1, Vector2D vector_2) {

	bool _compareX = vector_1._componentX == vector_2._componentX;
	bool _compareY = vector_1._componentY == vector_2._componentY;
	if (_compareX && _compareY) {
		return true;
	}
	else {
		return false;
	}
}

bool operator!=(Vector2D vector_1, Vector2D vector_2) {

	bool _compare = vector_1 == vector_2;
	if (_compare) {
		return false;
	}
	else {
		return true;
	}
}

Vector2D Vector2D::random(Vector2D x_range, Vector2D y_range) {

	Vector2D random_vector;

	random_vector._componentX = (x_range._componentX + 1) + rand() % (x_range._componentY - 2);
	random_vector._componentY = (y_range._componentX + 1) + rand() % (y_range._componentY - 2);

	return random_vector;

}