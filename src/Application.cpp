#include "Application.hpp"
#include <math.h>

static bool isLeftMouseButtonPressed = false;

Application::Application() :Window(SIMULATION_WIDTH, SIMULATION_HEIGHT, "Particle Physics Simulation")
{
	
	this->ballRenderer = new BallRenderer();
	this->physicsSolver = new PhysicsSolver();
	this->textRenderer = new TextRenderer();
	this->lastTime = glfwGetTime();
	ptr_guiManager = std::make_unique<GuiManager>();



	glfwSetMouseButtonCallback(this->window, mouseButtonCallback);
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
		processMouseEvents();
		
	}
	

	this->updatePhysicsSolver();
	this->physicsSolver->applyPhysics(deltaTime);

}

void Application::onRender()
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	this->ballRenderer->DrawBalls(this->physicsSolver->objects);

	std::string objectStr = "Objects: " + std::to_string(this->physicsSolver->objects.size());
	this->textRenderer->DrawText(objectStr,10, SIMULATION_HEIGHT-40);

	unsigned int collsionChecks = this->physicsSolver->getCollisionChecks();
	std::string collisionStr = "Checks:" + std::to_string(collsionChecks);
	this->textRenderer->DrawText(collisionStr, 10, SIMULATION_HEIGHT - 70);
	
	ptr_guiManager->render();
}
void Application::processEvents()
{
	if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
	{
		this->physicsSolver->resetSimulationState();
		this->lastTime = glfwGetTime();
		this->accumulator = 0;
	}
}

void Application::updatePhysicsSolver()
{
	this->physicsSolver->setColor(ptr_guiManager->getBallColor());
	this->physicsSolver->setGravity(ptr_guiManager->getGravity());
	this->physicsSolver->setRadius(ptr_guiManager->getBallRadius());
}

void Application::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			isLeftMouseButtonPressed = true;	
		}
		else if (action == GLFW_RELEASE) {
			isLeftMouseButtonPressed = false;

		}
	}

}
void Application::processMouseEvents()
{


	if (isLeftMouseButtonPressed)
	{
		double xPos, yPos;
		glfwGetCursorPos(this->window, &xPos, &yPos);

		if (xPos > SIMULATION_WIDTH)return;

		this->physicsSolver->spawnObject(xPos,SIMULATION_HEIGHT-yPos);
		
	}
}




