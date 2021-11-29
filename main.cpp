#include "Collision.h"
#include "windows_console.h"
#include "Globals.h"
#include "Input.h"
#include "Render.h"

#include <iostream>
#include <fstream>
#include <thread>
#include <Windows.h>
#include <conio.h>
#include <math.h>

void Map(std::vector<Vector2D>& walls) {

	// string to store file lines (all the characters until the end of the current line)
	std::string textCopied = " ";
	// declare a file
	std::fstream file;
	// open a file in read mode
	file.open("level_1.txt", std::ios::in);

	// while we haven't reach the end of the file
	/*Returns true if the eofbit error state flag is set for the stream.
	This flag is set by all standard input operations when the End - of - File is reached in the sequence associated with the stream.*/
	int j = 0;
	int i = 0;
	while (!file.eof()) {
		file >> textCopied;

		// copy char by char from string to the correspondong row in the map (according to current read line)
		for (int i = 0; i < textCopied.size(); i++) {
			if (textCopied[i] == '#') {
				walls.push_back(Vector2D(MAP_INITIAL_X_POSITION + i, MAP_INITIAL_Y_POSITION + j));
			}
		}
		// move into the next line
		j++;

	}
	// close the file
	file.close();
}

void Initialize(Snake& snake, std::vector<Vector2D>& walls, std::vector<Vector2D>& happyFaces) {
	Map(walls);
	spawnHappyFace(snake, happyFaces,walls);
	renderMap(walls);
}

int main()
{
	srand(time(NULL));

	Snake snake = Snake(3);
	std::vector<Vector2D> happyFaces;
	std::vector<Vector2D> walls;

	playing = true;
	score = 0;
	speed = 200;

	Initialize(snake,walls,happyFaces);
	

	while (playing) 
	{
		Input(snake);

		UpdateLogicAndPhysics(snake,happyFaces,walls);

		Render(happyFaces,walls,snake);

		Sleep(speed);
	}

	return 0;
}