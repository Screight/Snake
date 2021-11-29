#ifndef RENDER_H
#define RENDER_H

#include "Vector2D.h"
#include "Snake.h"
#include <vector>

void Render(const std::vector<Vector2D>& happyFaces, const std::vector<Vector2D>& walls, const Snake& snake);

#endif // !RENDER_H
