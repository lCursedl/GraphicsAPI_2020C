#pragma once
#include "CMesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class CModel
{
public:
	CModel();
	~CModel();

	void draw(CGraphicsAPI* api);
	void load(std::string const & path, CGraphicsAPI* api);
private:
	std::vector<CMesh*> m_vMeshes;
	std::string m_sDirectory;

	void processNode(aiNode* node, const aiScene* scene, CGraphicsAPI* api);
	CMesh* processMesh(aiMesh* mesh, const aiScene* scene, CGraphicsAPI* api);
};