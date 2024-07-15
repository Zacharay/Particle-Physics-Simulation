#pragma once
#include "BallObject.hpp"
#include <vector>

class PhysicsSolver {
	glm::vec2 gravity = glm::vec2(0.0f, -1000.0f);
	std::vector<BallObject*>& gameObjects;
	void applyConstrains();
	void applyGravity();
	void updatePositions(float dt);
public:
	PhysicsSolver(std::vector<BallObject*>& objects);
	void applyPhysics(float dt);

};

