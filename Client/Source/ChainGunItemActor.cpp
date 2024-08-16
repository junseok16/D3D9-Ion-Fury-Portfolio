#include "pch.h"
#include "ChainGunItemActor.h"

#include "RectangleMeshComponent.h"
#include "CubeColliderComponent.h"
#include "SoundComponent.h"

#include "CollisionManager.h"
#include "RenderManager.h"
#include "DeviceManager.h"

#include "PlayerActor.h"
#include "Level.h"
using namespace std;

void CChainGunItemActor::Initialize()
{
	m_eWeaponType = EWeaponType::CHAINGUN;

	m_wpRectangleMeshComponent = CreateActorComponent<CRectangleMeshComponent>(L"RectangleMeshComponent");
	SetRootComponent(m_wpRectangleMeshComponent.lock());
	m_wpRectangleMeshComponent.lock()->SetRectangleMeshInfo(L"Item_ChainGun_", 0, 0);
	CCollisionManager::GetInstance()->AddPrimitiveComponent(m_wpRectangleMeshComponent.lock());
	m_wpRectangleMeshComponent.lock()->SetComponentScale({ 20.f, 20.f, 20.f });

	m_wpCubeColliderComponent = CreateActorComponent<CCubeColliderComponent>(L"CubeColliderComponent");
	m_wpCubeColliderComponent.lock()->SetOwnerComponent(m_wpRectangleMeshComponent);
	m_wpCubeColliderComponent.lock()->SetCollisionLayerType(ECollisionLayerType::ITEM);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::PLAYER);
	CCollisionManager::GetInstance()->AddColliderComponent(m_wpCubeColliderComponent.lock());

	CWeaponItemActor::Initialize();
}

void CChainGunItemActor::BeginPlay()
{
	CWeaponItemActor::BeginPlay();
}

int32 CChainGunItemActor::Update(const float& _fDeltaSeconds)
{
	return CWeaponItemActor::Update(_fDeltaSeconds);
}

int32 CChainGunItemActor::LateUpdate(const float& _fDeltaSeconds)
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

void CChainGunItemActor::Render()
{
	CWeaponItemActor::Render();
}

void CChainGunItemActor::EndPlay()
{
	CWeaponItemActor::EndPlay();
}

void CChainGunItemActor::Release()
{
	CWeaponItemActor::Release();
}

int32 CChainGunItemActor::OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	dynamic_pointer_cast<CPlayerActor>(GetLevel().lock()->FindActor(L"Player"))->SetChainGunEnable();
	m_wpSoundComponent.lock()->PlayPlayerSound("Get_ChainGun", 100.f, ESoundType::ITEM);
	m_bIsDead = true;
	return 0;
}

void CChainGunItemActor::OnCollisionStay(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
}

void CChainGunItemActor::OnCollisionExit(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
}
