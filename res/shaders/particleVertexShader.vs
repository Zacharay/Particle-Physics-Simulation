#version 330 core

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec4 aColor;
layout(location = 2) in mat4 instanceMatrix;

out vec4 color;

uniform mat4 projection;

void main()
{
	gl_Position = projection*instanceMatrix*vec4(aPos,0.0f,1.0f);

	color = vec4(aColor);
}