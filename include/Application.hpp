#pragma once
#include "glad/glad.h"
#include "glfw3.h"
#include "BallRenderer.hpp"
#include "Globals.hpp"
#include "BallObject.hpp"
#include "PhysicsSolver.hpp"
#include "Window.hpp"
#include <iostream>


class Application : public Window{
private:
	BallRenderer *ballRenderer;
	PhysicsSolver *physicsSolver;


	const float FIXED_SPAWN_RATE = 0.05f;
	float accumulator = 0.0f;
	float lastTime;

	std::vector<BallObject*> objects;
	void spawnObject();
protected:

	void onUpdate() override;
	void onRender()override;
	
public:
	Application();
};