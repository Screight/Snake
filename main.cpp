#include <iostream>
#include <thread>
#include "windows_console.h"
#include <conio.h>
#include "Vector2D.h"
#include "Snake.h"
#include <math.h>

static  enum COLORS { BLACK, BLUE, GREEN, BRIGHT_BLUE, RED, PURPLE, YELLOW, BRIGHT_GREY, GREY, CYAN, BRIGHT_GREEN, BRIGHT_CYAN, BRIGHT_RED, BRIGHT_PURPLE, BRIGHT_YELLOW, WHITE };

static bool s_Finished = false;
static bool playing = true;
static const int MAP_INITIAL_X_POSITION = 0;
static const int MAP_INITIAL_Y_POSITION = 0;
static const int MAP_SIZE_X = 30;
static const int MAP_SIZE_Y = 30;
static int score = 0;
static int speed = 300;

enum KEY_CODES {KB_UP = 72, KB_DOWN = 80, KB_LEFT = 75, KB_RIGHT = 77};

bool collides(const Snake& snake) 
{
	for (int i = 0; i < MAP_SIZE_X; i++) {
		for (int j = 0; j < MAP_SIZE_Y; j++) {

			if (j == 0 || i == 0 || i == MAP_SIZE_X - 1 || j == MAP_SIZE_Y - 1) {

				if (snake.snakeBody[0].position == Vector2D(i,j)) {
					return true;
				}

			}

		}

	}

	for (int i = 1; i < snake.snakeBody.size(); i++) {
		if (snake.snakeBody[0].position == snake.snakeBody[i].position) {
			return true;
		}
	}

	return false;
}

void spawnHappyFace(const Snake& snake, std::vector<Vector2D>& happyFaces) {

	char happyFace = static_cast<char>(1);

	Vector2D position = Vector2D::random(Vector2D(MAP_INITIAL_X_POSITION,MAP_SIZE_X), Vector2D(MAP_INITIAL_Y_POSITION, MAP_SIZE_Y));

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

	setCursorPosition(position);
	//printf("%c", happyFace);
	printColor(happyFace,COLORS::BRIGHT_YELLOW,COLORS::BLACK);
	happyFaces.push_back(position);
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

	position = Vector2D(50, 10);
	setCursorPosition(position);
	std::cout << "BUG ALERT: if u hit 2 keys fast enough u can";
	position._componentY++;
	setCursorPosition(position);
	std::cout << "trick the system and go backwards resulting in a loss.";
	position._componentY++;
	position._componentY++;
	setCursorPosition(position);
	std::cout << "When picking a coin near a wall the tail might spawn";
	position._componentY++;
	setCursorPosition(position);
	std::cout << "inside the wall producing a hole in it.";

}

void Move(Snake* snake, std::vector<Vector2D>* happyFaces)
{
	while (!s_Finished) {

		setCursorPosition(snake->snakeBody[snake->snakeBody.size() - 1].position);
		
		printf("%c",' ');

		snake->move();
		displayUI();

		if (collides(*snake)) {
			playing = false;
			s_Finished = true;
		}

		for (int i = 0; i < happyFaces->size(); i++) {
			if (snake->snakeBody[0].position == (*happyFaces)[i]) {
				happyFaces->erase(happyFaces->begin() + i);
				score++;
				
				Vector2D position;

				for (int i = -1; i < 2; i++) {
					for (int j = -1; j < 2; j++) {
					
						if (abs(i) != abs(j)) {
							for (int k = 0; k < snake->snakeBody.size(); k++) {
								if (snake->snakeBody[k].position != snake->snakeBody[k].position + Vector2D(i, j)) {
									position = snake->snakeBody[k].position + Vector2D(i, j);
								}
							}
						}
					}
				}

				snake->snakeBody.push_back(Body(position,snake->snakeBody[snake->snakeBody.size()-1].position - position));

				if (snake->snakeBody[snake->snakeBody.size() - 1].direction == Vector2D(1, 0)) {
					snake->snakeBody[snake->snakeBody.size() - 1].sprite = '<';
				}
				else if (snake->snakeBody[snake->snakeBody.size() - 1].direction == Vector2D(-1, 0)) {
					snake->snakeBody[snake->snakeBody.size() - 1].sprite = '>';
				}
				else if (snake->snakeBody[snake->snakeBody.size() - 1].direction == Vector2D(0, 1)) {
					snake->snakeBody[snake->snakeBody.size() - 1].sprite = '^';
				}
				else {
					snake->snakeBody[snake->snakeBody.size() - 1].sprite = '"';
				}
				
				snake->snakeBody[snake->snakeBody.size() - 2].sprite = 'o';
				spawnHappyFace(*snake, *happyFaces);
				if (speed > 50) {
					speed -= 10;
				}
				
			}
		}
		
		if (snake->snakeBody[snake->snakeBody.size() - 1].direction == Vector2D(1, 0)) {
			snake->snakeBody[snake->snakeBody.size() - 1].sprite = '<';
		}
		else if (snake->snakeBody[snake->snakeBody.size() - 1].direction == Vector2D(-1, 0)) {
			snake->snakeBody[snake->snakeBody.size() - 1].sprite = '>';
		}
		else if (snake->snakeBody[snake->snakeBody.size() - 1].direction == Vector2D(0, 1)) {
			snake->snakeBody[snake->snakeBody.size() - 1].sprite = '^';
		}
		else {
			snake->snakeBody[snake->snakeBody.size() - 1].sprite = '"';
		}

		for (int i = 0; i < snake->snakeBody.size(); i++) {
			setCursorPosition(snake->snakeBody[i].position);
			printf("%c", snake->snakeBody[i].sprite);
		}

		

		setCursorPosition(Vector2D(0,0));

		std::this_thread::sleep_for(std::chrono::milliseconds(speed));
	}
}

void input(Snake& snake) {

	Vector2D direction;

	if (_getch() == 224) {

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

	if (direction != Vector2D(0,0)) {
		snake.snakeBody[0].direction = direction;
	}
	s_Finished = true;
}



int main()
{
	srand(time(NULL));

	Vector2D userInput;
	Snake snake = Snake(2);
	std::vector<Vector2D> happyFaces;

	std::chrono::high_resolution_clock::time_point time;

	std::chrono::duration<double> diff;

	//DRAW MAP
	for (int i = 0; i < MAP_SIZE_X; i++) {
		for (int j = 0; j < MAP_SIZE_Y; j++) {

			if (j == 0 || i == 0 || i == MAP_SIZE_X - 1 || j == MAP_SIZE_Y - 1) {
				setCursorPosition(Vector2D(i,j));
				//printf("%c",'#');
				printColor('#',COLORS::WHITE,COLORS::WHITE);
			}

		}

	}

	displayUI();

	spawnHappyFace(snake, happyFaces);

	while (playing) 
	{
		s_Finished = false;
		std::thread worker(Move,&snake,&happyFaces);

		input(snake);

		diff = std::chrono::high_resolution_clock::now() - time;
		if (diff.count() > 0.5) {

			time = std::chrono::high_resolution_clock::now();
		}
		
		worker.join();
	}
	

	return 0;
}