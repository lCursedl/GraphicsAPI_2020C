#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <iostream>
#include <vector>

class CBuffer;
class CGraphicsAPI;

struct MeshVertex
{
	glm::vec3 Position;
	glm::vec2 TexCoords;
	glm::vec3 Normal;	
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
};

class CMesh
{
public:
	
	CMesh(std::vector<MeshVertex>* vertex,
		std::vector<unsigned int>* index,
		CGraphicsAPI* api);
	~CMesh();
	void setupMesh(CGraphicsAPI* api);
	void draw(CGraphicsAPI* api);

private:

	std::vector<MeshVertex>* m_vVertices;
	std::vector<unsigned int>* m_vIndices;
	CBuffer* m_pVertexBuffer;
	CBuffer* m_pIndexBuffer;
};