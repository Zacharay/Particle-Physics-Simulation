#pragma once
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

class BallObject {
private:
	
	glm::vec2 acceleration;
	const float radius = 20.0f;
public:
	glm::vec2 currentPosition;
	glm::vec2 previousPosition;
	BallObject();
	BallObject(glm::vec2 position);
	void updatePosition(float dt);
	void accelerate(glm::vec2 acc);
	glm::vec2 getCurrentPosition()const;
	glm::vec2 getPreviousPosition()const;
	float getRadius()const;
	void setCurrentPosition(glm::vec2 pos);
	void setPreviousPosition(glm::vec2 pos);

};