#include "pch.h"
#include "PenetratorItemActor.h"

#include "RectangleMeshComponent.h"
#include "CubeColliderComponent.h"
#include "SoundComponent.h"

#include "CollisionManager.h"
#include "RenderManager.h"
#include "DeviceManager.h"

#include "PlayerActor.h"
#include "Level.h"
using namespace std;

void CPenetratorItemActor::Initialize()
{
	m_eWeaponType = EWeaponType::PENETRATOR;

	m_wpRectangleMeshComponent = CreateActorComponent<CRectangleMeshComponent>(L"RectangleMeshComponent");
	SetRootComponent(m_wpRectangleMeshComponent.lock());
	m_wpRectangleMeshComponent.lock()->SetRectangleMeshInfo(L"Item_Penetrator_", 0, 0);
	CCollisionManager::GetInstance()->AddPrimitiveComponent(m_wpRectangleMeshComponent.lock());
	m_wpRectangleMeshComponent.lock()->SetComponentScale({ 10.f, 10.f, 10.f });

	m_wpCubeColliderComponent = CreateActorComponent<CCubeColliderComponent>(L"CubeColliderComponent");
	m_wpCubeColliderComponent.lock()->SetOwnerComponent(m_wpRectangleMeshComponent);
	m_wpCubeColliderComponent.lock()->SetCollisionLayerType(ECollisionLayerType::ITEM);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::PLAYER);
	CCollisionManager::GetInstance()->AddColliderComponent(m_wpCubeColliderComponent.lock());

	CWeaponItemActor::Initialize();
}

void CPenetratorItemActor::BeginPlay()
{
	CWeaponItemActor::BeginPlay();
}

int32 CPenetratorItemActor::Update(const float& _fDeltaSeconds)
{
	return CWeaponItemActor::Update(_fDeltaSeconds);
}

int32 CPenetratorItemActor::LateUpdate(const float& _fDeltaSeconds)
{
	if (m_bIsDead)
	{
		CRenderManager::GetInstance()->RemoveActor(m_eRenderType, dynamic_pointer_cast<CActor>(shared_from_this()));
		GetLevel().lock()->RemoveActor(GetActorName());
		return -1;
	}

	SetBillboard(m_wpRectangleMeshComponent);

	return CWeaponItemActor::LateUpdate(_fDeltaSeconds);
}

void CPenetratorItemActor::Render()
{
	CWeaponItemActor::Render();
}

void CPenetratorItemActor::EndPlay()
{
	CWeaponItemActor::EndPlay();
}

void CPenetratorItemActor::Release()
{
	CWeaponItemActor::Release();
}

int32 CPenetratorItemActor::OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	dynamic_pointer_cast<CPlayerActor>(GetLevel().lock()->FindActor(L"Player"))->SetPenetratorEnable();
	m_wpSoundComponent.lock()->PlayPlayerSound("Get_Penetrator", 100.f, ESoundType::ITEM);
	m_bIsDead = true;
	return 0;
}

void CPenetratorItemActor::OnCollisionStay(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
}

void CPenetratorItemActor::OnCollisionExit(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
}