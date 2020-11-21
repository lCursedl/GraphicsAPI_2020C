#include "CMesh.h"
#include "CGraphicsAPI.h"

CMesh::CMesh(std::vector<MeshVertex>* vertex,
	std::vector<unsigned int>* index,
	CGraphicsAPI* api)
{
	m_vVertices = vertex;
	m_vIndices = index;
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

void CMesh::draw(CGraphicsAPI* api)
{
	api->setVertexBuffer(m_pVertexBuffer, sizeof(MeshVertex));
	api->setIndexBuffer(m_pIndexBuffer);
	api->drawIndexed(m_vIndices->size());
}