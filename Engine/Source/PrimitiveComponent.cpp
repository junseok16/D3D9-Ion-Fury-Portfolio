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
		m_iNumVertices * m_iVertexSize,	// 버퍼에 할당할 바이트 수
		0,								// 정적 버퍼
		m_iVertexFormat,				// 버텍스 포맷
		m_tD3DPool,						// 메모리 풀
		&m_pVertexBuffer,				// 버택스 버퍼를 받을 포인터
		nullptr
	));
}

void CPrimitiveComponent::CreateIndexBuffer()
{
	ENSURE(m_pD3DDevice9->CreateIndexBuffer
	(
		m_iIndexSize * m_iNumTriangles,	// 버퍼에 할당할 바이트 수
		0,
		m_tIndexFormat,					// 인덱스 포맷
		m_tD3DPool,						// 메모리 풀
		&m_pIndexBuffer,				// 인덱스 버퍼를 받을 포인터
		nullptr
	));
}

void CPrimitiveComponent::CreateTexture()
{
	// 콜라이더는 텍스처를 불러오지 않아도 됩니다.
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

	tMaterial.Diffuse = _tDiffuse;	// 난반사광
	tMaterial.Ambient = _tAmbient;	// 환경광
	tMaterial.Specular = _tSpecular;// 정반사광(쉐이더 쓰기 전까진 안씀, 기본적으로 비활성화)
	tMaterial.Emissive = _tEmissive;// 빛 발산(빛을 안받아도 혼자서 빛남, 주변이 밝아지진 않음)
	tMaterial.Power = _fPower;		// 정반사광의 날카로운 정도, 높아질수록 하이라이트 강조. 정반사광이 비활성화라 보통 0.f

	m_pD3DDevice9->SetMaterial(&tMaterial);
}

