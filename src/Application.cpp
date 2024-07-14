#include "Application.hpp"

void Application::onUpdate()
{
	//process user input
}

void Application::onRender()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	this->ballRenderer->Draw(glm::vec2(0.0f,0.0f),20.0f);

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
}

void Application::Run()
{

	while (!glfwWindowShouldClose(this->window))
	{
		this->onUpdate();
		this->onRender();
	}

}
