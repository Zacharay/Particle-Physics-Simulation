#pragma once
#include "BallObject.hpp"
#include <vector>
#include "Globals.hpp"
#include "UniformGrid.hpp"
#include <memory>


class PhysicsSolver{
	const float c_gridCellSize = 40.0f;
	
	unsigned int m_substeps = 4;

	glm::vec2 m_gravity = glm::vec2(0.0f, -2000.0f);
	glm::vec3 m_ballColor = glm::vec3(0.0f,0.0f,0.0f);
	float m_ballRadius = 10.0f;


	std::unique_ptr<UniformGrid> ptr_grid;


	unsigned int collisionChecks = 0;
	
	void applyConstrains();
	void applyGravity();
	void updatePositions(float dt);
	void solveCollisions();
	void resolveCollision(BallObject& ballObj1, BallObject& ballObj2);
	
public:
	
	void spawnObject(float xPos, float yPos);
	std::vector<std::unique_ptr<BallObject>>objects;
	PhysicsSolver();
	void applyPhysics(float dt);
	unsigned int getCollisionChecks();
	void resetSimulationState();

	void setGravity(glm::vec2 gravity);
	void setRadius(float radius);
	void setColor(glm::vec3 color);

};

