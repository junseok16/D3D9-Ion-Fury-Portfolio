#include "pch.h"
#include "PlaneActor.h"
#include "RectangleMeshComponent.h"
#include "RectColliderComponent.h"

#include "DeviceManager.h"
#include "CollisionManager.h"
#include "RenderManager.h"
#include "DeviceManager.h"
using namespace std;

void CPlaneActor::Initialize()
{
	// �簢�� ������Ʈ
	m_wpRectangleMeshComponent = CreateActorComponent<CRectangleMeshComponent>(L"RectangleMeshComponent");
	SetRootComponent(m_wpRectangleMeshComponent.lock());
	m_wpRectangleMeshComponent.lock()->SetRectangleMeshInfo(L"../Resource/Texture/Player/PlayerSprite/Foward/Walk/Player_Walk_", 3, 3);
	
	// �ݶ��̴� ������Ʈ
	m_wpRectColliderComponent = CreateActorComponent<CRectColliderComponent>(L"RectColliderComponent");
	m_wpRectColliderComponent.lock()->SetOwnerComponent(m_wpRectangleMeshComponent);
	m_wpRectColliderComponent.lock()->SetCollisionLayerType(ECollisionLayerType::PLAYER);
	m_wpRectColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::MONSTER);
	CCollisionManager::GetInstance()->AddColliderComponent(m_wpRectColliderComponent.lock());
	
	SetRenderType(ERenderType::NON_ALPHA);
	CActor::Initialize();
}

void CPlaneActor::BeginPlay()
{
	CActor::BeginPlay();
}

int32 CPlaneActor::Update(const float& _fDeltaSeconds)
{
	return CActor::Update(_fDeltaSeconds);
}

int32 CPlaneActor::LateUpdate(const float& _fDeltaSeconds)
{
	return CActor::LateUpdate(_fDeltaSeconds);
}

void CPlaneActor::Render()
{
	// �׽�Ʈ�� (���� ���� ���ؼ�), �ĸ� �߷����� ������
	CDeviceManager::GetInstance()->GetDirect3DDevice9()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	CActor::Render();
	CDeviceManager::GetInstance()->GetDirect3DDevice9()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void CPlaneActor::EndPlay()
{
	CActor::EndPlay();
}

void CPlaneActor::Release()
{
	CActor::Release();
}
