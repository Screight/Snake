#include "Collision.h"
#include "Globals.h"

void spawnHappyFace(const Snake& snake, std::vector<Vector2D>& happyFaces) {

	char happyFace = static_cast<char>(1);

	Vector2D position = Vector2D::random(Vector2D(MAP_INITIAL_X_POSITION, MAP_SIZE_X), Vector2D(MAP_INITIAL_Y_POSITION, MAP_SIZE_Y));

	bool collides = true;

	while (collides) {
		int i = 0;
		while (i < snake.snakeBody.size()) {
			if (snake.snakeBody[i].position == position) {
				position = Vector2D::random(Vector2D(MAP_INITIAL_X_POSITION, MAP_SIZE_X), Vector2D(MAP_INITIAL_Y_POSITION, MAP_SIZE_Y));
				break;
			}
			i++;
		}
		if (i == snake.snakeBody.size()) {
			collides = false;
		}
	}

	happyFaces.push_back(position);
}

int collides(Vector2D mainObject, const std::vector<Vector2D> objectsToCollideWith)
{

	for (int i = 0; i < objectsToCollideWith.size(); i++) {
		if (mainObject == objectsToCollideWith[i]) {
			return i;
		}
	}

	return -1;
}

void collidesWalls(Snake snake, std::vector<Vector2D> walls) {
	if (collides(snake.snakeBody[0].position, walls) != -1) {
		playing = false;
	}
}

void collidesHappyFace(Snake& snake, std::vector<Vector2D>& happyFaces) {
	if (collides(snake.snakeBody[0].position, happyFaces) != -1) {

		int index = collides(snake.snakeBody[0].position, happyFaces);

		happyFaces.erase(happyFaces.begin() + index);
		score++;

		Vector2D position;

		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {

				if (abs(i) != abs(j)) {
					for (int k = 0; k < snake.snakeBody.size(); k++) {
						if (snake.snakeBody[k].position != snake.snakeBody[k].position + Vector2D(i, j)) {
							position = snake.snakeBody[k].position + Vector2D(i, j);
						}
					}
				}
			}
		}

		snake.snakeBody.push_back(Body(position, snake.snakeBody[snake.snakeBody.size() - 1].position - position));

		snake.snakeBody[snake.snakeBody.size() - 2].sprite = 'o';

		spawnHappyFace(snake, happyFaces);
		if (speed > 50) {
			speed -= 10;
		}

	}
}


void UpdateLogicAndPhysics(Snake& snake, std::vector<Vector2D>& happyFaces, std::vector<Vector2D>& walls) {
	collidesWalls(snake,walls);
	collidesHappyFace(snake, happyFaces);
	snake.move();
}