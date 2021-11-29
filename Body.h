#pragma once

#include "Vector2D.h"

class Body
{
public:
	char sprite = 'o';
	Vector2D position;
	Vector2D direction = Vector2D(1,0);

	void move();
	Body(Vector2D position, Vector2D direction);
	Body();
};

