#include "BallRenderer.hpp"
#include "glad/glad.h"
#include <iostream>
#include "Globals.hpp"

BallRenderer::BallRenderer()
{

	this->InitializeVertices();
	
	glGenVertexArrays(1, &this->VAO);

	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->IBO);
	
	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(float), this->vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), this->indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glfwSwapInterval(1);
	shader = new Shader("res/shaders/ballVertexShader.vs", "res/shaders/ballFragmentShader.fs");
	
}
BallRenderer::~BallRenderer()
{
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
}
void BallRenderer::DrawBalls(const std::vector<std::unique_ptr<BallObject>>& objects)const
{
	
	
	const size_t objectCount = objects.size();

	std::vector<glm::mat4> modelMatrices(objectCount);
	std::vector<glm::vec3> colors(objectCount);

	for (int i = 0; i < objectCount; i++)
	{
		const BallObject& obj = *objects[i];

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(obj.currentPosition, 0.0f));
		model = glm::scale(model, glm::vec3(obj.getRadius()));
		modelMatrices[i] = model;

		colors[i] = obj.getBallColor();

	}

	glBindVertexArray(this->VAO);
	unsigned int colorBuffer;
	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, objectCount * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	glVertexAttribDivisor(1, 1);

	
	unsigned int instanceBuffer;
	glGenBuffers(1, &instanceBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, instanceBuffer);
	glBufferData(GL_ARRAY_BUFFER, objectCount * sizeof(glm::mat4), modelMatrices.data(), GL_STATIC_DRAW);


	
	std::size_t vec4Size = sizeof(glm::vec4);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(1*vec4Size));

	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));

	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));

	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
	
	glm::mat4 projection = glm::ortho(0.0f, (float)SIMULATION_WIDTH, 0.0f, (float)SIMULATION_HEIGHT);

	shader->useProgram();
	shader->setMat4(projection, "projection");
	shader->setVec3(glm::vec3(1.0f, 1.0f, 1.0f), "uniColor");

	

	glDrawElementsInstanced(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT,0, objectCount);

	glDeleteBuffers(1, &instanceBuffer); 
	glDeleteBuffers(1, &colorBuffer); 

}
void BallRenderer::InitializeVertices()
{
	float radius = 1.0f;
	unsigned int vCount = 36;

	float angle = 360.0f / vCount;

	unsigned int triangleCount = vCount - 2;

	std::vector<float>temp;

	for (unsigned int i = 0; i < vCount; i++)
	{
		float currentAngle = angle * i;

		float x = radius * cos(glm::radians(currentAngle));
		float y = radius * sin(glm::radians(currentAngle));


		this->vertices.push_back(x);
		this->vertices.push_back(y);
	}

	for (unsigned int i = 0; i < triangleCount; i++)
	{
		this->indices.push_back(0);
		this->indices.push_back(i+1);
		this->indices.push_back(i+2);
	}
}
