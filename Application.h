#pragma once
#include "glad/glad.h"
#include "glfw3.h"


class Application {
private:
	GLFWwindow* window;
	void onUpdate();
	void onRender();
public:
	Application();
	void Run();
};