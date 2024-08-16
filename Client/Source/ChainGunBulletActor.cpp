#include "pch.h"
#include "ChainGunBulletActor.h"

#include "RectangleMeshComponent.h"
#include "CubeColliderComponent.h"
#include "SoundComponent.h"

#include "CollisionManager.h"
#include "RenderManager.h"
#include "DeviceManager.h"

#include "ChainGunActor.h"
#include "Level.h"

using namespace std;

void CChainGunBulletActor::Initialize()
{
	m_eWeaponType = EWeaponType::CHAINGUN;
	m_iBulletNumber = 100;

	m_wpRectangleMeshComponent = CreateActorComponent<CRectangleMeshComponent>(L"RectangleMeshComponent");
	SetRootComponent(m_wpRectangleMeshComponent.lock());
	m_wpRectangleMeshComponent.lock()->SetRectangleMeshInfo(L"ChainGunBullet_", 0, 0);
	m_wpRectangleMeshComponent.lock()->SetComponentScale({ 10.f, 10.f, 10.f });
	CCollisionManager::GetInstance()->AddPrimitiveComponent(m_wpRectangleMeshComponent.lock());

	m_wpCubeColliderComponent = CreateActorComponent<CCubeColliderComponent>(L"CubeColliderComponent");
	m_wpCubeColliderComponent.lock()->SetOwnerComponent(m_wpRectangleMeshComponent);
	m_wpCubeColliderComponent.lock()->SetCollisionLayerType(ECollisionLayerType::ITEM);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::PLAYER);
	CCollisionManager::GetInstance()->AddColliderComponent(m_wpCubeColliderComponent.lock());

	CBulletActor::Initialize();
}

void CChainGunBulletActor::BeginPlay()
{
	CBulletActor::BeginPlay();
}

int32 CChainGunBulletActor::Update(const float& _fDeltaSeconds)
{
	return CBulletActor::Update(_fDeltaSeconds);
}

int32 CChainGunBulletActor::LateUpdate(const float& _fDeltaSeconds)
{
	if (m_bIsDead)
	{
		CRenderManager::GetInstance()->RemoveActor(m_eRenderType, dynamic_pointer_cast<CActor>(shared_from_this()));
		GetLevel().lock()->RemoveActor(GetActorName());
		return -1;
	}

	SetBillboard(m_wpRectangleMeshComponent);

	return CBulletActor::LateUpdate(_fDeltaSeconds);
}

void CChainGunBulletActor::Render()
{
	CBulletActor::Render();
}

void CChainGunBulletActor::EndPlay()
{
	CBulletActor::EndPlay();
}

void CChainGunBulletActor::Release()
{
	CBulletActor::Release();
}

int32 CChainGunBulletActor::OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	dynamic_pointer_cast<CChainGunActor>(GetLevel().lock()->FindActor(L"ChainGun"))->SetBulletHolding(m_iBulletNumber);
	m_wpSoundComponent.lock()->PlayPlayerSound("Get_Item", 100.f, ESoundType::ITEM);
	m_bIsDead = true;

	return 0;
}

void CChainGunBulletActor::OnCollisionStay(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
}

void CChainGunBulletActor::OnCollisionExit(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
}