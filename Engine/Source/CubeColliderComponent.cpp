#include "pch.h"
#include "SphereColliderComponent.h"
#include "RectColliderComponent.h"
#include "CubeColliderComponent.h"

#include "DeviceManager.h"
#include "CollisionManager.h"
using namespace std;

void CCubeColliderComponent::Initialize()
{
	m_pD3DDevice9 = CDeviceManager::GetInstance()->GetDirect3DDevice9();
	m_eTextureType = ETextureType::COLOR;
	m_eColliderType = EColliderType::CUBE;
	m_ePrimitiveType = EPrimitiveType::COLLIDER;

	SetVertexInfo(8, sizeof(ColorVertex), COLOR_FVF);
	SetIndexInfo(12, sizeof(ColorIndex), D3DFMT_INDEX32);

	m_vecColorVertices.reserve(8);
	m_vecColorVertices.resize(8);

	// ����
	m_vecColorVertices[0] = { { -0.5f, 0.5f, -0.5f }, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f) };
	m_vecColorVertices[1] = { { 0.5f, 0.5f, -0.5f }, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f) };
	m_vecColorVertices[2] = { { 0.5f, -0.5f, -0.5f }, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f) };
	m_vecColorVertices[3] = { { -0.5f, -0.5f, -0.5f }, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f) };

	// �ĸ�
	m_vecColorVertices[4] = { { -0.5f, 0.5f, 0.5f }, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f) };
	m_vecColorVertices[5] = { { 0.5f, 0.5f, 0.5f }, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f) };
	m_vecColorVertices[6] = { { 0.5f, -0.5f, 0.5f }, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f) };
	m_vecColorVertices[7] = { { -0.5f, -0.5f, 0.5f }, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f) };

	m_vecColorIndices.reserve(12);
	m_vecColorIndices.resize(12);
	m_vecColorIndices[0] = { 1, 5, 6 };
	m_vecColorIndices[1] = { 1, 6, 2 };
	m_vecColorIndices[2] = { 4, 0, 3 };
	m_vecColorIndices[3] = { 4, 3, 7 };
	m_vecColorIndices[4] = { 4, 5, 1 };
	m_vecColorIndices[5] = { 4, 1, 0 };
	m_vecColorIndices[6] = { 3, 2, 6 };
	m_vecColorIndices[7] = { 3, 6, 7 };
	m_vecColorIndices[8] = { 7, 6, 5 };
	m_vecColorIndices[9] = { 7, 5, 4 };
	m_vecColorIndices[10] = { 0, 1, 2 };
	m_vecColorIndices[11] = { 0, 2, 3 };

	m_vecVertexWorldPos.reserve(8);
	m_vecVertexWorldPos.resize(8);

	m_vecVertexIndices.reserve(8);

	CColliderComponent::Initialize();
}

void CCubeColliderComponent::BeginPlay()
{
	CColliderComponent::BeginPlay();
}

int32 CCubeColliderComponent::Update(const float& _fDeltaSeconds)
{
	return CColliderComponent::Update(_fDeltaSeconds);
}

int32 CCubeColliderComponent::LateUpdate(const float& _fDeltaSeconds)
{
	return CColliderComponent::LateUpdate(_fDeltaSeconds);
}

void CCubeColliderComponent::Render()
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

void CCubeColliderComponent::EndPlay()
{
	CColliderComponent::EndPlay();
}

void CCubeColliderComponent::Release()
{
	CColliderComponent::Release();
}

bool CCubeColliderComponent::IsCollided(std::weak_ptr<CColliderComponent> _wpColliderComponent)
{
	if (IsCollisionLayerOverlapped(_wpColliderComponent) == false) { return false; }

	switch (_wpColliderComponent.lock()->GetColliderType())
	{
	case EColliderType::RECT:
		//return CCollisionManager::IntersectBoxToPlane(this, static_cast<CBoxColliderComponent*>(_pColliderComponent));;

	case EColliderType::CUBE:
		return CCollisionManager::IntersectCubeToCube(dynamic_pointer_cast<CCubeColliderComponent>(shared_from_this()), dynamic_pointer_cast<CCubeColliderComponent>(_wpColliderComponent.lock()));

	case EColliderType::SPHERE:
		//return CCollisionManager::IntersectBoxToSphere(this, static_cast<CSphereColliderComponent*>(_pColliderComponent));
	default:
		break;
	}
	return false;
}
