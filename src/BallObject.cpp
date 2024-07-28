#include "BallObject.hpp"

BallObject::BallObject():m_radius(10.0f), m_isKinematic(true)
{
	m_currentPosition = glm::vec2(400.0f, 400.0f);
	m_previousPosition = glm::vec2(400.0f, 400.0f);
	m_acceleration = glm::vec2(0.0f, 0.0f);
	m_ballColor = glm::vec3(1.0f, 1.0f, 1.0f);

}
BallObject::BallObject(glm::vec2 position,glm::vec2 prevPosition,glm::vec3 color,float radius,bool isKinematic):m_radius(radius), m_isKinematic(isKinematic)
{
	this->m_currentPosition = position;
	this->m_previousPosition = prevPosition;
	m_acceleration = glm::vec2(0.0f, 0.0f);

	m_ballColor = color;

}

void BallObject::updatePosition(float dt)
{
	
	if (!m_isKinematic)return;

	glm::vec2 velocity = this->m_currentPosition - this->m_previousPosition;
	
	this->m_previousPosition = this->m_currentPosition;

	this->m_currentPosition = this->m_currentPosition + velocity + m_acceleration * (dt * dt);

	m_acceleration = glm::vec2(0.0f, 0.0f);
}

void BallObject::accelerate(glm::vec2 acc)
{
	m_acceleration += acc;;
}

void BallObject::applyConstrains() {
	
	

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

glm::vec2 BallObject::getCurrentPosition()const
{
	return m_currentPosition;
}
void BallObject::setCurrentPosition(glm::vec2 position)
{
	m_currentPosition = position;
}

float BallObject::getRadius() const
{
	return m_radius;
}

glm::vec3 BallObject::getBallColor() const
{
	return m_ballColor;
}
void BallObject::moveByVector(glm::vec2 moveVector)
{
	m_currentPosition += moveVector;
}
bool BallObject::isKinematic()const
{
	return m_isKinematic;
}
