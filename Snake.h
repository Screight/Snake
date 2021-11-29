#pragma once
#include "Body.h"
#include <vector>

class Snake
{
public:
	std::vector<Body> snakeBody;

	void move();
	Snake(int _bodyParts);
};

