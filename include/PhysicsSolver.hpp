#pragma once
#include "BallObject.hpp"
#include <vector>
#include "Globals.hpp"
#include "UniformGrid.hpp"
class PhysicsSolver {
	UniformGrid* grid;
	

	unsigned int collisionChecks = 0;
	glm::vec2 gravity = glm::vec2(0.0f, -500.0f);
	void applyConstrains();
	void applyGravity();
	void updatePositions(float dt);
	void solveCollisions();
	void resolveCollision(BallObject& ballObj1, BallObject& ballObj2);
	
public:
	void spawnObject();
	std::vector<BallObject*>objects;
	PhysicsSolver();
	void applyPhysics(float dt);
	unsigned int getCollisionChecks();
};

