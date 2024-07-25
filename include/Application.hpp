#pragma once
#include "BallRenderer.hpp"
#include "Globals.hpp"
#include "BallObject.hpp"
#include "PhysicsSolver.hpp"
#include "Window.hpp"
#include <iostream>
#include <chrono>
#include <random>
#include "TextRenderer.hpp"


class Application : 
	public Window{
private:
	BallRenderer *ballRenderer;
	PhysicsSolver *physicsSolver;
	TextRenderer* textRenderer;

	const float FIXED_SPAWN_RATE = 0.00f;
	float accumulator = 0.0f;
	double lastTime;
	
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	void processMouseEvents();

protected:

	void onUpdate() override;
	void onRender()override;
	void processEvents()override;
	
public:
	Application();
};