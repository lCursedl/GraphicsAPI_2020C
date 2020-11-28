#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <iostream>
#include <vector>

class CBuffer;
class CGraphicsAPI;
class CTexture;
class CSamplerState;

struct MeshVertex
{
	glm::vec3 Position;
	glm::vec2 TexCoords;
	glm::vec3 Normal;	
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
};

struct MeshTexture
{
	std::string type;
	std::string path;
	CTexture* m_Texture;
};

class CMesh
{
public:
	
	CMesh(std::vector<MeshVertex>* vertex,
		std::vector<unsigned int>* index,
		std::vector<MeshTexture> tex,
		CGraphicsAPI* api);
	~CMesh();
	void setupMesh(CGraphicsAPI* api);
	void draw(CGraphicsAPI* api, CSamplerState* sstate);

private:

	std::vector<MeshVertex>* m_vVertices;
	std::vector<unsigned int>* m_vIndices;
	std::vector<MeshTexture> m_vTextures;
	CBuffer* m_pVertexBuffer;
	CBuffer* m_pIndexBuffer;
};