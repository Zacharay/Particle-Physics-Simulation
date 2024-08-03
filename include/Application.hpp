#pragma once
#include "ParticleRenderer.hpp"
#include "Globals.hpp"
#include "Particle.hpp"
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

	std::unique_ptr<ParticleRenderer> ptr_ballRenderer;
	std::unique_ptr<PhysicsSolver> ptr_physicsSolver;
	std::unique_ptr<TextRenderer> ptr_textRenderer;
	std::unique_ptr<GuiManager> ptr_guiManager;

	std::vector<std::shared_ptr<Particle>>temporaryParticles;

	const float c_fixedSpawnRate = 0.00f;
	float m_accumulator = 0.0f;
	double m_lastTime;
	
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