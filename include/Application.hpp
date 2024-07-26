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
#include "Globals.hpp"

class Application : 
	public Window{
private:
	glm::vec4 m_ballColor = glm::vec4(1.0f,1.0f,1.0f,1.0f);
	float m_ballRadius = 10;


	BallRenderer *ballRenderer;
	PhysicsSolver *physicsSolver;
	TextRenderer* textRenderer;

	const float FIXED_SPAWN_RATE = 0.03f;
	float accumulator = 0.0f;
	double lastTime;
	
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	void processMouseEvents();

protected:

	void onUpdate() override;
	void onRender()override;
	void processEvents()override;
	void renderGUI()override;
public:
	Application();
};