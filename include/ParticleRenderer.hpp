#pragma once
#include <vector>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.hpp"
#include "Particle.hpp"
class ParticleRenderer {
private:
	unsigned int VBO, VAO, IBO;
	Shader *shader;
	std::vector<float>vertices;
	std::vector<unsigned int>indices;

public:
	ParticleRenderer();
	~ParticleRenderer();
	void DrawParticles(const std::vector<std::shared_ptr<Particle>>& m_particles)const;
	void InitializeVertices();
};