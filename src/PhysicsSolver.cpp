#include "PhysicsSolver.hpp"

#include <iostream>
#include <thread>



PhysicsSolver::PhysicsSolver()
{
	ptr_grid = std::make_unique<UniformGrid>(c_gridCellSize);

	this->objects.reserve(MAX_OBJECTS);
	glm::vec2 spawnerPos = glm::vec2(400.0f + float(0 * 20.0f), 400.0f);
	this->objects.emplace_back(std::make_shared<BallObject>(spawnerPos, spawnerPos, m_ballColor, m_ballRadius, false));

	for (int i = 1; i < 20; i++)
	{
		glm::vec2 spawnerPos = glm::vec2(400.0f + float(i*20.0f), 400.0f);
		this->objects.emplace_back(std::make_shared<BallObject>(spawnerPos, spawnerPos, m_ballColor, m_ballRadius, true));
	}

	spawnerPos = glm::vec2(400.0f + float(20 * 20.0f), 400.0f);
	this->objects.emplace_back(std::make_shared<BallObject>(spawnerPos, spawnerPos, m_ballColor, m_ballRadius, true));

	for (int i = 0; i <= 19; i++)
	{
		links.emplace_back(std::make_unique<Link>(this->objects[i], this->objects[i+1], 20));
	}


	
}

void PhysicsSolver::spawnObject(float xPos, float yPos)
{
	
	glm::vec2 spawnerPos = glm::vec2(xPos, yPos);
	this->objects.emplace_back(std::make_shared<BallObject>(spawnerPos, spawnerPos, m_ballColor, m_ballRadius));
}
void PhysicsSolver::applyPhysics(float dt)
{
			
		float sub_dt = dt / static_cast<float>(m_substeps);

		for (int i = 0; i < m_substeps; i++)
		{
			
			applyGravity();
			applyConstrains();
			solveCollisions();
			updateSticks();
			updatePositions(sub_dt);
			ptr_grid->clearGrid();
		}
		
}
unsigned int PhysicsSolver::getCollisionChecks()
{
	return this->m_collisionChecks;
}
void PhysicsSolver::updatePositions(float dt)
{
	for (const std::shared_ptr<BallObject>&obj : this->objects)
	{
		obj->updatePosition(dt);
	}

}
void PhysicsSolver::updateSticks()
{
	for (std::unique_ptr<Link>& link : links)
	{
		glm::vec2 axisBetweenObjects = link->object1->getCurrentPosition() - link->object2->getCurrentPosition();

		float currentDistance = glm::length(axisBetweenObjects);
		

		float scalar = (currentDistance - link->desiredLength) / 2;

		axisBetweenObjects = glm::normalize(axisBetweenObjects);

		link->object1->moveByVector(-axisBetweenObjects * scalar);
		
		link->object2->moveByVector(axisBetweenObjects * scalar);

	}
}
void PhysicsSolver::applyGravity()
{

	for (const std::shared_ptr<BallObject>& obj : this->objects)
	{
		obj->accelerate(m_gravity);

		if (m_isForceModeEnabled)
		{
			glm::vec2 currentAxis = m_forceOrigin - obj->getCurrentPosition();


			float dist = glm::length(currentAxis);

			if (dist > m_forceRadius) continue;

			currentAxis = glm::normalize(currentAxis);

			float scalar = m_forceStrength*100.0f * static_cast<float>(m_forceMode);

			obj->accelerate(currentAxis* scalar);

		}

	}
	
}
void PhysicsSolver::applyConstrains()
{
	int idx = 0;
	for (const std::shared_ptr<BallObject>&obj :this->objects)
	{
		obj->applyConstrains();
		ptr_grid->addItem(obj->getCurrentPosition().x, obj->getCurrentPosition().y, idx);
		idx++;
	}
	

}
void PhysicsSolver::solveCollisions()
{
	unsigned int currentCollisions = 0;
	for (int cellID = 0; cellID < ptr_grid->getNumOfCells(); cellID++)
	{
		std::vector<unsigned int> currentCellObjectsID = ptr_grid->getCellItems(cellID);
		std::vector<unsigned int> neighboursObjectsID;
		ptr_grid->getNeighbours(cellID, neighboursObjectsID);

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

	m_collisionChecks = currentCollisions;

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
	float halfOverlap = (centerDistance - radiusSum) * 0.5f*0.75f ;

	glm::vec2 displacement = halfOverlap * normalizedCollisionAxis;

	ballObj1.moveByVector(-displacement);
	ballObj2.moveByVector(displacement);
}


void PhysicsSolver::resetSimulationState()
{
	this->objects.clear();
	ptr_grid->clearGrid();
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

void PhysicsSolver::setAttraction(bool isAttractionEnabled, glm::vec2 attractionPos)
{
	m_isForceModeEnabled = isAttractionEnabled;
	m_forceOrigin = attractionPos;
}
void PhysicsSolver::setForceMode(int forceMode)
{
	m_forceMode = forceMode;
}

void PhysicsSolver::setForceRadius(float forceRadius)
{
	m_forceRadius = forceRadius;
}

void PhysicsSolver::setForceStrength(float forceStrength)
{
	m_forceStrength = forceStrength;
}
