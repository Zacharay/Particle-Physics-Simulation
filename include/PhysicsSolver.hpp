#pragma once
#include "BallObject.hpp"
#include <vector>

class PhysicsSolver {
	unsigned int collisionChecks = 0;
	glm::vec2 gravity = glm::vec2(0.0f, -500.0f);
	std::vector<BallObject*>& gameObjects;
	void applyConstrains();
	void applyGravity();
	void updatePositions(float dt);
	void solveCollisions();
	void resolveCollision(BallObject& ballObj1, BallObject& ballObj2);
public:
	PhysicsSolver(std::vector<BallObject*>& objects);
	void applyPhysics(float dt);
	unsigned int getCollisionChecks();
};

