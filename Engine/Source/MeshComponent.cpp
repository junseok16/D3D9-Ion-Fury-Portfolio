#include "pch.h"
#include "MeshComponent.h"

void CMeshComponent::Initialize()
{
	CPrimitiveComponent::Initialize();
	CreateVertices();
	CreateIndices();
}

void CMeshComponent::BeginPlay()
{
	CPrimitiveComponent::BeginPlay();
}

int CMeshComponent::Update(const float& _fDeltaSeconds)
{
	return CPrimitiveComponent::Update(_fDeltaSeconds);
}

int CMeshComponent::LateUpdate(const float& _fDeltaSeconds)
{
	return CPrimitiveComponent::LateUpdate(_fDeltaSeconds);
}

void CMeshComponent::Render()
{
	CPrimitiveComponent::Render();
}

void CMeshComponent::EndPlay()
{
	CPrimitiveComponent::EndPlay();
}

void CMeshComponent::Release()
{
	CPrimitiveComponent::Release();
}

void CMeshComponent::CreateVertices()
{
	switch (m_eTextureType)
	{
	case ETextureType::TEXTURE:
	{
		TextureVertex* pVertex = nullptr;
		ENSURE(m_pVertexBuffer->Lock(0, 0, (void**)&pVertex, 0));

		for (int32 nth = 0; nth < m_iNumVertices; ++nth)
		{
			pVertex[nth].position = m_vecTextureVertices[nth].position;
			pVertex[nth].normal = m_vecTextureVertices[nth].normal;

			pVertex[nth].uv.x = m_vecTextureVertices[nth].uv.x * m_fScaleU;
			pVertex[nth].uv.y = m_vecTextureVertices[nth].uv.y * m_fScaleV;
			// pVertex[nth].uv = m_vecTextureVertices[nth].uv;

			m_vecVertexPos.push_back(pVertex[nth].position);
		}
		ENSURE(m_pVertexBuffer->Unlock());

	}
		break;

	case ETextureType::CUBE_TEXTURE:
	{
		CubeTextureVertex* pVertex = nullptr;
		ENSURE(m_pVertexBuffer->Lock(0, 0, (void**)&pVertex, 0));

		for (int32 nth = 0; nth < m_iNumVertices; ++nth)
		{
			pVertex[nth].position = m_vecCubeTextureVertices[nth].position;
			pVertex[nth].normal = m_vecCubeTextureVertices[nth].normal;
			pVertex[nth].uv = m_vecCubeTextureVertices[nth].uv;

			m_vecVertexPos.push_back(pVertex[nth].position);
		}
		ENSURE(m_pVertexBuffer->Unlock());

	}
		break;

	default:
		CHECKF(false, TEXT("Texture type isn't designated."))
		break;
	}
}

