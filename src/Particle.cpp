#include "Particle.hpp"

Particle::Particle()
	:	
	m_particleColor(1.0f, 1.0f, 1.0f), 
	m_acceleration(0.0f, 0.0f),
	m_radius(10.0f), 
	m_isKinematic(true),
	m_currentPosition(400.0f,400.0f),
	m_previousPosition(400.0f,400.0f){}

Particle::Particle(glm::vec2 position,glm::vec2 prevPosition,glm::vec3 color,float radius,bool isKinematic)
	:
	m_particleColor(color),
	m_acceleration(0.0f, 0.0f),
	m_radius(radius),
	m_isKinematic(isKinematic),
	m_currentPosition(position),
	m_previousPosition(prevPosition) {}


void Particle::updatePosition(float dt)
{
	
	if (!m_isKinematic)return;

	glm::vec2 velocity = this->m_currentPosition - this->m_previousPosition;
	
	this->m_previousPosition = this->m_currentPosition;

	this->m_currentPosition = this->m_currentPosition + velocity + m_acceleration * (dt * dt);

	m_acceleration = glm::vec2(0.0f, 0.0f);
}

void Particle::accelerate(glm::vec2 acc)
{
	m_acceleration += acc;;
}

void Particle::applyConstrains() {
	
	

	glm::vec2 velocity = m_currentPosition - m_previousPosition;

	if (m_currentPosition.x < m_radius)
	{
		m_currentPosition = glm::vec2(m_radius, m_currentPosition.y);
		m_previousPosition = glm::vec2(m_previousPosition.x + velocity.x, m_previousPosition.y);
	}
	else if (m_currentPosition.x > SIMULATION_WIDTH - m_radius)
	{
		m_currentPosition = glm::vec2(SIMULATION_WIDTH - m_radius, m_currentPosition.y);
		m_previousPosition = glm::vec2(m_previousPosition.x + velocity.x, m_previousPosition.y);
	}

	velocity = m_currentPosition - m_previousPosition;
	if (m_currentPosition.y < m_radius)
	{
		m_currentPosition = glm::vec2(m_currentPosition.x, m_radius);
		m_previousPosition = glm::vec2(m_previousPosition.x, m_previousPosition.y + velocity.y);
	}
	else if (m_currentPosition.y > SIMULATION_HEIGHT - m_radius)
	{
		m_currentPosition = glm::vec2(m_currentPosition.x, SIMULATION_HEIGHT - m_radius);
		m_previousPosition = glm::vec2(m_previousPosition.x, m_previousPosition.y + velocity.y);
	}
}

glm::vec2 Particle::getCurrentPosition()const
{
	return m_currentPosition;
}
void Particle::setCurrentPosition(glm::vec2 position)
{
	if (!m_isKinematic)return;

	m_currentPosition = position;
}

float Particle::getRadius() const
{
	return m_radius;
}

glm::vec3 Particle::getParticleColor() const
{
	return m_particleColor;
}
void Particle::moveByVector(glm::vec2 moveVector)
{
	if (!m_isKinematic)return;
	
	m_currentPosition += moveVector;
}

