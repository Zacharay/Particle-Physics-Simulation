#include "Application.hpp"
#include <chrono>

Application::Application() :Window(WINDOW_WIDTH, WINDOW_HEIGHT, "Particle Physics Simulation")
{
	
	this->ballRenderer = new BallRenderer();
	this->physicsSolver = new PhysicsSolver(this->objects);
	this->lastTime = glfwGetTime();
}

void Application::onUpdate()
{
	float currentTime = glfwGetTime();

	float deltaTime = currentTime - this->lastTime;

	this->lastTime = currentTime;

	deltaTime = std::min(1.0f / FRAMES_PER_SECOND, deltaTime);
	this->accumulator += deltaTime;

	if (this->accumulator > this->FIXED_SPAWN_RATE)
	{
		this->accumulator -= this->FIXED_SPAWN_RATE;

		this->spawnObject();
	}
	


	this->physicsSolver->applyPhysics(deltaTime);

}

void Application::onRender()
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	for (auto ballObject : this->objects)
	{
		this->ballRenderer->Draw(ballObject->getCurrentPosition(),ballObject->getBallColor(), ballObject->getRadius());
	}

	


}
void Application::spawnObject()
{
	glm::vec2 pos = glm::vec2(100.0f, 700.0f);
	glm::vec3 color = glm::vec3(0.2, 0.3f, 0.8f);

	BallObject* obj = new BallObject(pos, color);
	obj->setPreviousPosition(glm::vec2(96.0f, 701.5f));
	this->objects.push_back(obj);
}



