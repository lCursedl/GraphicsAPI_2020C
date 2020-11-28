#pragma once
#include "CMesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class CTexture;

class CModel
{
public:
	CModel();
	~CModel();

	void draw(CGraphicsAPI* api);
	void load(std::string const & path, CGraphicsAPI* api);
private:
	std::vector<CMesh*> m_vMeshes;
	std::vector<MeshTexture> m_vTextures;
	std::string m_sDirectory;
	CSamplerState* m_pSampler;

	void processNode(aiNode* node, const aiScene* scene, CGraphicsAPI* api);
	CMesh* processMesh(aiMesh* mesh, const aiScene* scene, CGraphicsAPI* api);
	std::vector<MeshTexture> loadMaterialTextures(aiMaterial* material,
													aiTextureType type,
													CGraphicsAPI* api);
};