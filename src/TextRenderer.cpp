#include "TextRenderer.hpp"


struct Vertice {
	float xPos;
	float yPos;
	float texturePosX;
	float texturePosY;

	Vertice(float x, float y, float texX, float texY) : xPos(x), yPos(y), texturePosX(texX), texturePosY(texY) {}

};

TextRenderer::TextRenderer()
{
	this->LoadCharacterData();

	this->shader = new Shader("res/shaders/textVertexShader.vs", "res/shaders/textFragmentShader.fs");

	int width, height, nrChannels;

	unsigned char* data = stbi_load("res/font/font.png", &width, &height, &nrChannels, 0);

	glGenTextures(1, &this->textureID);
	glBindTexture(GL_TEXTURE_2D, this->textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
	
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
	
}
void TextRenderer::LoadCharacterData()
{
	std::ifstream file("res/font/font.fnt");

	if (!file.is_open())
	{
		std::cerr << "Failed to open the file." << std::endl;
	}

	std::string line;
	std::getline(file, line);
	int idx = -1;
	while (std::getline(file, line))
	{


		std::string temp = "";


		unsigned int id = 0;
		int xPos = 0, yPos = 0, xOffset = 0, xAdvance = 0, width = 0;
		for (char c : line)
		{
			if (c == ' ' || c == '\n')continue;

			if (c != ';') {
				temp += c;

			}
			else {

				idx++;

				switch (idx) {
				case 0:
					id = stoi(temp);

					break;
				case 1:
					xPos = stoi(temp);

					break;
				case 2:
					yPos = stoi(temp);

					break;
				case 3:
					width = stoi(temp);

					break;
				case 4:
					xOffset = stoi(temp);

					break;
				case 5:
					xAdvance = stoi(temp);

					idx = -1;
					break;
				}
				temp = "";
			}
		}
		Character ch = {
			id,
			glm::ivec2(xPos,yPos),
			width,
			xOffset,
			xAdvance
		};

		this->Characters.insert(std::pair<char, Character>(char(ch.id), ch));

	}
	file.close();
}
void TextRenderer::DrawText(std::string str, unsigned int xPos, unsigned int yPos)
{

	float chHeight = 32;

	std::vector<Vertice> vertices;
	unsigned int x = xPos;
	unsigned int y = yPos;
	for (char c : str)
	{
		Character ch = this->Characters[c];
		//todo texture mapping
		vertices.emplace_back(x,y,0,0); //left bottom
		vertices.emplace_back(x+ch.width,y,0,0); // right bottom
		vertices.emplace_back(x + ch.width,y+ chHeight,0,0); // top left

		vertices.emplace_back(x, y, 0, 0); // left bottom
		vertices.emplace_back(x + ch.width, y+ chHeight, 0, 0); //top left
		vertices.emplace_back(x, y + chHeight, 0, 0); // top right

		x += ch.xAdvance;
	}


	

	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);


	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertice), vertices.data(), GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertice), (void*)offsetof(Vertice, xPos));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertice), (void*)offsetof(Vertice, texturePosX));
	glEnableVertexAttribArray(1);


	//glBindTexture(GL_TEXTURE_2D, this->textureID);
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(WINDOW_WIDTH), 0.0f, static_cast<float>(WINDOW_HEIGHT));
	this->shader->useProgram();
	this->shader->setMat4(projection, "projection");
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

}

