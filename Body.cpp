#include "Body.h"

void Body::move() 
{
	this->position = this->position + direction;
}

Body::Body(Vector2D position, Vector2D direction) {
	this->position = position;
	this->direction = direction;
}

Body::Body() {

}