#include "Application.hpp"
#include <math.h>

Application::Application() :Window(WINDOW_WIDTH, WINDOW_HEIGHT, "Particle Physics Simulation")
{
	
	this->ballRenderer = new BallRenderer();
	this->physicsSolver = new PhysicsSolver(this->objects);
	this->textRenderer = new TextRenderer();
	this->lastTime = glfwGetTime();
}

void Application::onUpdate()
{
	float currentTime = glfwGetTime();

	float deltaTime = currentTime - this->lastTime;

	this->lastTime = currentTime;

	deltaTime = std::min(1.0f / FRAMES_PER_SECOND, deltaTime);
	this->accumulator += deltaTime;

	if (this->accumulator > this->FIXED_SPAWN_RATE && this->numOfObjects < MAX_OBJECTS)
	{
		this->accumulator -= this->FIXED_SPAWN_RATE;
		this->numOfObjects++;
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

	std::string objectStr = "Objects: " + std::to_string(this->numOfObjects);
	this->textRenderer->DrawText(objectStr,600, 760);

	unsigned int collsionChecks = this->physicsSolver->getCollisionChecks();
	std::string collisionStr = "Checks:" + std::to_string(collsionChecks);
	this->textRenderer->DrawText(collisionStr, 600, 730);


}
void Application::spawnObject()
{
	std::random_device rd;
	unsigned int seed = rd();
	std::default_random_engine engine(seed);
	std::uniform_int_distribution<int> numberDistribution(1, 3);
	glm::vec3 color;
	if (numOfObjects % 2 == 0)
		color = glm::vec3(0, 0, 1);
	else if (numOfObjects % 3 == 0)
		color = glm::vec3(0, 1, 0);
	else
		color = glm::vec3(1, 0, 0);


	const float radius = 5.0f;
	float initalXPos = 6 * radius;
	float initalYPos = WINDOW_HEIGHT - 6 * radius;

	glm::vec2 spawnerPos = glm::vec2(initalXPos, initalYPos);

	float initalXOffset = -4.0f;
	float initalYOffset = 1.5f;

	BallObject* obj = new BallObject(spawnerPos, color, radius);
	obj->setPreviousPosition(glm::vec2(initalXPos + initalXOffset, initalYPos + initalYOffset));
	this->objects.push_back(obj);
}



