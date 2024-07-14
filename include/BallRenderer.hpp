#pragma once
#include <vector>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.hpp"
class BallRenderer {
private:
	unsigned int VBO, VAO, IBO;
	Shader *shader;
	std::vector<float>vertices;
	std::vector<unsigned int>indices;

public:
	BallRenderer();
	~BallRenderer();
	void Draw(glm::vec2 ballPosition, float radius);
	void InitializeVertices();
};