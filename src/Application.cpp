#include "Application.hpp"

void Application::onUpdate()
{
	float currentFrame = glfwGetTime();
	float dt = currentFrame - this->lastFrame;

	this->lastFrame = currentFrame;

	this->physicsSolver->applyPhysics(dt);

}

void Application::onRender()
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	for (auto ballObject : this->objects)
	{
		
		this->ballRenderer->Draw(ballObject->getCurrentPosition(), ballObject->getRadius());
		
	}

	

	glfwSwapBuffers(this->window);
	glfwPollEvents();
}

Application::Application()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	this->window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Particle Physics Simulatio", NULL, NULL);
	glfwMakeContextCurrent(this->window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		//TODO 
		//Add some assertion right here
	}
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	this->ballRenderer = new BallRenderer();

	for (int i = 0; i < 10; i++)
	{
		
		BallObject* obj = new BallObject(glm::vec2(20.0f+i*60,700));
		this->objects.push_back(obj);
	}

	this->physicsSolver = new PhysicsSolver(this->objects);
}

void Application::Run()
{
	this->lastFrame = glfwGetTime();

	while (!glfwWindowShouldClose(this->window))
	{
		this->onUpdate();
		this->onRender();
	}

}
