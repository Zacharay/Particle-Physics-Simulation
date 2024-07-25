#pragma once
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

class BallObject {
private:
	glm::vec3 ballColor;
	glm::vec2 acceleration;
	const float radius;
public:
	glm::vec2 currentPosition;
	glm::vec2 previousPosition;
	
	BallObject();
	BallObject(glm::vec2 position, glm::vec2 prevPosition, glm::vec3 color,float radius);
	void updatePosition(float dt);
	void accelerate(glm::vec2 acc);
	float getRadius()const;
	glm::vec3 getBallColor()const;


	

};