#include "pch.h"
#include "TriangleMeshComponent.h"

#include "DeviceManager.h"
#include "Actor.h"
using namespace std;

void CTriangleMeshComponent::Initialize()
{
	m_pD3DDevice9 = CDeviceManager::GetInstance()->GetDirect3DDevice9();
	m_pD3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice9->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_eTextureType = ETextureType::TEXTURE;

	SetVertexInfo(3, sizeof(TextureVertex), TEXTURE_FVF);
	SetIndexInfo(1, sizeof(TextureIndex), D3DFMT_INDEX32);

	m_vecTextureVertices.reserve(3);
	m_vecTextureVertices.resize(3);
	m_vecTextureVertices[0] = { { -0.5f, -1 / 2 * sqrtf(3.0f), 0.0f }, { 0.0f, 1.0f } };
	m_vecTextureVertices[1] = { { +0.0f,     +1 / sqrtf(3.0f), 0.0f }, { 0.5f, 0.0f } };
	m_vecTextureVertices[2] = { { +0.5f, -1 / 2 * sqrtf(3.0f), 0.0f }, { 1.0f, 1.0f } };

	m_vecTextureIndices.reserve(1);
	m_vecTextureIndices.resize(1);
	m_vecTextureIndices[0] = { 0, 1, 2 };
	CMeshComponent::Initialize();
}

void CTriangleMeshComponent::BeginPlay()
{
	CMeshComponent::BeginPlay();
}

int32 CTriangleMeshComponent::Update(const float& _fDeltaSeconds)
{
	return CMeshComponent::Update(_fDeltaSeconds);
}

int32 CTriangleMeshComponent::LateUpdate(const float& _fDeltaSeconds)
{
	return CMeshComponent::LateUpdate(_fDeltaSeconds);
}

void CTriangleMeshComponent::Render()
{
	CMeshComponent::Render();

	// 월드 행렬(World matrix, W)을 설정합니다.
	m_pD3DDevice9->SetTransform(D3DTS_WORLD, &m_matWorld);

	// 스트림 소스에 버텍스 버퍼를 지정한다.
	m_pD3DDevice9->SetStreamSource(0, m_pVertexBuffer, 0, m_iVertexSize);

	// 버텍스 포맷을 지정한다.
	m_pD3DDevice9->SetFVF(m_iVertexFormat);

	// 인덱스 버퍼를 지정한다.
	m_pD3DDevice9->SetIndices(m_pIndexBuffer);

	m_pD3DDevice9->SetTexture(0, m_vecD3DTextures[m_iFileIndex]);

	// 인덱스 정보를 활용해 기본 도형을 그린다. 
	m_pD3DDevice9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_iNumVertices, 0, m_iNumTriangles);
}

void CTriangleMeshComponent::EndPlay()
{
	CMeshComponent::EndPlay();
}

void CTriangleMeshComponent::Release()
{
	CMeshComponent::Release();
}

void CTriangleMeshComponent::SetTriangleMeshInfo(const std::wstring _wstrTextureFileName, int32 _iFileIndex, const std::wstring _wstrTextureFileExt)
{
	m_wstrTextureFileName = _wstrTextureFileName;
	m_wstrTextureFileExt = _wstrTextureFileExt;
	m_iFileIndex = _iFileIndex;
}
