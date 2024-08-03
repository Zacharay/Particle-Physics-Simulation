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
	ImGui::RadioButton("Color Picker", &m_colorPickerState, ColorPickerState::Standard);
	ImGui::SameLine();
	ImGui::RadioButton("Rainbow Mode", &m_colorPickerState, ColorPickerState::Rainbow);
	if (m_colorPickerState==ColorPickerState::Standard)
	{
		ImGui::Text("Color");
		ImGui::ColorPicker4("Color", (float*)&m_particleColor, colorEditFlags);
		ImGui::Dummy(ImVec2(0.0f, 20.0f));
	}


	ImGui::Text("Radius");
	ImGui::SliderFloat("##radius", &m_ballRadius, 5.0f, 10.0f);
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

	


	ImGui::RadioButton("Spawn", &m_mouseState,MouseState::Spawner);
	ImGui::SameLine();
	ImGui::RadioButton("Attraction" , &m_mouseState, MouseState::Attraction);
	ImGui::SameLine();
	ImGui::RadioButton("Repulsion", &m_mouseState, MouseState::Repulsion);

	ImGui::Dummy(ImVec2(0.0f, 10.0f));

	if (m_mouseState == MouseState::Attraction || m_mouseState == MouseState::Repulsion)
	{
		ImGui::SliderFloat("Force Radius", &m_forceRadius, forceMinRadius, forceMaxRadius);
		ImGui::SliderFloat("Force Strength", &m_forceStrength, forceStrengthMin, forceStrengthMax);


	}
	else if (m_mouseState == MouseState::Spawner)
	{
		ImGui::Text("Spawn Speed");
		ImGui::RadioButton("Slow", &m_spawnSpeed, SpawnSpeed::Slow);
		ImGui::SameLine();
		ImGui::RadioButton("Normal", &m_spawnSpeed, SpawnSpeed::Normal);
		ImGui::SameLine();
		ImGui::RadioButton("Fast", &m_spawnSpeed, SpawnSpeed::Fast);
		
		ImGui::Dummy(ImVec2(0.0f, 5.0f));
		ImGui::Text("Type of object");
		ImGui::RadioButton("Particle", &m_objectType, SpawningObject::ParticleObj);
		ImGui::SameLine();
		ImGui::RadioButton("Cube", &m_objectType, SpawningObject::Cube);
		ImGui::SameLine();
		ImGui::RadioButton("Rope", &m_objectType, SpawningObject::Rope);
		ImGui::SameLine();
		ImGui::RadioButton("Bridge", &m_objectType, SpawningObject::Bridge);

	}

	ImGui::PopFont();
	

	ImGui::PopStyleColor();


	ImGui::End(); 
}

glm::vec3 GuiManager::getParticleColor() const
{
	return glm::vec3(m_particleColor.x, m_particleColor.y, m_particleColor.z);
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
	return m_mouseState;
}
float GuiManager::getForceRadius()const {
	return m_forceRadius;
}
float GuiManager::getForceStrength()const {
	return m_forceStrength;
}
int GuiManager::getColorMode()const {
	return m_colorPickerState;
}
int GuiManager::getSpawnObjectType()const {
	return m_objectType;
}
int GuiManager::getSpawnSpeed()const {
	return m_spawnSpeed;
}