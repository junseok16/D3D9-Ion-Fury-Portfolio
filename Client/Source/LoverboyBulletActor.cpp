#include "pch.h"
#include "LoverboyBulletActor.h"

#include "RectangleMeshComponent.h"
#include "CubeColliderComponent.h"
#include "SoundComponent.h"

#include "CollisionManager.h"
#include "RenderManager.h"
#include "DeviceManager.h"

#include "LoverboyActor.h"
#include "Level.h"

using namespace std;

void CLoverboyBulletActor::Initialize()
{
	m_eWeaponType = EWeaponType::LOVERBOY;
	m_iBulletNumber = 6 * (iCapaType + 1);
												
	m_wpRectangleMeshComponent = CreateActorComponent<CRectangleMeshComponent>(L"RectangleMeshComponent");
	SetRootComponent(m_wpRectangleMeshComponent.lock());
	m_wpRectangleMeshComponent.lock()->SetRectangleMeshInfo(L"LoverboyBullet_", 0, 1);
	m_wpRectangleMeshComponent.lock()->SetComponentScale({ 10.f, 10.f, 10.f });
	CCollisionManager::GetInstance()->AddPrimitiveComponent(m_wpRectangleMeshComponent.lock());

	m_wpCubeColliderComponent = CreateActorComponent<CCubeColliderComponent>(L"CubeColliderComponent");
	m_wpCubeColliderComponent.lock()->SetOwnerComponent(m_wpRectangleMeshComponent);
	m_wpCubeColliderComponent.lock()->SetCollisionLayerType(ECollisionLayerType::ITEM);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::PLAYER);
	CCollisionManager::GetInstance()->AddColliderComponent(m_wpCubeColliderComponent.lock());

	CBulletActor::Initialize();
}

void CLoverboyBulletActor::BeginPlay()
{
	switch (iCapaType)
	{
	case 0:
		m_wpRectangleMeshComponent.lock()->SetTextureIndex(0);
		break;

	case 1:
		m_wpRectangleMeshComponent.lock()->SetTextureIndex(1);
		break;
	}
	CBulletActor::BeginPlay();
}

int32 CLoverboyBulletActor::Update(const float& _fDeltaSeconds)
{
	return CBulletActor::Update(_fDeltaSeconds);
}

int32 CLoverboyBulletActor::LateUpdate(const float& _fDeltaSeconds)
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

void CLoverboyBulletActor::Render()
{
	CBulletActor::Render();
}

void CLoverboyBulletActor::EndPlay()
{
	CBulletActor::EndPlay();
}

void CLoverboyBulletActor::Release()
{
	CBulletActor::Release();
}

int32 CLoverboyBulletActor::OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	dynamic_pointer_cast<CLoverboyActor>(GetLevel().lock()->FindActor(L"Loverboy"))->SetBulletHolding(m_iBulletNumber);
	m_wpSoundComponent.lock()->PlayPlayerSound("Get_Item", 100.f, ESoundType::ITEM);
	m_bIsDead = true;

	return 0;
}

void CLoverboyBulletActor::OnCollisionStay(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
}

void CLoverboyBulletActor::OnCollisionExit(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
}