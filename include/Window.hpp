#pragma once
#include "Globals.hpp"
#include "glad/glad.h"
#include "glfw3.h"
#include <chrono>
#include <iostream>
class Window {
private:
	unsigned int frameCount = 0;

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	GLFWwindow* window;
public:
	Window(unsigned int width,unsigned int height,const char *windowName);
	void mainLoop();

protected:
	virtual void onUpdate() = 0;
	virtual void onRender() = 0;
	unsigned int getCurrentFrames()const;
};
