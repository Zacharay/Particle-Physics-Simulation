#include "PhysicsSolver.hpp"
#include "Globals.hpp"
#include <iostream>
PhysicsSolver::PhysicsSolver(std::vector<BallObject*>& objects):gameObjects(objects)
{

}


void PhysicsSolver::applyPhysics(float dt)
{


	
	
	
	
			applyGravity();
			applyConstrains();
			solveCollisions();
			updatePositions(dt);
		
	

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
	for (int i = 0; i < this->gameObjects.size(); i++)
	{
		for (int j = 0; j < this->gameObjects.size(); j++)
		{
			if (i == j)continue;

			BallObject* obj1 = this->gameObjects[i];
			BallObject* obj2 = this->gameObjects[j];
			
			if (this->doBallsCollide(*obj1, *obj2))
			{
				this->resolveCollision(*obj1, *obj2);
			}

		}
	}
}
void PhysicsSolver::resolveCollision(BallObject& ballObj1, BallObject& ballObj2)
{
	glm::vec2 position1 = ballObj1.getCurrentPosition();
	glm::vec2 position2 = ballObj2.getCurrentPosition();

	glm::vec2 delta = position1 - position2;
	
	float minDist = ballObj1.getRadius() + ballObj2.getRadius();
	float distance = glm::length(delta);


	float overlap = (distance - minDist)*0.5f;

	glm::vec2 displacement = delta * (overlap / distance);
	
	ballObj1.currentPosition -= displacement;
	ballObj2.currentPosition += displacement;


	
}
bool PhysicsSolver::doBallsCollide(BallObject & ballObj1, BallObject & ballObj2)
{
	float radius1 = ballObj1.getRadius();
	float radius2 = ballObj2.getRadius();

	glm::vec2 position1 = ballObj1.getCurrentPosition();
	glm::vec2 position2 = ballObj2.getCurrentPosition();


	float centerDistance = (position1.x - position2.x) * (position1.x - position2.x) + (position1.y - position2.y) * (position1.y - position2.y);

	if (centerDistance < (radius1 + radius2) * (radius1 + radius2))
	{
		return true;
	}
	
	return false;
	
}

