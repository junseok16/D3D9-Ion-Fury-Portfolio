#include "pch.h"
#include "PenetratorBulletActor.h"

#include "RectangleMeshComponent.h"
#include "CubeColliderComponent.h"
#include "SoundComponent.h"

#include "CollisionManager.h"
#include "RenderManager.h"
#include "DeviceManager.h"

#include "PenetratorActor.h"
#include "Level.h"

using namespace std;

void CPenetratorBulletActor::Initialize()
{
	m_eWeaponType = EWeaponType::PENETRATOR;
	m_iBulletNumber = 40;

	m_wpRectangleMeshComponent = CreateActorComponent<CRectangleMeshComponent>(L"RectangleMeshComponent");
	SetRootComponent(m_wpRectangleMeshComponent.lock());
	m_wpRectangleMeshComponent.lock()->SetRectangleMeshInfo(L"PenetratorBullet_", 0, 0);
	m_wpRectangleMeshComponent.lock()->SetComponentScale({ 10.f, 10.f, 10.f });
	CCollisionManager::GetInstance()->AddPrimitiveComponent(m_wpRectangleMeshComponent.lock());

	m_wpCubeColliderComponent = CreateActorComponent<CCubeColliderComponent>(L"CubeColliderComponent");
	m_wpCubeColliderComponent.lock()->SetOwnerComponent(m_wpRectangleMeshComponent);
	m_wpCubeColliderComponent.lock()->SetCollisionLayerType(ECollisionLayerType::ITEM);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::PLAYER);
	CCollisionManager::GetInstance()->AddColliderComponent(m_wpCubeColliderComponent.lock());

	CBulletActor::Initialize();
}

void CPenetratorBulletActor::BeginPlay()
{
	CBulletActor::BeginPlay();
}

int32 CPenetratorBulletActor::Update(const float& _fDeltaSeconds)
{
	return CBulletActor::Update(_fDeltaSeconds);
}

int32 CPenetratorBulletActor::LateUpdate(const float& _fDeltaSeconds)
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

void CPenetratorBulletActor::Render()
{
	CBulletActor::Render();
}

void CPenetratorBulletActor::EndPlay()
{
	CBulletActor::EndPlay();
}

void CPenetratorBulletActor::Release()
{
	CBulletActor::Release();
}

int32 CPenetratorBulletActor::OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	dynamic_pointer_cast<CPenetratorActor>(GetLevel().lock()->FindActor(L"Penetrator"))->SetBulletHolding(m_iBulletNumber);
	m_wpSoundComponent.lock()->PlayPlayerSound("Get_Item", 100.f, ESoundType::ITEM);
	m_bIsDead = true;

	return 0;
}

void CPenetratorBulletActor::OnCollisionStay(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
}

void CPenetratorBulletActor::OnCollisionExit(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
}