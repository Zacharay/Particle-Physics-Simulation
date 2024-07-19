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
	
	shader = new Shader("shaders/ballVertexShader.vs", "shaders/ballFragmentShader.fs");

}
BallRenderer::~BallRenderer()
{
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
}
void BallRenderer::Draw(glm::vec2 ballPosition,glm::vec3 ballColor, float radius)
{
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, glm::vec3(ballPosition, 0.0f));
	model = glm::scale(model, glm::vec3(radius));
	
	glm::mat4 projection = glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT);

	shader->useProgram();
	shader->setMat4(model, "model");
	shader->setMat4(projection, "projection");
	shader->setVec3(ballColor, "uniColor");
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
}
void BallRenderer::InitializeVertices()
{
	float radius = 1.0f;
	unsigned int vCount = 36;

	float angle = 360.0f / vCount;

	unsigned int triangleCount = vCount - 2;

	std::vector<float>temp;

	for (int i = 0; i < vCount; i++)
	{
		float currentAngle = angle * i;

		float x = radius * cos(glm::radians(currentAngle));
		float y = radius * sin(glm::radians(currentAngle));


		this->vertices.push_back(x);
		this->vertices.push_back(y);
	}

	for (int i = 0; i < triangleCount; i++)
	{
		this->indices.push_back(0);
		this->indices.push_back(i+1);
		this->indices.push_back(i+2);
	}
}
