#ifndef WINDOWS_CONSOLE_H
#define WINDOWS_CONSOLE_H
#include <string>
#include "Vector2D.h"

void setCursorPosition(Vector2D position);

void printAtPosition(char sprite, int horizontal, int vertical);

void printColor(char textToColor, int textColor, int backgroundColor);

#endif // !WINDOWS_CONSOLE_HH
