#include "Application.hpp"
#include <chrono>
float accumulator = 0.0f;
const float FIXED_SPAWN_RATE = 0.06f;

void Application::onUpdate()
{
	float currentFrame = glfwGetTime();
	float deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	deltaTime = 1.0f / 144.0f;

	//deltaTime = std::min(deltaTime, 0.005f);

	accumulator += deltaTime;

	if (accumulator > FIXED_SPAWN_RATE)
	{
		accumulator -= FIXED_SPAWN_RATE;
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

	
	glfwSwapBuffers(this->window);
	glfwPollEvents();

}
void Application::spawnObject()
{
	glm::vec2 pos = glm::vec2(100.0f, 700.0f);
	glm::vec3 color = glm::vec3(0.2, 0.3f, 0.8f);

	BallObject* obj = new BallObject(pos, color);
	obj->setPreviousPosition(glm::vec2(97.0f, 701.0f));
	this->objects.push_back(obj);
}
Application::Application()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	this->window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Particle Physics Simulation", NULL, NULL);
	glfwMakeContextCurrent(this->window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		//TODO 
		//Add some assertion right here
	}
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	this->ballRenderer = new BallRenderer();

	this->physicsSolver = new PhysicsSolver(this->objects);
}

void Application::Run()
{
	this->lastFrame = glfwGetTime();

	const double updateInterval = 1.0 / 144.0;  // Update 144 times per second

	auto previousUpdateTime = std::chrono::high_resolution_clock::now();
	double accumulator = 0.0;

	// Variables for FPS calculation
	double fpsPreviousTime = glfwGetTime();
	int frameCount = 0;
	while (!glfwWindowShouldClose(this->window))
	{

		auto currentTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsedTime = currentTime - previousUpdateTime;
		previousUpdateTime = currentTime;
		accumulator += elapsedTime.count();


		// Update loop
		while (accumulator >= updateInterval) {
			// FPS calculation
			frameCount++;
			double fpsCurrentTime = glfwGetTime();
			if (fpsCurrentTime - fpsPreviousTime >= 1.0) {
				// Display the FPS
				std::cout << "FPS: " << frameCount << std::endl;

				// Reset the counters
				frameCount = 0;
				fpsPreviousTime = fpsCurrentTime;
			}



			this->onUpdate();
			accumulator -= updateInterval;
		}

		this->onRender();

	}

}
