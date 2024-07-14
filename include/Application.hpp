#pragma once
#include "glad/glad.h"
#include "glfw3.h"
#include "BallRenderer.hpp"
#include "Globals.hpp"

#include <iostream>

class Application {
private:

	BallRenderer *ballRenderer;
	GLFWwindow* window;
	void onUpdate();
	void onRender();
public:
	Application();
	void Run();
};