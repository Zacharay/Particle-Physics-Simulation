#include "Application.hpp"
#include <math.h>

static bool isLeftMouseButtonPressed = false;

Application::Application() :Window(SIMULATION_WIDTH, SIMULATION_HEIGHT, "Particle Physics Simulation")
{
	
	this->ballRenderer = new BallRenderer();
	this->physicsSolver = new PhysicsSolver();
	this->textRenderer = new TextRenderer();
	this->lastTime = glfwGetTime();

	glfwSetMouseButtonCallback(this->window, mouseButtonCallback);
}

void Application::onUpdate()
{

	


	double currentTime = glfwGetTime();

	double deltaTime = currentTime - this->lastTime;

	this->lastTime = currentTime;

	deltaTime = std::min(static_cast<double>(1.0f / FRAMES_PER_SECOND), deltaTime);
	this->accumulator += deltaTime;
	
	if (this->accumulator > this->FIXED_SPAWN_RATE && this->physicsSolver->objects.size()<=MAX_OBJECTS)
	{
		this->accumulator -= this->FIXED_SPAWN_RATE;
		processMouseEvents();
		
	}
	

	
	this->physicsSolver->applyPhysics(deltaTime);

}

void Application::onRender()
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	this->ballRenderer->DrawBalls(this->physicsSolver->objects);

	std::string objectStr = "Objects: " + std::to_string(this->physicsSolver->objects.size());
	this->textRenderer->DrawText(objectStr,10, SIMULATION_HEIGHT-40);

	unsigned int collsionChecks = this->physicsSolver->getCollisionChecks();
	std::string collisionStr = "Checks:" + std::to_string(collsionChecks);
	this->textRenderer->DrawText(collisionStr, 10, SIMULATION_HEIGHT - 70);
	

}
void Application::processEvents()
{
	if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
	{
		this->physicsSolver->resetSimulationState();
		this->lastTime = glfwGetTime();
		this->accumulator = 0;
	}
}

void Application::renderGUI()
{
	ImGuiIO& io = ImGui::GetIO();
	// Set the desired window background color
	ImVec4 windowBgColor = ImVec4(0, 0, 0, 1.00f); 

	ImFont* robotoFontBold = io.Fonts->Fonts[0]; 
	ImFont* robotoFontRegular = io.Fonts->Fonts[1]; 
	

	ImGui::SetNextWindowPos(ImVec2(SIMULATION_WIDTH, 0), ImGuiCond_Once); 
	ImGui::SetNextWindowSize(ImVec2(GUI_WIDTH, SIMULATION_HEIGHT), ImGuiCond_Once); 

	ImGui::PushStyleColor(ImGuiCol_WindowBg, windowBgColor);
	ImGui::Begin("Fixed Position Window", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);

	ImGui::PushFont(robotoFontBold);
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f,1.0f,0.0f,1.0f));
	ImGui::Text("FPS: 144");
	ImGui::PopStyleColor();


	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
	ImGui::Text("New Object Properties");
	ImGui::PopFont();

	// squared box
	ImGuiColorEditFlags colorEditFlags =
		ImGuiColorEditFlags_NoSmallPreview |
		ImGuiColorEditFlags_NoTooltip |
		ImGuiColorEditFlags_NoLabel |
		ImGuiColorEditFlags_NoSidePreview |
		ImGuiColorEditFlags_NoInputs |
		ImGuiColorEditFlags_NoAlpha |
		ImGuiColorEditFlags_PickerHueBar;


	ImGui::PushFont(robotoFontRegular);
	ImGui::Text("Color");
	ImGui::ColorPicker4("Color",(float*)&m_ballColor,colorEditFlags);
	ImGui::Dummy(ImVec2(0.0f, 20.0f));

	ImGui::Text("Radius");
	ImGui::SliderFloat("", &m_ballRadius, 5.0f, 10.0f);

	ImGui::PopStyleColor();
	ImGui::PopFont();

	ImGui::End();
}

void Application::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			isLeftMouseButtonPressed = true;	
		}
		else if (action == GLFW_RELEASE) {
			isLeftMouseButtonPressed = false;

		}
	}

}
void Application::processMouseEvents()
{


	if (isLeftMouseButtonPressed)
	{
		double xPos, yPos;
		glfwGetCursorPos(this->window, &xPos, &yPos);

		if (xPos > SIMULATION_WIDTH)return;

		this->physicsSolver->spawnObject(xPos,SIMULATION_HEIGHT-yPos,m_ballColor,m_ballRadius);
		
	}
}




