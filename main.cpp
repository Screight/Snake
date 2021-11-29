#include "Collision.h"
#include "windows_console.h"
#include "Globals.h"
#include "Input.h"
#include "Render.h"

#include <iostream>
#include <thread>
#include <Windows.h>
#include <conio.h>
#include <math.h>

void Map(std::vector<Vector2D>& walls) {

	for (int i = MAP_INITIAL_X_POSITION; i < MAP_SIZE_X; i++) {
		for (int j = MAP_INITIAL_Y_POSITION; j < MAP_SIZE_Y; j++) {

			if (j == 0 || i == 0 || i == MAP_SIZE_X - 1 || j == MAP_SIZE_Y - 1) {
				setCursorPosition(Vector2D(i, j));
				walls.push_back(Vector2D(i, j));
			}
		}
	}
}

int main()
{
	srand(time(NULL));

	Snake snake = Snake(3);
	std::vector<Vector2D> happyFaces;
	std::vector<Vector2D> walls;

	playing = true;
	score = 0;
	speed = 300;

	//INITIALIZE LEVEL
	Map(walls);
	spawnHappyFace(snake,happyFaces);

	while (playing) 
	{
		Input(snake);

		UpdateLogicAndPhysics(snake,happyFaces,walls);

		Render(happyFaces,walls,snake);

		Sleep(100);
	}

	return 0;
}