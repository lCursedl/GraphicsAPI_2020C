#include "CMesh.h"
#include "CGraphicsAPI.h"
#include "CSamplerState.h"

CMesh::CMesh(std::vector<MeshVertex>* vertex,
	std::vector<unsigned int>* index,
	std::vector<MeshTexture> tex,
	CGraphicsAPI* api)
{
	m_vVertices = vertex;
	m_vIndices = index;
	m_vTextures = tex;
	setupMesh(api);
}

CMesh::~CMesh()
{
	if (m_vVertices)
	{
		if (m_vVertices->size() > 0)
		{
			m_vVertices->clear();
			delete m_vVertices;
		}
	}
	if (m_vIndices)
	{
		if (m_vIndices->size() > 0)
		{
			m_vIndices->clear();
			delete m_vIndices;
		}
	}
	if (m_vTextures.size() > 0)
	{
		m_vTextures.clear();
	}
	if (m_pVertexBuffer)
	{
		delete m_pVertexBuffer;
	}
	if (m_pIndexBuffer)
	{
		delete m_pIndexBuffer;
	}
}

void CMesh::setupMesh(CGraphicsAPI* api)
{
	m_pVertexBuffer = api->createBuffer(m_vVertices->data(),
										sizeof(MeshVertex) * m_vVertices->size(),
										VERTEX_BUFFER);
	m_pIndexBuffer = api->createBuffer(m_vIndices->data(),
										sizeof(unsigned int) * m_vIndices->size(),
										INDEX_BUFFER);
}

void CMesh::draw(CGraphicsAPI* api, CSamplerState* sstate)
{
	for (unsigned int i = 0; i < m_vTextures.size(); i++)
	{
		api->setSamplerState(0, m_vTextures[i].m_Texture, sstate);
		api->setTexture(i, m_vTextures[i].m_Texture);
	}
	api->setVertexBuffer(m_pVertexBuffer, sizeof(MeshVertex), 0);
	api->setIndexBuffer(m_pIndexBuffer);
	api->drawIndexed(m_vIndices->size());
}