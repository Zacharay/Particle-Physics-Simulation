#include "GuiManager.hpp"
#include <string>


void GuiManager::render()
{
	ImGuiIO& io = ImGui::GetIO();
	ImVec4 windowBgColor = ImVec4(0, 0, 0, 1.00f);

	ImFont* robotoFontBold = io.Fonts->Fonts[0];
	ImFont* robotoFontRegular = io.Fonts->Fonts[1];


	ImGui::SetNextWindowPos(ImVec2(SIMULATION_WIDTH, 0), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2(GUI_WIDTH, SIMULATION_HEIGHT), ImGuiCond_Once);

	ImGui::PushStyleColor(ImGuiCol_WindowBg, windowBgColor);
	ImGui::Begin("Fixed Position Window", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);
	ImGui::PopStyleColor();

	ImGui::PushFont(robotoFontBold);
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 0.0f, 1.0f));
	ImGui::Text("FPS: 60");
	ImGui::PopStyleColor();


	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
	ImGui::Text("New Object Properties");
	ImGui::PopFont();




	ImGui::PushFont(robotoFontRegular);
	ImGui::Text("Color");
	ImGui::ColorPicker4("Color", (float*)&m_ballColor, colorEditFlags);
	ImGui::Dummy(ImVec2(0.0f, 20.0f));

	ImGui::Text("Radius");
	ImGui::SliderFloat("##radius", &m_ballRadius, 10.0f, 20.0f);
	ImGui::PopFont();

	ImGui::Dummy(ImVec2(0.0f, 10.0f));

	ImGui::PushFont(robotoFontBold);
	ImGui::Text("Gravity");
	ImGui::PopFont();

	ImGui::PushFont(robotoFontRegular);
	ImGui::SliderFloat("Gravity Force", &m_gravityForce, minGravity
		, maxGravity);
	ImGui::SliderFloat("X-axis gravity", &m_gravityDirection.x, -1.0f
		, 1.0f);
	ImGui::SliderFloat("Y-axis gravity", &m_gravityDirection.y, -1.0f
		, 1.0f);
	ImGui::PopFont();

	ImGui::Dummy(ImVec2(0.0f, 10.0f));

	

	ImGui::PushFont(robotoFontBold);
	ImGui::Text("Mouse Behaviour");
	ImGui::PopFont();

	ImGui::PushFont(robotoFontRegular);

	ImGui::RadioButton("Spawner", &m_state,MouseState::Spawner);
	ImGui::SameLine();
	ImGui::RadioButton("Attraction" , &m_state, MouseState::Attraction);
	ImGui::SameLine();
	ImGui::RadioButton("Repulsion", &m_state, MouseState::Repulsion);

	if (m_state == MouseState::Attraction || m_state== MouseState::Repulsion)
	{
		ImGui::SliderFloat("Force Radius", &m_forceRadius, forceMinRadius, forceMaxRadius);
		ImGui::SliderFloat("Force Strength", &m_forceStrength, forceStrengthMin, forceStrengthMax);


	}

	ImGui::PopFont();
	

	ImGui::PopStyleColor();


	ImGui::End(); 
}

glm::vec3 GuiManager::getBallColor() const
{
	return glm::vec3(m_ballColor.x, m_ballColor.y, m_ballColor.z);
}

float GuiManager::getBallRadius() const
{
	return m_ballRadius;
}

glm::vec2 GuiManager::getGravity() const
{
	return m_gravityDirection * m_gravityForce * 100.0f;
}
int GuiManager::getMouseState()const {
	return m_state;
}
float GuiManager::getForceRadius()const {
	return m_forceRadius;
}
float GuiManager::getForceStrength()const {
	return m_forceStrength;
}