#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "glm/glm.hpp"
#include "Globals.hpp"

const static float minGravity = 0.0f;
const static float maxGravity = 20.0f;

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

class GuiManager {
private:

	glm::vec4 m_ballColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	float m_ballRadius = 10;
	float m_gravityForce = 10.0f;
	glm::vec2 m_gravityDirection = glm::vec2(0.0f, -1.0f);


public:
	GuiManager() {};
	void render();
	void update();

	glm::vec3 getBallColor()const;
	float getBallRadius()const;
	glm::vec2 getGravity()const;

};