#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <iostream>
#include <vector>

struct Vertex
{
	glm::vec3 v_Position;
	glm::vec3 v_Normal;
	glm::vec2 v_TexCoords;
	glm::vec3 v_Tangent;
	glm::vec3 v_Bitangent;
};

struct Texture
{
	unsigned int i_ID;
	std::string s_type;
	std::string s_path;
};

class CMesh
{
public:
	
	CMesh(std::vector<Vertex> vertex,
		std::vector<unsigned int> index,
		std::vector<Texture> texture);
	~CMesh();

	std::vector<Vertex> m_vVertices;
	std::vector<unsigned int> m_vIndices;
	std::vector<Texture> m_vTextures;
};