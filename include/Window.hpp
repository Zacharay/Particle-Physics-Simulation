#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"


#include "Globals.hpp"
#include "glad/glad.h"
#include "glfw3.h"
#include <chrono>
#include <iostream>
class Window {
private:
	unsigned int frameCount = 0;

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

public:
	Window(unsigned int width,unsigned int height,const char *windowName);
	void mainLoop();

protected:
	GLFWwindow* window;
	virtual void onUpdate() = 0;
	virtual void onRender() = 0;
	virtual void processEvents() = 0;
	
	
	unsigned int getCurrentFrames()const;
};
