#pragma once
#include <vector>
#include "Vector2D.h"
#include "Snake.h"

void UpdateLogicAndPhysics(Snake& snake, std::vector<Vector2D>& happyFaces, std::vector<Vector2D>& walls);

void spawnHappyFace(const Snake& snake, std::vector<Vector2D>& happyFaces, const std::vector<Vector2D>& walls);