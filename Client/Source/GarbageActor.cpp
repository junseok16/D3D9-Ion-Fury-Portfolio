#include "pch.h"
#include "GarbageActor.h"

#include "RectangleMeshComponent.h"
#include "CubeColliderComponent.h"

#include "CollisionManager.h"
#include "RenderManager.h"
#include "DeviceManager.h"

#include "PlayerActor.h"
#include "Level.h"
using namespace std;

void CGarbageActor::Initialize()
{
	m_iHp = 2;

	m_wpRectangleMeshComponent = CreateActorComponent<CRectangleMeshComponent>(L"RectangleMeshComponent");
	SetRootComponent(m_wpRectangleMeshComponent.lock());
	m_wpRectangleMeshComponent.lock()->SetRectangleMeshInfo(L"Garbage_", 0, 2);
	m_wpRectangleMeshComponent.lock()->SetComponentScale({ 10.f, 12.f, 1.f });
	CCollisionManager::GetInstance()->AddPrimitiveComponent(m_wpRectangleMeshComponent.lock());

	m_wpCubeColliderComponent = CreateActorComponent<CCubeColliderComponent>(L"CubeColliderComponent");
	m_wpCubeColliderComponent.lock()->SetOwnerComponent(m_wpRectangleMeshComponent);
	m_wpCubeColliderComponent.lock()->SetCollisionLayerType(ECollisionLayerType::ITEMOBJECT);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::PLAYER);
	CCollisionManager::GetInstance()->AddColliderComponent(m_wpCubeColliderComponent.lock());

	CItemObjectActor::Initialize();
}

void CGarbageActor::BeginPlay()
{
	m_wpRectangleMeshComponent.lock()->SetTextureIndex(0);

	CItemObjectActor::BeginPlay();
}

int32 CGarbageActor::Update(const float& _fDeltaSeconds)
{
	if(!m_bConsumed)
	{
		HpInteract();
	}
	return CItemObjectActor::Update(_fDeltaSeconds);
}

int32 CGarbageActor::LateUpdate(const float& _fDeltaSeconds)
{
	SetBillboard(m_wpRectangleMeshComponent);

	return CItemObjectActor::LateUpdate(_fDeltaSeconds);
}

void CGarbageActor::Render()
{
	CItemObjectActor::Render();
}

void CGarbageActor::EndPlay()
{
	CItemObjectActor::EndPlay();
}

void CGarbageActor::Release()
{
	CItemObjectActor::Release();
}

int32 CGarbageActor::OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	return 0;
}

void CGarbageActor::OnCollisionStay(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
}

void CGarbageActor::OnCollisionExit(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
}

void CGarbageActor::HpInteract()
{
	switch (m_iHp)
	{
	case 0:
		m_wpRectangleMeshComponent.lock()->SetTextureIndex(2);
		CreateItem(m_iCapaType);
		m_bConsumed = true;
		break;

	case 1:
		m_wpRectangleMeshComponent.lock()->SetTextureIndex(1);
		break;

	case 2:
		m_wpRectangleMeshComponent.lock()->SetTextureIndex(0);
		break;

	default:
		break;
	}
}
