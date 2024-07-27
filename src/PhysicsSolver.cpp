#include "PhysicsSolver.hpp"

#include <iostream>
#include <thread>
PhysicsSolver::PhysicsSolver()
{
	constexpr float gridCellSize = 40.0f;

	this->grid = new UniformGrid(gridCellSize);

	

	this->objects.reserve(MAX_OBJECTS);
}

void PhysicsSolver::spawnObject(float xPos, float yPos)
{
	

	glm::vec2 spawnerPos = glm::vec2(xPos, yPos);
	

	this->objects.emplace_back(std::make_unique<BallObject>(spawnerPos, spawnerPos, m_ballColor, m_ballRadius));
}
void PhysicsSolver::applyPhysics(float dt)
{
		
		for (int i = 0; i < 4; i++)
		{
			
			applyGravity();
			applyConstrains();
			solveCollisions();
			
			updatePositions(dt/4.0f);
			this->grid->clearGrid();
		}

}
unsigned int PhysicsSolver::getCollisionChecks()
{
	return this->collisionChecks;
}
void PhysicsSolver::updatePositions(float dt)
{
	for (const std::unique_ptr<BallObject>&obj : this->objects)
	{
		obj->updatePosition(dt);
	}

}
void PhysicsSolver::applyGravity()
{

	for (const std::unique_ptr<BallObject>& obj : this->objects)
	{
		obj->accelerate(m_gravity);

	}

}
void PhysicsSolver::applyConstrains()
{
	for (int i = 0; i < this->objects.size(); i++)
	{
		BallObject& obj = *this->objects[i];
		float radius = obj.getRadius();

		glm::vec2 velocity = obj.currentPosition - obj.previousPosition;

		if (obj.currentPosition.x < radius)
		{
			obj.currentPosition = glm::vec2(radius, obj.currentPosition.y);
			obj.previousPosition = glm::vec2(obj.previousPosition.x + velocity.x, obj.previousPosition.y);
		}
		else if (obj.currentPosition.x > SIMULATION_WIDTH - radius)
		{
			obj.currentPosition= glm::vec2(SIMULATION_WIDTH - radius, obj.currentPosition.y);
			obj.previousPosition = glm::vec2(obj.previousPosition.x + velocity.x, obj.previousPosition.y);
		}

		velocity = obj.currentPosition - obj.previousPosition;
		if (obj.currentPosition.y < radius)
		{
			obj.currentPosition=glm::vec2(obj.currentPosition.x, radius);
			obj.previousPosition=glm::vec2(obj.previousPosition.x, obj.previousPosition.y + velocity.y);
		}
		else if (obj.currentPosition.y > SIMULATION_HEIGHT - radius)
		{
			obj.currentPosition = glm::vec2(obj.currentPosition.x, SIMULATION_HEIGHT - radius);
			obj.previousPosition = glm::vec2(obj.previousPosition.x, obj.previousPosition.y + velocity.y);
		}


		glm::vec2 currentPos = obj.currentPosition;
		grid->addItem(currentPos.x, currentPos.y, i);
	}
}
void PhysicsSolver::solveCollisions()
{
	unsigned int currentCollisions = 0;
	for (int cellID = 0; cellID < grid->getNumOfCells(); cellID++)
	{
		std::vector<unsigned int> currentCellObjectsID = grid->getCellItems(cellID);
		std::vector<unsigned int> neighboursObjectsID;
		grid->getNeighbours(cellID, neighboursObjectsID);

		for (unsigned int currentCellObjID: currentCellObjectsID)
		{
			
			BallObject & currentCellObj = *this->objects[currentCellObjID];
			

			for (unsigned int currentCellSecondObjID : currentCellObjectsID)
			{
				if (currentCellObjID == currentCellSecondObjID)continue;


				BallObject& currentCellSecondObj = *this->objects[currentCellSecondObjID];
				
				currentCollisions++;
				
				resolveCollision(currentCellObj,currentCellSecondObj);
			}
			for (unsigned int nbrID:neighboursObjectsID)
			{
				BallObject& nbrObj = *this->objects[nbrID];
				
				currentCollisions++;
				resolveCollision(currentCellObj, nbrObj);
			}
		}


	}

	this->collisionChecks = currentCollisions;

}
void PhysicsSolver::resolveCollision(BallObject& ballObj1, BallObject& ballObj2)
{
	glm::vec2 position1 = ballObj1.currentPosition;
	glm::vec2 position2 = ballObj2.currentPosition;

	glm::vec2 collisionAxis = position1 - position2;

	float radiusSum = ballObj1.getRadius() + ballObj2.getRadius();
	float centerDistance = glm::length(collisionAxis);

	bool doBallsColide = centerDistance < radiusSum;

	if (!doBallsColide)return;


	glm::vec2 normalizedCollisionAxis = collisionAxis / centerDistance;
	float halfOverlap = (centerDistance - radiusSum) * 0.5f*0.75f ;

	glm::vec2 displacement = halfOverlap * normalizedCollisionAxis;

	ballObj1.currentPosition = position1 - displacement;
	ballObj2.currentPosition = position2 + displacement ;
}


void PhysicsSolver::resetSimulationState()
{
	this->objects.clear();
	this->grid->clearGrid();
}

void PhysicsSolver::setGravity(glm::vec2 gravity)
{
	m_gravity = gravity;
}

void PhysicsSolver::setRadius(float radius)
{
	m_ballRadius = radius;
}

void PhysicsSolver::setColor(glm::vec3 color)
{
	m_ballColor = color;
}
