#include "Application.hpp"
#include <math.h>

glm::vec3 hsvToRgb(float h, float s, float v) {
	float r, g, b;
	int i = int(h * 6);
	float f = h * 6 - i;
	float p = v * (1 - s);
	float q = v * (1 - f * s);
	float t = v * (1 - (1 - f) * s);

	switch (i % 6) {
	case 0: r = v, g = t, b = p; break;
	case 1: r = q, g = v, b = p; break;
	case 2: r = p, g = v, b = t; break;
	case 3: r = p, g = q, b = v; break;
	case 4: r = t, g = p, b = v; break;
	case 5: r = v, g = p, b = q; break;
	}
	return glm::vec3(r, g, b);
}



static bool isLeftMouseButtonPressed = false;
static bool spawnStaticParticle = false;
glm::vec2 startingPos;

Application::Application() :Window(SIMULATION_WIDTH, SIMULATION_HEIGHT, "Particle Physics Simulation")
{
	
	ptr_ballRenderer = std::make_unique<ParticleRenderer>();
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
	
	float spawnDelay = static_cast<float>(ptr_guiManager->getSpawnSpeed()) / 100.0f;

	if (m_accumulator > spawnDelay && ptr_physicsSolver->m_particles.size() <= MAX_OBJECTS)
	{
		m_accumulator -= spawnDelay;
		processMouseEvents();
		
	}
	updatePhysicsSolver();
	ptr_physicsSolver->applyPhysics(deltaTime);

}

void Application::onRender()
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	ptr_ballRenderer->DrawParticles(ptr_physicsSolver->m_particles);
	ptr_ballRenderer->DrawParticles(temporaryParticles);


	const std::string objectStr = "Objects: " + std::to_string(this->ptr_physicsSolver->m_particles.size());
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
			spawnStaticParticle = true;
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
		if (isLeftMouseButtonPressed && ptr_guiManager->getSpawnObjectType() == SpawningObject::ParticleObj)
		{
			double xPos, yPos;
			glfwGetCursorPos(this->window, &xPos, &yPos);

			if (xPos > SIMULATION_WIDTH)return;

			glm::vec3 color = this->ptr_guiManager->getParticleColor();
			if (this->ptr_guiManager->getColorMode() == ColorPickerState::Rainbow)
			{
				float t = float(this->ptr_physicsSolver->m_particles.size() % 360) / 360.0f;
				color = hsvToRgb(t, 1.0f, 1.0f);
			}

			this->ptr_physicsSolver->spawnParticle(xPos, SIMULATION_HEIGHT - yPos, color);
		}
		else if (isLeftMouseButtonPressed && ptr_guiManager->getSpawnObjectType() == SpawningObject::Cube)
		{
			double xPos, yPos;
			glfwGetCursorPos(this->window, &xPos, &yPos);

			glm::vec3 color = this->ptr_guiManager->getParticleColor();

			if (xPos > SIMULATION_WIDTH)return;

			this->ptr_physicsSolver->spawnCube(xPos, SIMULATION_HEIGHT - yPos, color);

			//disable constant spawning on mouse hold
			isLeftMouseButtonPressed = false;
		}
		else if (ptr_guiManager->getSpawnObjectType() == SpawningObject::Rope || ptr_guiManager->getSpawnObjectType() == SpawningObject::Bridge)
		{
			if(isLeftMouseButtonPressed)
			{
				double xPos, yPos;
				glfwGetCursorPos(this->window, &xPos, &yPos);

				glm::vec3 color = this->ptr_guiManager->getParticleColor();

				if (xPos > SIMULATION_WIDTH)return;

				if (spawnStaticParticle == true)
				{
					startingPos = glm::vec2(xPos, SIMULATION_HEIGHT - yPos);
					spawnStaticParticle = false;
					
				}

				temporaryParticles.clear();

				glm::vec2 currentMousePos = glm::vec2(xPos, SIMULATION_HEIGHT - yPos);

				glm::vec2 currentAxis = currentMousePos - startingPos;

				float axisLength = glm::length(currentAxis);
				float diameter = 10.0f * 2.0f;

				unsigned int numOfParticles = axisLength / diameter;


				glm::vec2 normalizedAxis = glm::normalize(currentAxis);

				glm::vec2 currentParticlePos = startingPos;
				temporaryParticles.emplace_back(std::make_shared<Particle>(currentParticlePos, currentParticlePos, glm::vec3(1.0f, 0.0f,0.0f), 10.0f, false));


				for (int i = 1; i <= numOfParticles; i++)
				{
					currentParticlePos += normalizedAxis * diameter;

					if (i == numOfParticles)
					{
						if (ptr_guiManager->getSpawnObjectType() == SpawningObject::Bridge)
						{
							temporaryParticles.emplace_back(std::make_shared<Particle>(currentParticlePos, currentParticlePos, glm::vec3(1.0f, 0.0f, 0.0f), 10.0f, false));
						}
						else {
							temporaryParticles.emplace_back(std::make_shared<Particle>(currentParticlePos, currentParticlePos, glm::vec3(0.0f, 0.0f, 0.0f), 10.0f, true));
						}
						break;
					}

					temporaryParticles.emplace_back(std::make_shared<Particle>(currentParticlePos, currentParticlePos, glm::vec3(0.0f, 0.0f, 0.0f), 10.0f, true));

				}
			}
			else {
				if (temporaryParticles.size() > 0)
				{
					ptr_physicsSolver->spawnLinkedParticles(temporaryParticles);
				}
				temporaryParticles.clear();
			}
			
			

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




