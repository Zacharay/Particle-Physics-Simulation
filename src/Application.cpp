#include "Application.hpp"
#include <math.h>

Application::Application() :Window(WINDOW_WIDTH, WINDOW_HEIGHT, "Particle Physics Simulation")
{
	
	this->ballRenderer = new BallRenderer();
	this->physicsSolver = new PhysicsSolver();
	this->textRenderer = new TextRenderer();
	this->lastTime = glfwGetTime();
}

void Application::onUpdate()
{
	double currentTime = glfwGetTime();

	double deltaTime = currentTime - this->lastTime;

	this->lastTime = currentTime;

	deltaTime = std::min(static_cast<double>(1.0f / FRAMES_PER_SECOND), deltaTime);
	this->accumulator += deltaTime;
	
	if (this->accumulator > this->FIXED_SPAWN_RATE && this->physicsSolver->objects.size()<=MAX_OBJECTS)
	{
		this->accumulator -= this->FIXED_SPAWN_RATE;
		this->physicsSolver->spawnObject();
	}
	

	
	this->physicsSolver->applyPhysics(deltaTime);

}

void Application::onRender()
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	for (BallObject *ballObject : this->physicsSolver->objects)
	{

		this->ballRenderer->Draw(ballObject);
	}

	std::string objectStr = "Objects: " + std::to_string(this->physicsSolver->objects.size());
	this->textRenderer->DrawText(objectStr,600, 760);

	unsigned int collsionChecks = this->physicsSolver->getCollisionChecks();
	std::string collisionStr = "Checks:" + std::to_string(collsionChecks);
	this->textRenderer->DrawText(collisionStr, 600, 730);


}




