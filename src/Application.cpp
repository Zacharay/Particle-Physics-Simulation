#include "Application.hpp"
#include <math.h>

static bool isLeftMouseButtonPressed = false;

Application::Application() :Window(SIMULATION_WIDTH, SIMULATION_HEIGHT, "Particle Physics Simulation")
{
	
	ptr_ballRenderer = std::make_unique<BallRenderer>();
	ptr_physicsSolver = std::make_unique<PhysicsSolver>();
	ptr_textRenderer = std::make_unique<TextRenderer>();
	ptr_guiManager = std::make_unique<GuiManager>();
	
	m_lastTime = glfwGetTime();
	glfwSetMouseButtonCallback(this->window, mouseButtonCallback);

}

void Application::onUpdate()
{

	float currentTime = glfwGetTime();

	float deltaTime = currentTime - m_lastTime;

	m_lastTime = currentTime;

	deltaTime = std::min(1.0f / FRAMES_PER_SECOND, deltaTime);
	m_accumulator += deltaTime;
	
	if (m_accumulator > c_fixedSpawnRate && ptr_physicsSolver->objects.size()<=MAX_OBJECTS)
	{
		m_accumulator -= c_fixedSpawnRate;
		processMouseEvents();
		
	}
	

	updatePhysicsSolver();
	ptr_physicsSolver->applyPhysics(deltaTime);

}

void Application::onRender()
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	ptr_ballRenderer->DrawBalls(ptr_physicsSolver->objects);

	const std::string objectStr = "Objects: " + std::to_string(this->ptr_physicsSolver->objects.size());
	ptr_textRenderer->DrawText(objectStr,10, SIMULATION_HEIGHT-40);

	unsigned int collsionChecks = ptr_physicsSolver->getCollisionChecks();
	const std::string collisionStr = "Checks:" + std::to_string(collsionChecks);
	ptr_textRenderer->DrawText(collisionStr, 10, SIMULATION_HEIGHT - 70);
	
	ptr_guiManager->render();
}
void Application::processEvents()
{
	if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
	{
		ptr_physicsSolver->resetSimulationState();
		m_lastTime = glfwGetTime();
		m_accumulator = 0;
	}
}

void Application::updatePhysicsSolver()
{
	ptr_physicsSolver->setColor(ptr_guiManager->getBallColor());
	ptr_physicsSolver->setGravity(ptr_guiManager->getGravity());
	ptr_physicsSolver->setRadius(ptr_guiManager->getBallRadius());
	ptr_physicsSolver->setForceMode(ptr_guiManager->getMouseState());
	ptr_physicsSolver->setForceStrength(ptr_guiManager->getForceStrength());
	ptr_physicsSolver->setForceRadius(ptr_guiManager->getForceRadius());

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

	if (ptr_guiManager->getMouseState() == MouseState::Spawner)
	{
		if (isLeftMouseButtonPressed)
		{
			double xPos, yPos;
			glfwGetCursorPos(this->window, &xPos, &yPos);

			if (xPos > SIMULATION_WIDTH)return;

			this->ptr_physicsSolver->spawnObject(xPos, SIMULATION_HEIGHT - yPos);
		}
	}
	else if (ptr_guiManager->getMouseState() == MouseState::Attraction || ptr_guiManager->getMouseState() == MouseState::Repulsion)
	{
		if (isLeftMouseButtonPressed)
		{
			double xPos, yPos;
			glfwGetCursorPos(this->window, &xPos, &yPos);

			this->ptr_physicsSolver->setAttraction(true, glm::vec2(xPos, SIMULATION_HEIGHT - yPos));
		}
		else {
			this->ptr_physicsSolver->setAttraction(false, glm::vec2(0.0f, 0.0f));
		}
	}
	
}




