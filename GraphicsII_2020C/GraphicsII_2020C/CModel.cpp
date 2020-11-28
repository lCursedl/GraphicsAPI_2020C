#include "CModel.h"
#include "CGraphicsAPI.h"

std::string getTexturePath(std::string file)
{
	size_t realPos = 0;
	size_t posInvSlash = file.rfind('\\');
	size_t posSlash = file.rfind('/');

	if (posInvSlash == std::string::npos)
	{
		if (posSlash != std::string::npos)
		{
			realPos = posSlash;
		}
	}
	else
	{
		realPos = posInvSlash;
		if (!posSlash == std::string::npos)
		{
			if (posSlash > realPos)
			{
				posSlash = realPos;
			}
		}
	}
	return file.substr(realPos, file.length() - realPos);
}

CModel::CModel(){}

CModel::~CModel()
{
	for (unsigned int i = 0; i < m_vMeshes.size(); i++)
	{
		delete m_vMeshes[i];
	}
	m_vMeshes.clear();
	m_vTextures.clear();
}

void CModel::draw(CGraphicsAPI* api)
{
	for (unsigned int i = 0; i < m_vMeshes.size(); i++)
	{
		m_vMeshes[i]->draw(api, m_pSampler);
	}
}

void CModel::load(std::string const& path, CGraphicsAPI* api)
{
	//Read file via assimp
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path,
		aiProcessPreset_TargetRealtime_Fast |
		aiProcess_ConvertToLeftHanded |
		aiProcess_FindInstances |
		aiProcess_ValidateDataStructure |
		aiProcess_OptimizeMeshes |
		aiProcess_Debone);
	
	//Check for errors
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		return;
	}
	//Retrieve the directory path of the file
	m_sDirectory = path.substr(0, path.find_last_of('/'));
	//Process assimp's root node recursively
	processNode(scene->mRootNode, scene, api);
	//Create texture sampler for model's textures
	m_pSampler = api->createSamplerState(FILTER_LINEAR,
		FILTER_LINEAR,
		FILTER_LINEAR,
		0,
		WRAP);
}

void CModel::processNode(aiNode* node, const aiScene* scene, CGraphicsAPI* api)
{
	//Process each mesh located at the current node
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		//The node object only contains indices to index the actual objects in the scene.
		//The scene contains all the data, node is just to keep stuff organized.
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_vMeshes.push_back(processMesh(mesh, scene, api));
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene, api);
	}
}

CMesh* CModel::processMesh(aiMesh* mesh, const aiScene* scene, CGraphicsAPI* api)
{
	//Data to fill
	std::vector<MeshVertex>* vertices = new std::vector<MeshVertex>();
	std::vector<unsigned int>* indices = new std::vector<unsigned int>();
	std::vector<MeshTexture> textures;

	//Walk through each of the mesh's vertices.
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		MeshVertex v;
		//Positions
		v.Position.x = mesh->mVertices[i].x;
		v.Position.y = mesh->mVertices[i].y;
		v.Position.z = mesh->mVertices[i].z;
		//Texcoords
		//Check if mesh contains texcoords
		if (mesh->mTextureCoords[0])
		{
			v.TexCoords.x = mesh->mTextureCoords[0][i].x;
			v.TexCoords.y = mesh->mTextureCoords[0][i].y;
		}
		else
		{
			v.TexCoords = glm::vec2(0.0f, 0.0f);
		}
		//Normals
		v.Normal.x = mesh->mNormals[i].x;
		v.Normal.y = mesh->mNormals[i].y;
		v.Normal.z = mesh->mNormals[i].z;
		//Tangents
		v.Tangent.x = mesh->mTangents[i].x;
		v.Tangent.y = mesh->mTangents[i].y;
		v.Tangent.z = mesh->mTangents[i].z;
		//Bitangents
		v.Tangent.x = mesh->mBitangents[i].x;
		v.Tangent.y = mesh->mBitangents[i].y;
		v.Tangent.z = mesh->mBitangents[i].z;
		vertices->push_back(v);
	}
	//Go through each of the mesh's faces and retrieve the corresponding indices.
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		//retrieve all indices of the face and store them in the indices vector
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices->push_back(face.mIndices[j]);
		}
	}

	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

	std::vector<MeshTexture> diffuseMaps = loadMaterialTextures(material,
		aiTextureType_DIFFUSE,
		api);
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

	return new CMesh(vertices, indices, textures, api);
}

std::vector<MeshTexture> CModel::loadMaterialTextures(aiMaterial* material,
	aiTextureType type,
	CGraphicsAPI* api)
{
	std::vector<MeshTexture> textures;

	for (unsigned int i = 0; i < material->GetTextureCount(type); i++)
	{
		aiString aistr;
		material->GetTexture(type, i, &aistr);
		std::string str = std::string(aistr.C_Str());
		str = m_sDirectory + getTexturePath(str);
		bool skip = false;
		for (unsigned int j = 0; j < m_vTextures.size(); j++)
		{

			if (std::strcmp(m_vTextures[j].path.data(), str.data()) == 0)
			{
				textures.push_back(m_vTextures[j]);
				skip = true;
				break;
			}
		}
		if (!skip)
		{
			MeshTexture meshTexture;
			meshTexture.m_Texture = api->createTextureFromFile(str);
			meshTexture.path = str;
			textures.push_back(meshTexture);
			m_vTextures.push_back(meshTexture);
		}
	}
	return textures;
}
