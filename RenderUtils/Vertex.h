#pragma once
#include "GLM\glm.hpp"

struct Vertex
{
	glm::vec4 position;
	glm::vec4 color;
	glm::vec4 normal;
	glm::vec2 texCoord;

	//float position[4];
	//float color[4];
	//float normal[4];
	//float tangent[4];
	//float binormal[4];
	//float texCoord[2];

	enum
	{
		POSITION = 0,
		COLOR = 16,
		NORMAL = 32,
		TEXCOORD = 32,
	};
};