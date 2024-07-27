#pragma once
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "Globals.hpp"
class BallObject {
private:
	glm::vec3 m_ballColor;
	glm::vec2 m_acceleration;
	const float m_radius;

	glm::vec2 m_currentPosition;
	glm::vec2 m_previousPosition;
public:
	
	
	
	BallObject();
	BallObject(glm::vec2 position, glm::vec2 prevPosition, glm::vec3 color,float radius);
	void updatePosition(float dt);
	void accelerate(glm::vec2 acc);
	void applyConstrains();


	float getRadius()const;
	glm::vec3 getBallColor()const;
	glm::vec2 getCurrentPosition()const;
	void setCurrentPosition(glm::vec2 position);
	

};