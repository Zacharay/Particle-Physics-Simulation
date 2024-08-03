#include "PhysicsSolver.hpp"

#include <iostream>
#include <thread>
#include "PhysicsSolver.hpp"




PhysicsSolver::PhysicsSolver()
{
	ptr_grid = std::make_unique<UniformGrid>(c_gridCellSize);

	this->m_particles.reserve(MAX_OBJECTS);
	
}

void PhysicsSolver::spawnParticle(float xPos, float yPos,glm::vec3 ballColor,bool isKinematic)
{
	
	glm::vec2 spawnerPos = glm::vec2(xPos, yPos);

	this->m_particles.emplace_back(std::make_shared<Particle>(spawnerPos, spawnerPos, ballColor, m_ballRadius,isKinematic));
	

	
}
void PhysicsSolver::spawnLinkedParticles(std::vector<std::shared_ptr<Particle>>& tempParticles)
{
	m_particles.push_back(tempParticles[0]);
	for (int i = 1; i < tempParticles.size(); i++)
	{
		m_particles.push_back(tempParticles[i]);

		links.emplace_back(std::make_unique<Link>(tempParticles[i - 1], tempParticles[i], tempParticles[i]->getRadius()*2));
	}
}
void PhysicsSolver::spawnCube(float xPos, float yPos, glm::vec3 color)
{
	const int cubeSize = 7;
	const unsigned int startIdx = this->m_particles.size();

	const float diameter = m_ballRadius * 2;

	const float linkLength = (diameter * sqrtf(2));
	const float startXPos = xPos - (static_cast<float>(cubeSize / 2) * m_ballRadius * 2);
	const float startYPos = yPos + (static_cast<float>(cubeSize / 2) * m_ballRadius * 2);

	for (int row = 0; row < cubeSize; row++)
	{
		for (int col = 0; col < cubeSize; col++)
		{
			glm::vec2 spawnerPos = glm::vec2(startXPos + col * diameter, startYPos - row * diameter);

			this->m_particles.emplace_back(std::make_shared<Particle>(spawnerPos, spawnerPos, color, m_ballRadius, true));

			const int currentIndex = startIdx + (row * cubeSize) +  col;



			if (col != 0)
			{
				this->links.emplace_back(std::make_unique<Link>(this->m_particles[currentIndex], this->m_particles[currentIndex - 1], diameter));
			}

			if (row != 0)
			{
				
				this->links.emplace_back(std::make_unique<Link>(this->m_particles[currentIndex], this->m_particles[currentIndex - cubeSize], diameter));
			}
			if (col != 0 && row != 0)
			{
				
				this->links.emplace_back(std::make_unique<Link>(this->m_particles[currentIndex], this->m_particles[currentIndex - cubeSize -1 ], linkLength));
			}
			if (row != 0 && col != cubeSize - 1)
			{
				
				this->links.emplace_back(std::make_unique<Link>(this->m_particles[currentIndex], this->m_particles[currentIndex - cubeSize + 1], linkLength));
			}
		}
	}
	
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
	for (const std::shared_ptr<Particle>&particle : this->m_particles)
	{
		particle->updatePosition(dt);
	}

}
void PhysicsSolver::updateSticks()
{
	for (std::unique_ptr<Link>& link : links)
	{
		glm::vec2 axisBetweenObjects = link->m_firstParticle->getCurrentPosition() - link->m_secondParticle->getCurrentPosition();

		float currentDistance = glm::length(axisBetweenObjects);
		

		float scalar = (currentDistance - link->m_desiredLength) / 2;

		axisBetweenObjects = glm::normalize(axisBetweenObjects);

		link->m_firstParticle->moveByVector(-axisBetweenObjects * scalar);
		
		link->m_secondParticle->moveByVector(axisBetweenObjects * scalar);

	}
}
void PhysicsSolver::applyGravity()
{

	for (const std::shared_ptr<Particle>& obj : this->m_particles)
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
	for (const std::shared_ptr<Particle>&obj :this->m_particles)
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
			
			Particle & currentCellObj = *this->m_particles[currentCellObjID];
			

			for (unsigned int currentCellSecondObjID : currentCellObjectsID)
			{
				if (currentCellObjID == currentCellSecondObjID)continue;


				Particle& currentCellSecondObj = *this->m_particles[currentCellSecondObjID];
				
				currentCollisions++;
				
				resolveCollision(currentCellObj,currentCellSecondObj);
			}
			for (unsigned int nbrID:neighboursObjectsID)
			{
				Particle& nbrObj = *this->m_particles[nbrID];
				
				currentCollisions++;
				resolveCollision(currentCellObj, nbrObj);
			}
		}


	}

	m_collisionChecks = currentCollisions;

}
void PhysicsSolver::resolveCollision(Particle & ballObj1, Particle & ballObj2)
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
	this->m_particles.clear();
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
