#include "pch.h"
#include "SphereColliderComponent.h"
#include "RectColliderComponent.h"
#include "CubeColliderComponent.h"

#include "DeviceManager.h"
#include "CollisionManager.h"
using namespace std;

void CSphereColliderComponent::Initialize()
{
	m_pD3DDevice9 = CDeviceManager::GetInstance()->GetDirect3DDevice9();
	m_eTextureType = ETextureType::COLOR;
	m_eColliderType = EColliderType::SPHERE;
	m_ePrimitiveType = EPrimitiveType::COLLIDER;

	SetVertexInfo(4, sizeof(ColorVertex), COLOR_FVF);
	SetIndexInfo(2, sizeof(ColorIndex), D3DFMT_INDEX32);

	m_vecColorVertices.reserve(4);
	m_vecColorVertices.resize(4);
	m_vecColorVertices[0] = { { -0.5f, +0.5f, 0.0f }, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f) };
	m_vecColorVertices[1] = { { +0.5f, +0.5f, 0.0f }, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f) };
	m_vecColorVertices[2] = { { +0.5f, -0.5f, 0.0f }, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f) };
	m_vecColorVertices[3] = { { -0.5f, -0.5f, 0.0f }, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.0f) };

	m_vecColorIndices.reserve(2);
	m_vecColorIndices.resize(2);
	m_vecColorIndices[0] = { 0, 1, 2 };
	m_vecColorIndices[1] = { 0, 2, 3 };

	D3DXCreateSphere(m_pD3DDevice9, m_fRadius, m_iSlice, m_iStack, &m_pMesh, NULL);
	CColliderComponent::Initialize();
}

void CSphereColliderComponent::BeginPlay()
{
	CColliderComponent::BeginPlay();
}

int32 CSphereColliderComponent::Update(const float& _fDeltaSeconds)
{
	return CColliderComponent::Update(_fDeltaSeconds);
}

int32 CSphereColliderComponent::LateUpdate(const float& _fDeltaSeconds)
{
	return CColliderComponent::LateUpdate(_fDeltaSeconds);
}

void CSphereColliderComponent::Render()
{
	m_pD3DDevice9->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pMesh->DrawSubset(0);
	m_pD3DDevice9->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	CColliderComponent::Render();
}

void CSphereColliderComponent::EndPlay()
{
	CColliderComponent::EndPlay();
}

void CSphereColliderComponent::Release()
{
	CColliderComponent::Release();
}

bool CSphereColliderComponent::IsCollided(std::weak_ptr<CColliderComponent> _wpColliderComponent)
{
	CHECK(!_wpColliderComponent.expired());
	if (CColliderComponent::IsCollisionLayerOverlapped(_wpColliderComponent) == false) { return false; }

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

void CSphereColliderComponent::SetSphereColliderInfo(float _fRadius, int32 _iSlice, int32 _iStack)
{
	m_fRadius = _fRadius;
	m_iSlice = _iSlice;
	m_iStack = _iStack;
}
