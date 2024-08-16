#include "pch.h"
#include "PrimitiveComponent.h"

#include "DeviceManager.h"
#include "CollisionManager.h"
#include "ResourceManager.h"

#include "Actor.h"
using namespace std;

void CPrimitiveComponent::Initialize()
{
	m_pD3DDevice9 = CDeviceManager::GetInstance()->GetDirect3DDevice9();
	CSceneComponent::Initialize();
	CreateTexture();
	CreateVertexBuffer();
	CreateIndexBuffer();
}

void CPrimitiveComponent::BeginPlay()
{
	if (!m_vecVertexPos.empty())
	{
		for (int32 i = 0; i < m_iNumVertices; ++i)
		{
			D3DXVec3TransformCoord(&m_vecVertexWorldPos[i], &m_vecVertexPos[i], &(GetOwnerActor().lock()->GetWorldMatrix()));
		}
	}
	CSceneComponent::BeginPlay();
}

int32 CPrimitiveComponent::Update(const float& _fDeltaSeconds)
{
	UpdateVerticesTransform();
	return CSceneComponent::Update(_fDeltaSeconds);
}

int32 CPrimitiveComponent::LateUpdate(const float& _fDeltaSeconds)
{
	return CSceneComponent::LateUpdate(_fDeltaSeconds);
}

void CPrimitiveComponent::EndPlay()
{
	CSceneComponent::EndPlay();
}

void CPrimitiveComponent::Render()
{
	CSceneComponent::Render();
}

void CPrimitiveComponent::Release()
{
	CSceneComponent::Release();
	if (m_pVertexBuffer) { m_pVertexBuffer->Release(); }
	if (m_pIndexBuffer) { m_pIndexBuffer->Release(); }

	CCollisionManager::GetInstance()->RemovePrimitiveComponent(dynamic_pointer_cast<CPrimitiveComponent>(shared_from_this()));
}

void CPrimitiveComponent::CreateVertexBuffer()
{
	ENSURE(m_pD3DDevice9->CreateVertexBuffer
	(
		m_iNumVertices * m_iVertexSize,	// ���ۿ� �Ҵ��� ����Ʈ ��
		0,								// ���� ����
		m_iVertexFormat,				// ���ؽ� ����
		m_tD3DPool,						// �޸� Ǯ
		&m_pVertexBuffer,				// ���ý� ���۸� ���� ������
		nullptr
	));
}

void CPrimitiveComponent::CreateIndexBuffer()
{
	ENSURE(m_pD3DDevice9->CreateIndexBuffer
	(
		m_iIndexSize * m_iNumTriangles,	// ���ۿ� �Ҵ��� ����Ʈ ��
		0,
		m_tIndexFormat,					// �ε��� ����
		m_tD3DPool,						// �޸� Ǯ
		&m_pIndexBuffer,				// �ε��� ���۸� ���� ������
		nullptr
	));
}

void CPrimitiveComponent::CreateTexture()
{
	// �ݶ��̴��� �ؽ�ó�� �ҷ����� �ʾƵ� �˴ϴ�.
	if (m_ePrimitiveType == EPrimitiveType::COLLIDER) { return; }

	m_vecD3DTextures.resize(m_iFileEndIndex - m_iFileBeginIndex + 1);
	m_vecD3DTextures.reserve(m_iFileEndIndex - m_iFileBeginIndex + 1);

	while (true)
	{
		if (!iswdigit(m_wstrTextureFileName.back())) { break; }
		m_wstrTextureFileName.pop_back();
	}

	if (m_eTextureType == ETextureType::TEXTURE)
	{
		const vector<pair<wstring, IDirect3DBaseTexture9*>>& vecD3DTextures = CResourceManager::GetInstance()->GetD3DTextures();
		for (uint32 iIndex = m_iFileBeginIndex; iIndex <= m_iFileEndIndex; ++iIndex)
		{
			const wstring& wstrFileName = m_wstrTextureFileName + to_wstring(iIndex);

			for (auto& pair : vecD3DTextures)
			{
				if (pair.first == wstrFileName)
				{
					m_vecD3DTextures[iIndex] = pair.second;
					break;
				}
			}
		}
	}
	else if (m_eTextureType == ETextureType::CUBE_TEXTURE)
	{
		const vector<pair<wstring, IDirect3DBaseTexture9*>>& vecD3DCubeTextures = CResourceManager::GetInstance()->GetD3DCubeTextures();
		for (uint32 iIndex = m_iFileBeginIndex; iIndex <= m_iFileEndIndex; ++iIndex)
		{
			const wstring& wstrFileName = m_wstrTextureFileName + to_wstring(iIndex);

			for (auto& pair : vecD3DCubeTextures)
			{
				if (pair.first == wstrFileName)
				{
					m_vecD3DTextures[iIndex] = pair.second;
					break;
				}
			}
		}
	}
}

void CPrimitiveComponent::UpdateVerticesTransform()
{
	if (!m_vecVertexPos.empty())
	{
		for (int32 i = 0; i < m_iNumVertices; ++i)
		{
			D3DXVec3TransformCoord(&m_vecVertexWorldPos[i], &m_vecVertexPos[i], &(GetWorldMatrix()));
		}
	}
}

void CPrimitiveComponent::SetVertexInfo(int32 _iNumVertices, int32 _iVertexSize, int32 _iVertexFormat)
{
	m_iNumVertices = _iNumVertices;
	m_iVertexSize = _iVertexSize;
	m_iVertexFormat = _iVertexFormat;
}

void CPrimitiveComponent::SetIndexInfo(int32 _iNumTriangles, int32 _iIndexSize, D3DFORMAT _tIndexFormat)
{
	m_iNumTriangles = _iNumTriangles;
	m_iIndexSize = _iIndexSize;
	m_tIndexFormat = _tIndexFormat;
}

void CPrimitiveComponent::SetUVInfo(float _fScaleU, float _fScaleV)
{
	m_fScaleU = _fScaleU;
	m_fScaleV = _fScaleV;
}

void CPrimitiveComponent::SetMaterialInfo(D3DXCOLOR _tDiffuse, D3DXCOLOR _tAmbient, D3DXCOLOR _tSpecular, D3DXCOLOR _tEmissive, float _fPower)
{
	D3DMATERIAL9 tMaterial;
	ZeroMemory(&tMaterial, sizeof(D3DMATERIAL9));

	tMaterial.Diffuse = _tDiffuse;	// ���ݻ籤
	tMaterial.Ambient = _tAmbient;	// ȯ�汤
	tMaterial.Specular = _tSpecular;// ���ݻ籤(���̴� ���� ������ �Ⱦ�, �⺻������ ��Ȱ��ȭ)
	tMaterial.Emissive = _tEmissive;// �� �߻�(���� �ȹ޾Ƶ� ȥ�ڼ� ����, �ֺ��� ������� ����)
	tMaterial.Power = _fPower;		// ���ݻ籤�� ��ī�ο� ����, ���������� ���̶���Ʈ ����. ���ݻ籤�� ��Ȱ��ȭ�� ���� 0.f

	m_pD3DDevice9->SetMaterial(&tMaterial);
}

