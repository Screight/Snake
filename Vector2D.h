#pragma once
class Vector2D
{
public:
	int _componentX;
	int _componentY;

public:
	Vector2D(int _componentX, int _componentY);
	Vector2D();

	friend Vector2D operator*(int scalar, Vector2D vector);

	friend Vector2D operator+(Vector2D vector1, Vector2D vector2);

	friend Vector2D operator-(Vector2D vector1, Vector2D vector2);

	friend bool operator==(Vector2D vector_1, Vector2D Vector_2);

	friend bool operator!=(Vector2D vector_1, Vector2D Vector_2);

	static Vector2D random(Vector2D x_range, Vector2D y_range);
};

