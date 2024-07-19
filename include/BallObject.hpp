#pragma once
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

class BallObject {
private:
	glm::vec3 ballColor;
	glm::vec2 acceleration;
	const float radius = 5.0f;
public:
	glm::vec2 currentPosition;
	glm::vec2 previousPosition;
	BallObject();
	BallObject(glm::vec2 position, glm::vec3 color);
	void updatePosition(float dt);
	void accelerate(glm::vec2 acc);
	float getRadius()const;
	glm::vec3 getBallColor()const;


	glm::vec2 getCurrentPosition()const;
	glm::vec2 getPreviousPosition()const;
	void setCurrentPosition(glm::vec2 pos);
	void setPreviousPosition(glm::vec2 pos);

};