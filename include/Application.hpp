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
#include <memory>
#include "GuiManager.hpp"



class Application : 
	public Window{
private:


	BallRenderer *ballRenderer;
	PhysicsSolver *physicsSolver;
	TextRenderer* textRenderer;
	std::unique_ptr<GuiManager> ptr_guiManager;

	const float FIXED_SPAWN_RATE = 0.05f;
	float accumulator = 0.0f;
	double lastTime;
	
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	void processMouseEvents();
	void updatePhysicsSolver();
protected:

	void onUpdate() override;
	void onRender()override;
	void processEvents()override;

public:
	Application();
};