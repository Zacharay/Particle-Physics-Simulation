#pragma once
#include "BallObject.hpp"
#include <vector>
#include "Globals.hpp"
#include "UniformGrid.hpp"
#include <memory>


struct Link {
	std::shared_ptr<BallObject> object1;
	std::shared_ptr<BallObject>  object2;
	float desiredLength;

	Link(std::shared_ptr<BallObject>obj1, std::shared_ptr<BallObject>obj2, float length) :
		object1(obj1),
		object2(obj2),
		desiredLength(length) {};
};

class PhysicsSolver{
	const float c_gridCellSize = 40.0f;
	
	unsigned int m_substeps = 4;

	glm::vec2 m_gravity = glm::vec2(0.0f, -2000.0f);
	glm::vec3 m_ballColor = glm::vec3(0.0f,0.0f,0.0f);
	float m_ballRadius = 10.0f;


	std::unique_ptr<UniformGrid> ptr_grid;
	std::vector<std::unique_ptr<Link>> links;

	unsigned int m_collisionChecks = 0;
	
	void applyConstrains();
	void applyGravity();
	void updateSticks();
	void updatePositions(float dt);
	void solveCollisions();
	void resolveCollision(BallObject& ballObj1, BallObject& ballObj2);
	
public:
	
	void spawnObject(float xPos, float yPos);
	std::vector<std::shared_ptr<BallObject>>objects;
	PhysicsSolver();
	void applyPhysics(float dt);
	unsigned int getCollisionChecks();
	void resetSimulationState();

	void setGravity(glm::vec2 gravity);
	void setRadius(float radius);
	void setColor(glm::vec3 color);

};

