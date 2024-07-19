#pragma once
#include "glad/glad.h"
#include "glfw3.h"
#include "BallRenderer.hpp"
#include "Globals.hpp"
#include "BallObject.hpp"
#include "PhysicsSolver.hpp"

#include <iostream>


class Application {
private:
	float lastFrame;
	BallRenderer *ballRenderer;
	PhysicsSolver *physicsSolver;

	GLFWwindow* window;

	std::vector<BallObject*> objects;

	void onUpdate();
	void onRender();
	void spawnObject();
public:
	Application();
	void Run();
};