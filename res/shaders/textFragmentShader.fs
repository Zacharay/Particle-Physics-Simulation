#version 330 core

out vec4 FragColor;
in vec2 TexCoords;
uniform sampler2D ourTexture;


void main()
{
	vec4 sampled = vec4(1.0f,1.0f,1.0f,texture(ourTexture,TexCoords).r);
	FragColor = vec4(1.0f)*sampled;
}