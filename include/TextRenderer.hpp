#pragma once
#include "Shader.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include "glm/glm.hpp"
#include "Globals.hpp"
#include "stb_image.h"


struct Character {
	unsigned int id;
	glm::ivec2 textureCoordinates;
	unsigned int width;
	int xOffset;
	int xAdvance;
};

class TextRenderer {
private:

	unsigned int VAO, VBO,textureID;
	Shader* shader;

	std::map<char, Character>Characters;

public:
	TextRenderer();
	void DrawText(std::string str, unsigned int xPos, unsigned int yPos);
	void LoadCharacterData();
};