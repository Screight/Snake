#include "Input.h"
#include <conio.h>

enum KEY_CODES { KB_UP = 72, KB_DOWN = 80, KB_LEFT = 75, KB_RIGHT = 77 };

void Input(Snake& snake) {

	Vector2D direction;

	if (_kbhit()) {
		_getch();
		switch (_getch()) {
		case KB_UP:
			if (snake.snakeBody[0].direction != Vector2D(0, 1)) {
				direction = Vector2D(0, -1);
			}
			break;
		case KB_DOWN:
			if (snake.snakeBody[0].direction != Vector2D(0, -1)) {
				direction = Vector2D(0, 1);
			}
			break;
		case KB_LEFT:
			if (snake.snakeBody[0].direction != Vector2D(1, 0)) {
				direction = Vector2D(-1, 0);
			}
			break;
		case KB_RIGHT:
			if (snake.snakeBody[0].direction != Vector2D(-1, 0)) {
				direction = Vector2D(1, 0);
			}
			break;
		}
	}
	if (direction != Vector2D(0, 0)) {
		snake.snakeBody[0].direction = direction;
	}
}