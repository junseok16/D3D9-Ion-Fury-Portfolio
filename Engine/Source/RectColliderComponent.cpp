#include "pch.h"
#include "RectColliderComponent.h"
#include "SphereColliderComponent.h"
#include "CubeColliderComponent.h"

#include "DeviceManager.h"
#include "CollisionManager.h"
using namespace std;

void CRectColliderComponent::Initialize()
{
	m_pD3DDevice9 = CDeviceManager::GetInstance()->GetDirect3DDevice9();
	m_eTextureType = ETextureType::COLOR;
	m_eColliderType = EColliderType::RECT;
	m_ePrimitiveType = EPrimitiveType::COLLIDER;

	SetVertexInfo(4, sizeof(ColorVertex), COLOR_FVF);
	SetIndexInfo(2, sizeof(ColorIndex), D3DFMT_INDEX32);

	m_vecColorVertices.reserve(4);
	m_vecColorVertices.resize(4);

	m_vecColorVertices[0] = { { -0.5f, 0.0f, +0.5f }, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f) };
	m_vecColorVertices[1] = { { +0.5f, 0.0f, +0.5f }, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f) };
	m_vecColorVertices[2] = { { +0.5f, 0.0f, -0.5f }, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f) };
	m_vecColorVertices[3] = { { -0.5f, 0.0f, -0.5f }, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f) };

	m_vecColorIndices.reserve(2);
	m_vecColorIndices.resize(2);
	m_vecColorIndices[0] = { 0, 1, 2 };
	m_vecColorIndices[1] = { 0, 2, 3 };

	m_vecVertexWorldPos.reserve(4);
	m_vecVertexWorldPos.resize(4);

	m_vecVertexIndices.reserve(2);

	CColliderComponent::Initialize();
}

void CRectColliderComponent::BeginPlay()
{
	CColliderComponent::BeginPlay();
}

int32 CRectColliderComponent::Update(const float& _fDeltaSeconds)
{
	return CColliderComponent::Update(_fDeltaSeconds);
}

int32 CRectColliderComponent::LateUpdate(const float& _fDeltaSeconds)
{
	UpdatePlane();
	return CColliderComponent::LateUpdate(_fDeltaSeconds);
}

void CRectColliderComponent::Render()
{
	CColliderComponent::Render();

	/*
	m_pD3DDevice9->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	// ���� ���(World matrix, W)�� �����մϴ�.
	m_pD3DDevice9->SetTransform(D3DTS_WORLD, &m_matWorld);

	// ��Ʈ�� �ҽ��� ���ؽ� ���ۿ� �����Ͽ� ������ ���������ο� �����ϴ�.
	m_pD3DDevice9->SetStreamSource(0, m_pVertexBuffer, 0, m_iVertexSize);

	// ���ؽ� ������ �����մϴ�.
	m_pD3DDevice9->SetFVF(m_iVertexFormat);

	// �ε��� ���۸� �����մϴ�.
	m_pD3DDevice9->SetIndices(m_pIndexBuffer);

	// �ε��� ������ Ȱ���� �⺻ ������ �׸��ϴ�.
	m_pD3DDevice9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_iNumVertices, 0, m_iNumTriangles);

	m_pD3DDevice9->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	*/
}

void CRectColliderComponent::EndPlay()
{
	CColliderComponent::EndPlay();
}

void CRectColliderComponent::Release()
{
	CColliderComponent::Release();
}

bool CRectColliderComponent::IsCollided(std::weak_ptr<CColliderComponent> _wpColliderComponent)
{
	CHECK(!_wpColliderComponent.expired());

	if (IsCollisionLayerOverlapped(_wpColliderComponent) == false) { return false; }

	switch (_wpColliderComponent.lock()->GetColliderType())
	{
	case EColliderType::RECT:
		break;

	case EColliderType::CUBE:
		break;

	case EColliderType::SPHERE:
		break;
	}
	return false;
}

void CRectColliderComponent::UpdatePlane()
{
	if (!m_vecVertexPos.empty())
	{
		D3DXPlaneFromPoints
		(
			&m_tD3DPlane,
			&m_vecVertexPos[0],
			&m_vecVertexPos[1],
			&m_vecVertexPos[2]
		);
	}
}