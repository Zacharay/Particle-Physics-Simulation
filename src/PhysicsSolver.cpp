#include "PhysicsSolver.hpp"
#include "Globals.hpp"
#include <iostream>
PhysicsSolver::PhysicsSolver(std::vector<BallObject*>& objects):gameObjects(objects)
{

}


void PhysicsSolver::applyPhysics(float dt)
{
	//float substeps = 8;
	//float sub_dt = dt / substeps;
	//std::cout << sub_dt << std::endl;
	//for (int i = 0; i < substeps; i++)
	//{
			applyGravity();
			applyConstrains();
			updatePositions(dt);
		
	//}

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



