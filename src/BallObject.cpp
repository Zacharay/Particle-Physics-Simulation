#include "BallObject.hpp"
#include <iostream>
BallObject::BallObject()
{
	this->currentPosition = glm::vec2(400.0f, 400.0f);
	this->previousPosition = glm::vec2(400.0f, 400.0f);
	this->acceleration = glm::vec2(0.0f, 0.0f);
}
BallObject::BallObject(glm::vec2 position)
{
	this->currentPosition = position;
	this->previousPosition = position;
	this->acceleration = glm::vec2(0.0f, 0.0f);
}

void BallObject::updatePosition(float dt)
{
	glm::vec2 velocity = this->currentPosition - this->previousPosition;
	std::cout << acceleration.x << " " << acceleration.y << std::endl;
	this->previousPosition = this->currentPosition;

	this->currentPosition = this->currentPosition + velocity + this->acceleration * dt * dt;

	this->acceleration = glm::vec2(0.0f, 0.0f);
}

void BallObject::accelerate(glm::vec2 acc)
{
	this->acceleration += acc;;
}

glm::vec2 BallObject::getCurrentPosition() const
{
	return this->currentPosition;
}
glm::vec2 BallObject::getPreviousPosition() const
{
	return this->previousPosition;
}

float BallObject::getRadius() const
{
	return this->radius;
}

void BallObject::setCurrentPosition(glm::vec2 pos)
{
	this->currentPosition = pos;
}


void BallObject::setPreviousPosition(glm::vec2 pos)
{
	this->previousPosition = pos;
}
