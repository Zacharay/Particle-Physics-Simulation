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

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
	
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);


	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertice), (void*)offsetof(Vertice, xPos));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertice), (void*)offsetof(Vertice, texturePosX));
	glEnableVertexAttribArray(1);
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

	constexpr float chHeight = 32;
	constexpr float textureSize = 512.0f;


	std::vector<Vertice> vertices;
	unsigned int x = xPos;
	unsigned int y = yPos;

	


	for (char c : str)
	{
		Character ch = this->Characters[c];

		float textureX = ch.textureCoordinates.x;
		float textureY = ch.textureCoordinates.y;
		float textureWidth = ch.width;
		float textureHeight = 32.0f;



		float left = textureX / textureSize; //left
		float top = textureY / textureSize; //top
		float right = (textureX + textureWidth) / textureSize; //right
		float bottom = (textureY + textureHeight) / textureSize; //bottom
		x += ch.xOffset;
		

		vertices.emplace_back(x,					y,								left, bottom);                             // Left bottom
		vertices.emplace_back(x + textureWidth,		y,								right, bottom);                  // Right bottom
		vertices.emplace_back(x + textureWidth,		y + textureHeight,				right, top);       // Right top

		vertices.emplace_back(x,					y,								left, bottom);                             // Left bottom
		vertices.emplace_back(x + textureWidth,		y + textureHeight,				right, top);       // Right top
		vertices.emplace_back(x,					y + textureHeight,				left, top);                  // Left top
		
		x -= ch.xOffset;
		x += ch.xAdvance;
		
	}


	

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER,this->VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertice), vertices.data(), GL_DYNAMIC_DRAW);



	glBindTexture(GL_TEXTURE_2D, this->textureID);
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(WINDOW_WIDTH), 0.0f, static_cast<float>(WINDOW_HEIGHT));
	this->shader->useProgram();
	this->shader->setMat4(projection, "projection");

	

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	

}

