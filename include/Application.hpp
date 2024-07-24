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

	const float FIXED_SPAWN_RATE = 0.02f;
	float accumulator = 0.0f;
	double lastTime;
	unsigned int numOfObjects = 0;

	std::vector<BallObject*> objects;
	void spawnObject();
protected:

	void onUpdate() override;
	void onRender()override;
	
public:
	Application();
};