void CMeshComponent::CreateIndices()
{
	switch (m_eTextureType)
	{
	case ETextureType::TEXTURE:
	{
		TextureIndex* pIndex = nullptr;
		ENSURE(m_pIndexBuffer->Lock(0, 0, (void**)&pIndex, 0));

		FVector3 vDst = { 0.f, 0.f, 0.f }, vSrc = { 0.f, 0.f, 0.f }, vNormal = { 0.f, 0.f, 0.f };

		for (int32 nth = 0; nth < m_iNumTriangles; ++nth)
		{
			pIndex[nth]._0 = m_vecTextureIndices[nth]._0;
			pIndex[nth]._1 = m_vecTextureIndices[nth]._1;
			pIndex[nth]._2 = m_vecTextureIndices[nth]._2;

			vDst = m_vecTextureVertices[pIndex[nth]._1].position - m_vecTextureVertices[pIndex[nth]._0].position;
			vSrc = m_vecTextureVertices[pIndex[nth]._2].position - m_vecTextureVertices[pIndex[nth]._0].position;

			D3DXVec3Cross(&vNormal, &vDst, &vSrc);

			m_vecTextureVertices[pIndex[nth]._0].normal += vNormal;
			m_vecTextureVertices[pIndex[nth]._1].normal += vNormal;
			m_vecTextureVertices[pIndex[nth]._2].normal += vNormal;

			D3DXVec3Normalize(&m_vecTextureVertices[pIndex[nth]._0].normal, &m_vecTextureVertices[pIndex[nth]._0].normal);
			D3DXVec3Normalize(&m_vecTextureVertices[pIndex[nth]._1].normal, &m_vecTextureVertices[pIndex[nth]._1].normal);
			D3DXVec3Normalize(&m_vecTextureVertices[pIndex[nth]._2].normal, &m_vecTextureVertices[pIndex[nth]._2].normal);

			m_vecVertexIndices.push_back({ (float)pIndex[nth]._0 , (float)pIndex[nth]._1 , (float)pIndex[nth]._2 });
		}

		ENSURE(m_pIndexBuffer->Unlock());
		// m_vecTextureIndices.clear(); // UV반전 함수를 위해 잠시 주석처리 - 박동연 -
		// m_vecTextureVertices.clear();
	}
		break;

	case ETextureType::CUBE_TEXTURE:
	{
		CubeTextureIndex* pIndex = nullptr;
		ENSURE(m_pIndexBuffer->Lock(0, 0, (void**)&pIndex, 0));

		FVector3 vDst = { 0.f, 0.f, 0.f }, vSrc = { 0.f, 0.f, 0.f }, vNormal = { 0.f, 0.f, 0.f };

		for (int32 nth = 0; nth < m_iNumTriangles; ++nth)
		{
			pIndex[nth]._0 = m_vecCubeTextureIndices[nth]._0;
			pIndex[nth]._1 = m_vecCubeTextureIndices[nth]._1;
			pIndex[nth]._2 = m_vecCubeTextureIndices[nth]._2;

			vDst = m_vecCubeTextureVertices[pIndex[nth]._1].position - m_vecCubeTextureVertices[pIndex[nth]._0].position;
			vSrc = m_vecCubeTextureVertices[pIndex[nth]._2].position - m_vecCubeTextureVertices[pIndex[nth]._0].position;

			D3DXVec3Cross(&vNormal, &vDst, &vSrc);

			m_vecCubeTextureVertices[pIndex[nth]._0].normal += vNormal;
			m_vecCubeTextureVertices[pIndex[nth]._1].normal += vNormal;
			m_vecCubeTextureVertices[pIndex[nth]._2].normal += vNormal;

			D3DXVec3Normalize(&m_vecCubeTextureVertices[pIndex[nth]._0].normal, &m_vecCubeTextureVertices[pIndex[nth]._0].normal);
			D3DXVec3Normalize(&m_vecCubeTextureVertices[pIndex[nth]._1].normal, &m_vecCubeTextureVertices[pIndex[nth]._1].normal);
			D3DXVec3Normalize(&m_vecCubeTextureVertices[pIndex[nth]._2].normal, &m_vecCubeTextureVertices[pIndex[nth]._2].normal);

			m_vecVertexIndices.push_back({ (float)pIndex[nth]._0 , (float)pIndex[nth]._1 , (float)pIndex[nth]._2 });
		}

		ENSURE(m_pIndexBuffer->Unlock());
		// m_vecCubeTextureIndices.clear();
		// m_vecCubeTextureVertices.clear();
	}
		break;

	default:
		CHECKF(false, TEXT("Texture type isn't designated."))
		break;
	}	
}

void CMeshComponent::ReverseTextureUV()
{
	TextureVertex* pVertex = nullptr;
	ENSURE(m_pVertexBuffer->Lock(0, 0, (void**)&pVertex, 0));

	for (int32 nth = 0; nth < m_iNumVertices; ++nth)
	{
		pVertex[nth].position = m_vecTextureVertices[nth].position;
		pVertex[nth].normal = m_vecTextureVertices[nth].normal;

		pVertex[nth].uv.x = 1.0f - m_vecTextureVertices[nth].uv.x * m_fScaleU;
		pVertex[nth].uv.y = m_vecTextureVertices[nth].uv.y * m_fScaleV;
	}
	ENSURE(m_pVertexBuffer->Unlock());
}

void CMeshComponent::SetTextureUV(const float& _fU, const float& _fV)
{
	// 큐브 텍스쳐가 아닌 일반 텍스쳐에 한하여
	if (m_eTextureType == ETextureType::CUBE_TEXTURE)
	{
		return;
	}

	TextureVertex* pVertex = nullptr;
	ENSURE(m_pVertexBuffer->Lock(0, 0, (void**)&pVertex, 0));

	for (int32 nth = 0; nth < m_iNumVertices; ++nth)
	{
		pVertex[nth].position = m_vecTextureVertices[nth].position;
		pVertex[nth].normal = m_vecTextureVertices[nth].normal;

		pVertex[nth].uv.x = _fU;
		pVertex[nth].uv.y = _fV;

		// pVertex[nth].uv.x = m_vecTextureVertices[nth].uv.x * m_fScaleU;
		// pVertex[nth].uv.y = m_vecTextureVertices[nth].uv.y * m_fScaleV;
		
		// pVertex[nth].uv.x = 1.0f - (pVertex[nth].uv.x - 0.0f) * (_fU - 0.0f);
		// pVertex[nth].uv.y = 1.0f - (pVertex[nth].uv.y - 0.0f) * (_fV - 0.0f);

		if (nth > 1)
		{
			pVertex[nth].position.y = - 0.5f + _fV;
		}
		else
		{
			pVertex[nth].position.y = 0.5f;
		}
	}
	ENSURE(m_pVertexBuffer->Unlock());
}
