#include "BallObject.hpp"
#include <iostream>
BallObject::BallObject():radius(10.0f)
{
	this->currentPosition = glm::vec2(400.0f, 400.0f);
	this->previousPosition = glm::vec2(400.0f, 400.0f);
	this->acceleration = glm::vec2(0.0f, 0.0f);
	this->ballColor = glm::vec3(1.0f, 1.0f, 1.0f);

}
BallObject::BallObject(glm::vec2 position,glm::vec3 color,float radius):radius(radius)
{
	this->currentPosition = position;
	this->previousPosition = position;
	this->acceleration = glm::vec2(0.0f, 0.0f);

	this->ballColor = color;

}

void BallObject::updatePosition(float dt)
{
	

	glm::vec2 velocity = this->currentPosition - this->previousPosition;
	
	this->previousPosition = this->currentPosition;

	this->currentPosition = this->currentPosition + velocity + this->acceleration * (dt * dt);

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

glm::vec3 BallObject::getBallColor() const
{
	return this->ballColor;
}

void BallObject::setCurrentPosition(glm::vec2 pos)
{
	this->currentPosition = pos;
}


void BallObject::setPreviousPosition(glm::vec2 pos)
{
	this->previousPosition = pos;
}
