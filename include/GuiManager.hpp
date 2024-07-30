#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "glm/glm.hpp"
#include "Globals.hpp"

const static float minGravity = 0.0f;
const static float maxGravity = 20.0f;

const static float forceMinRadius = 100.0f;
const static float forceMaxRadius = SIMULATION_WIDTH / 2;

const static float forceStrengthMin = 5.0f;
const static float forceStrengthMax = 20.0f;

// colorPicker flags
static ImGuiColorEditFlags colorEditFlags =
ImGuiColorEditFlags_NoSmallPreview |
ImGuiColorEditFlags_NoTooltip |
ImGuiColorEditFlags_NoLabel |
ImGuiColorEditFlags_NoSidePreview |
ImGuiColorEditFlags_NoInputs |
ImGuiColorEditFlags_NoAlpha |
ImGuiColorEditFlags_PickerHueBar;

enum GravityDirection {
	BOTTOM ,
	LEFT,
	TOP,
	RIGHT
};
enum MouseState {
	Spawner = 0,
	Attraction = 1,
	Repulsion = -1
};
enum ColorPickerState {
	Standard,
	Rainbow
};

class GuiManager {
private:

	glm::vec4 m_ballColor = glm::vec4(0.0f, 0.2f,1.0f, 1.0f);
	float m_ballRadius = 10;
	float m_gravityForce = 5.0f;

	float m_forceRadius = 400.0f;
	float m_forceStrength = 20.0f;

	glm::vec2 m_gravityDirection = glm::vec2(0.0f, -1.0f);

	int m_colorPickerState = ColorPickerState::Rainbow;
	int m_mouseState = MouseState::Spawner;

public:
	GuiManager() {};
	void render();
	void update();

	glm::vec3 getBallColor()const;
	float getBallRadius()const;
	glm::vec2 getGravity()const;
	int getMouseState()const;
	float getForceRadius()const;
	float getForceStrength()const;
	int getColorMode()const;
};