#include "Snake.h"
#include "windows_console.h"
#include <iostream>

Snake::Snake(int _bodyParts) {
	for (int i = 0; i < _bodyParts + 1; i++) {
		snakeBody.push_back(Body());
		if (i != 0) {
			snakeBody[i].position._componentX = snakeBody[i - 1].position._componentX - 1;
		}
		else {
			snakeBody[i].position._componentX = 8;
			snakeBody[i].sprite = static_cast<char>(1);
			snakeBody[i].direction._componentX = 1;
		}
		snakeBody[i].position._componentY = 5;
	}
	snakeBody[_bodyParts - 1].sprite = '<';
}



void Snake::move() {

	for (int i = 0; i < snakeBody.size(); i++) {
		snakeBody[i].position = snakeBody[i].position + snakeBody[i].direction;
	}

	if (snakeBody.size() > 0) {
		for (int i = 1; i < snakeBody.size(); i++) {
			snakeBody[i].direction = snakeBody[i - 1].position - snakeBody[i].position;
		}
	}
}