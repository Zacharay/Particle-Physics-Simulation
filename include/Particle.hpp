#pragma once
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "Globals.hpp"
class Particle {
private:
	glm::vec3 m_particleColor;
	glm::vec2 m_acceleration;
	const float m_radius;

	const bool m_isKinematic;

	glm::vec2 m_currentPosition;
	glm::vec2 m_previousPosition;
public:
	
	Particle();
	Particle(glm::vec2 position, glm::vec2 prevPosition, glm::vec3 color,float radius,bool isKinematic = true);
	void updatePosition(float dt);
	void accelerate(glm::vec2 acc);
	void applyConstrains();


	float getRadius()const;
	glm::vec3 getParticleColor()const;
	glm::vec2 getCurrentPosition()const;
	void moveByVector(glm::vec2 moveVector);

	void setCurrentPosition(glm::vec2 position);

};