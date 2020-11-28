#version 420 core
out vec4 FragColor;

layout(std140, binding = 0) uniform Matrices
{
	mat4 World;
	mat4 Projection;
	vec4 Color;
};

layout(std140, binding = 1) uniform cbView
{
	mat4 View;
};

in vec2 Texcoord;
in vec4 psPos;

layout(binding = 0) uniform sampler2D diffuse;

void main()
{
	FragColor = psPos;
}