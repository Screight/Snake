#include "windows_console.h"
#include <Windows.h>
#include <conio.h>
#include <iostream>
#include "Vector2D.h"

void printAtPosition(char sprite, int horizontal, int vertical) {
	HANDLE current_console;
	current_console = GetStdHandle(
		STD_OUTPUT_HANDLE);

	COORD coord;
	coord.X = horizontal;
	coord.Y = vertical;

	SetConsoleCursorPosition(current_console, coord);

	printf("%c", sprite);


}

void setCursorPosition(Vector2D position) {

	HANDLE current_console;
	current_console = GetStdHandle(
		STD_OUTPUT_HANDLE);

	COORD coord;
	coord.X = position._componentX;
	coord.Y = position._componentY;

	SetConsoleCursorPosition(current_console, coord);
}

int getColorValue(int textColor, int backgroundColor) {

	int colorValue = textColor + 16 * backgroundColor;

	return colorValue;
}

void printColor(char textToColor, int textColor, int backgroundColor) {

	HANDLE console;
	console = GetStdHandle(STD_OUTPUT_HANDLE);

	int colorValue = getColorValue(textColor, backgroundColor);

	// P is color code of the
		// corresponding color
	SetConsoleTextAttribute(
		console, colorValue);

	// Print Statement
	std::cout << textToColor;

	SetConsoleTextAttribute(
		console, 15);
}