#include "pch.h"
#include "RectangleMeshComponent.h"

#include "DeviceManager.h"
#include "Actor.h"
using namespace std;

void CRectangleMeshComponent::Initialize()
{
	m_pD3DDevice9 = CDeviceManager::GetInstance()->GetDirect3DDevice9();
	m_eTextureType = ETextureType::TEXTURE;

	SetVertexInfo(4, sizeof(TextureVertex), TEXTURE_FVF);
	SetIndexInfo(2, sizeof(TextureIndex), D3DFMT_INDEX32);

	m_vecTextureVertices.reserve(4);
	m_vecTextureVertices.resize(4);
	m_vecTextureVertices[0] = { { -0.5f, +0.5f, 0.0f }, { 0.f, 0.f, 0.f }, { 0.0f, 0.0f } };
	m_vecTextureVertices[1] = { { +0.5f, +0.5f, 0.0f }, { 0.f, 0.f, 0.f }, { 1.0f, 0.0f } };
	m_vecTextureVertices[2] = { { +0.5f, -0.5f, 0.0f }, { 0.f, 0.f, 0.f }, { 1.0f, 1.0f } };
	m_vecTextureVertices[3] = { { -0.5f, -0.5f, 0.0f }, { 0.f, 0.f, 0.f }, { 0.0f, 1.0f } };

	m_vecTextureIndices.reserve(2);
	m_vecTextureIndices.resize(2);
	m_vecTextureIndices[0] = { 0, 1, 2 };
	m_vecTextureIndices[1] = { 0, 2, 3 };

	m_vecVertexWorldPos.reserve(4);
	m_vecVertexWorldPos.resize(4);

	m_vecVertexIndices.reserve(2);

	CMeshComponent::Initialize();
}

void CRectangleMeshComponent::BeginPlay()
{
	CMeshComponent::BeginPlay();
}

int32 CRectangleMeshComponent::Update(const float& _fDeltaSeconds)
{
	return CMeshComponent::Update(_fDeltaSeconds);
}

int32 CRectangleMeshComponent::LateUpdate(const float& _fDeltaSeconds)
{
	return CMeshComponent::LateUpdate(_fDeltaSeconds);
}

void CRectangleMeshComponent::Render()
{
	CMeshComponent::Render();

	// ���� ���(World matrix, W)�� �����մϴ�.
	m_pD3DDevice9->SetTransform(D3DTS_WORLD, &m_matWorld);

	// ��Ʈ�� �ҽ��� ���ؽ� ���ۿ� �����Ͽ� ������ ���������ο� �����ϴ�.
	m_pD3DDevice9->SetStreamSource(0, m_pVertexBuffer, 0, m_iVertexSize);

	// ���ؽ� ������ �����մϴ�.
	m_pD3DDevice9->SetFVF(m_iVertexFormat);

	// �ε��� ���۸� �����մϴ�.
	m_pD3DDevice9->SetIndices(m_pIndexBuffer);

	m_pD3DDevice9->SetTexture(0, m_vecD3DTextures[m_iFileIndex]);

	// �ε��� ������ Ȱ���� �⺻ ������ �׸��ϴ�.
	m_pD3DDevice9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_iNumVertices, 0, m_iNumTriangles);
}

void CRectangleMeshComponent::EndPlay()
{
	CMeshComponent::EndPlay();
}

void CRectangleMeshComponent::Release()
{
	CMeshComponent::Release();
}

void CRectangleMeshComponent::SetRectangleMeshInfo(const std::wstring& _wstrTextureFileName, uint32 _iBeginIndex, uint32 _iEndIndex)
{
	m_wstrTextureFileName = _wstrTextureFileName;
	m_iFileBeginIndex = _iBeginIndex;
	m_iFileEndIndex = _iEndIndex;
}

void CRectangleMeshComponent::SetTextureIndex(uint32 _iIndex)
{
	m_iFileIndex = _iIndex;
}

