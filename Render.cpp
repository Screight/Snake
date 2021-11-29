#include "Render.h"
#include "Globals.h"
#include "windows_console.h"
#include <iostream>

static  enum COLORS { BLACK, BLUE, GREEN, BRIGHT_BLUE, RED, PURPLE, YELLOW, BRIGHT_GREY, GREY, CYAN, BRIGHT_GREEN, BRIGHT_CYAN, BRIGHT_RED, BRIGHT_PURPLE, BRIGHT_YELLOW, WHITE };

void renderMap(std::vector<Vector2D> walls) {
	for (int i = 0; i < walls.size(); i++) {
		setCursorPosition(walls[i]);
		printColor('#',COLORS::WHITE,COLORS::WHITE);
	}
}

void renderHappyFaces(std::vector<Vector2D> happyFaces) {
	for (int i = 0; i < happyFaces.size(); i++) {
		setCursorPosition(happyFaces[i]);
		std::cout << static_cast<char>(1);
	}
}

void displayUI() {

	Vector2D position = Vector2D(50, 2);

	setCursorPosition(position);
	std::cout << "Score: " << score;
	position._componentY++;

	setCursorPosition(position);
	std::cout << "                   ";
	setCursorPosition(position);
	std::cout << "Speed: " << 310 - speed;
	position._componentY++;
	position._componentY++;
	setCursorPosition(position);
	std::cout << "When picking a coin near a wall the tail might spawn";
	position._componentY++;
	setCursorPosition(position);
	std::cout << "inside the wall producing a hole in it.";

}

void renderSnake(const Snake& snake) {
	for (int i = 0; i < snake.snakeBody.size() - 1; i++) {
		if (i == 0) {
			setCursorPosition(snake.snakeBody[0].position);
			std::cout << static_cast<char>(1);
		}
		else if (i == snake.snakeBody.size() - 2) {
			setCursorPosition(snake.snakeBody[snake.snakeBody.size() - 1].position);
			std::cout << " ";
			setCursorPosition(snake.snakeBody[i].position);
			if (snake.snakeBody[snake.snakeBody.size() - 2].direction == Vector2D(1, 0)) {
				std::cout << '<';
			}
			else if (snake.snakeBody[snake.snakeBody.size() - 2].direction == Vector2D(-1, 0)) {
				std::cout << '>';
			}
			else if (snake.snakeBody[snake.snakeBody.size() - 2].direction == Vector2D(0, 1)) {
				std::cout << '^';
			}
			else {
				std::cout << '"';
			}
		}
		else {
			setCursorPosition(snake.snakeBody[i].position);
			std::cout << "o";
		}
	}
}

void Render(const std::vector<Vector2D>& happyFaces,const std::vector<Vector2D>& walls, const Snake& snake) {
	renderMap(walls);
	renderHappyFaces(happyFaces);
	renderSnake(snake);
	displayUI();
	setCursorPosition(Vector2D(0, 0));
}

