#include "PhysicsSolver.hpp"
#include "Globals.hpp"
#include "UniformGrid.hpp"
#include <iostream>
PhysicsSolver::PhysicsSolver(std::vector<BallObject*>& objects):gameObjects(objects)
{
	UniformGrid* grid = new UniformGrid();

	grid->addItem(450, 220, 1);
	grid->addItem(620, 500, 1);
}


void PhysicsSolver::applyPhysics(float dt)
{
	
		applyGravity();
		applyConstrains();
		solveCollisions();
		updatePositions(dt);
	

		
	

}
unsigned int PhysicsSolver::getCollisionChecks()
{
	return this->collisionChecks;
}
void PhysicsSolver::updatePositions(float dt)
{

	for (auto gameObject : this->gameObjects)
	{
		gameObject->updatePosition(dt);

	}
}
void PhysicsSolver::applyGravity()
{

	for (auto gameObject : gameObjects)
	{
		gameObject->accelerate(gravity);

	}

}
void PhysicsSolver::applyConstrains()
{
	for (auto ballObject : this->gameObjects)
	{
		float radius = ballObject->getRadius();
		glm::vec2 currentPosition = ballObject->getCurrentPosition();
		glm::vec2 previousPosition = ballObject->getPreviousPosition();

		glm::vec2 velocity = currentPosition - previousPosition;

		if (currentPosition.x < radius)
		{
			ballObject->setCurrentPosition(glm::vec2(radius, currentPosition.y));
			ballObject->setPreviousPosition(glm::vec2(previousPosition.x + velocity.x, previousPosition.y));
		}
		else if (currentPosition.x > WINDOW_WIDTH - radius)
		{
			ballObject->setCurrentPosition(glm::vec2(WINDOW_WIDTH - radius, currentPosition.y));
			ballObject->setPreviousPosition(glm::vec2(previousPosition.x + velocity.x, previousPosition.y));
		}

		currentPosition = ballObject->getCurrentPosition();
		previousPosition = ballObject->getPreviousPosition();
		velocity = currentPosition - previousPosition;
		if (currentPosition.y < radius)
		{
			ballObject->setCurrentPosition(glm::vec2(currentPosition.x, radius));
			ballObject->setPreviousPosition(glm::vec2(previousPosition.x, previousPosition.y + velocity.y));
		}
		else if (currentPosition.y > WINDOW_HEIGHT - radius)
		{
			ballObject->setCurrentPosition(glm::vec2(currentPosition.x, WINDOW_HEIGHT - radius));
			ballObject->setPreviousPosition(glm::vec2(previousPosition.x, previousPosition.y + velocity.y));
		}
	}
}
void PhysicsSolver::solveCollisions()
{
	unsigned int currentCollisions = 0;
	for (int i = 0; i < this->gameObjects.size(); i++)
	{
		for (int j = 0; j < this->gameObjects.size(); j++)
		{
			if (i == j)continue;

			BallObject* obj1 = this->gameObjects[i];
			BallObject* obj2 = this->gameObjects[j];
			
			currentCollisions++;
			this->resolveCollision(*obj1, *obj2);

		}
	}
	this->collisionChecks = currentCollisions;
}
void PhysicsSolver::resolveCollision(BallObject& ballObj1, BallObject& ballObj2)
{
	glm::vec2 position1 = ballObj1.getCurrentPosition();
	glm::vec2 position2 = ballObj2.getCurrentPosition();
	glm::vec2 collisionAxis = position1 - position2;

	float radiusSum = ballObj1.getRadius() + ballObj2.getRadius();
	float centerDistance = glm::length(collisionAxis);

	bool doBallsColide = centerDistance < radiusSum;

	if (!doBallsColide)return;

	glm::vec2 normalizedCollisionAxis = collisionAxis / centerDistance;
	float halfOverlap = (centerDistance - radiusSum)*0.5f;

	glm::vec2 displacement = halfOverlap * normalizedCollisionAxis;
	
	ballObj1.setCurrentPosition(position1 - displacement);
	ballObj2.setCurrentPosition(position2 + displacement);

	
}

