#include "pch.h"
#include "Element.h"

#include "DeviceManager.h"

void CElement::Initialize()
{
	m_pD3DDevice9 = CDeviceManager::GetInstance()->GetDirect3DDevice9();
	m_eTextureType = ETextureType::TEXTURE;

	SetVertexInfo(4, sizeof(TextureVertex), TEXTURE_FVF);
	SetIndexInfo(2, sizeof(TextureIndex), D3DFMT_INDEX32);

	m_vecTextureVertices.reserve(4);
	m_vecTextureVertices.resize(4);
	m_vecTextureVertices[0] = { { -0.5f, +0.5f, 0.0f },{ 0.f, 0.f, 0.f }, { 0.0f, 0.0f } };
	m_vecTextureVertices[1] = { { +0.5f, +0.5f, 0.0f },{ 0.f, 0.f, 0.f }, { 1.0f, 0.0f } };
	m_vecTextureVertices[2] = { { +0.5f, -0.5f, 0.0f },{ 0.f, 0.f, 0.f }, { 1.0f, 1.0f } };
	m_vecTextureVertices[3] = { { -0.5f, -0.5f, 0.0f },{ 0.f, 0.f, 0.f }, { 0.0f, 1.0f } };

	m_vecTextureIndices.reserve(2);
	m_vecTextureIndices.resize(2);
	m_vecTextureIndices[0] = { 0, 1, 2 };
	m_vecTextureIndices[1] = { 0, 2, 3 };

	m_vecVertexWorldPos.reserve(4);
	m_vecVertexWorldPos.resize(4);

	m_vecVertexIndices.reserve(2);
    return;
}

void CElement::BeginPlay()
{
    return;
}

int32 CElement::Update(const float& _fDeltaSeconds)
{
    return 0;
}

int32 CElement::LateUpdate(const float& _fDeltaSeconds)
{
    return 0;
}

void CElement::EndPlay()
{
    return;
}

void CElement::Render()
{
	//CMeshComponent::Render();

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

	return;
}

void CElement::Release()
{
    return;
}

void CElement::SetElementSpriteInfo(const std::wstring& _wstrTextureFileName, uint32 _iBeginIndex, uint32 _iEndIndex)
{
	m_wstrTextureFileName = _wstrTextureFileName;
	m_iFileBeginIndex = _iBeginIndex;
	m_iFileEndIndex = _iEndIndex;
}