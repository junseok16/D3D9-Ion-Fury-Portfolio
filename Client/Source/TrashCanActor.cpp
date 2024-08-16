#include "pch.h"
#include "TrashCanActor.h"

#include "RectangleMeshComponent.h"
#include "CubeColliderComponent.h"

#include "CollisionManager.h"
#include "RenderManager.h"
#include "DeviceManager.h"

#include "PlayerActor.h"
#include "Level.h"

using namespace std;

void CTrashCanActor::Initialize()
{
	m_iHp = 1;

	m_wpRectangleMeshComponent = CreateActorComponent<CRectangleMeshComponent>(L"RectangleMeshComponent");
	SetRootComponent(m_wpRectangleMeshComponent.lock());
	m_wpRectangleMeshComponent.lock()->SetRectangleMeshInfo(L"TrashCan_", 0, 1);
	m_wpRectangleMeshComponent.lock()->SetComponentScale({ 8.f, 14.f, 1.f });
	CCollisionManager::GetInstance()->AddPrimitiveComponent(m_wpRectangleMeshComponent.lock());

	m_wpCubeColliderComponent = CreateActorComponent<CCubeColliderComponent>(L"CubeColliderComponent");
	m_wpCubeColliderComponent.lock()->SetOwnerComponent(m_wpRectangleMeshComponent);
	m_wpCubeColliderComponent.lock()->SetCollisionLayerType(ECollisionLayerType::ITEMOBJECT);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::PLAYER);
	CCollisionManager::GetInstance()->AddColliderComponent(m_wpCubeColliderComponent.lock());

	CItemObjectActor::Initialize();
}

void CTrashCanActor::BeginPlay()
{
	m_wpRectangleMeshComponent.lock()->SetTextureIndex(0);

	CItemObjectActor::BeginPlay();
}

int32 CTrashCanActor::Update(const float& _fDeltaSeconds)
{
	if (!m_bConsumed)
	{
		HpInteract();
	}
	return CItemObjectActor::Update(_fDeltaSeconds);
}

int32 CTrashCanActor::LateUpdate(const float& _fDeltaSeconds)
{
	SetBillboard(m_wpRectangleMeshComponent);

	return CItemObjectActor::LateUpdate(_fDeltaSeconds);
}

void CTrashCanActor::Render()
{
	CItemObjectActor::Render();
}

void CTrashCanActor::EndPlay()
{
	CItemObjectActor::EndPlay();
}

void CTrashCanActor::Release()
{
	CItemObjectActor::Release();
}

int32 CTrashCanActor::OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	return 0;
}

void CTrashCanActor::OnCollisionStay(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
}

void CTrashCanActor::OnCollisionExit(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
}

void CTrashCanActor::HpInteract()
{
	switch (m_iHp)
	{
	case 0:
		m_wpRectangleMeshComponent.lock()->SetTextureIndex(1);
		CreateItem(m_iCapaType);
		m_bConsumed = true;
		break;
	case 1:
		m_wpRectangleMeshComponent.lock()->SetTextureIndex(0);
		break;
	default:
		break;
	}
}
