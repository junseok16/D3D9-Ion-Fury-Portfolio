#include "pch.h"
#include "WarmechMissile.h"

// Framework
#include "Level.h"

// Manager
#include "TimerManager.h"
#include "CollisionManager.h"
#include "RenderManager.h"

// Component
#include "AnimationComponent.h"
#include "CubeColliderComponent.h"
#include "PhysicsComponent.h"
using namespace std;

void CWarmechMissile::Initialize()
{
	// 애니메이션 컴포넌트
	m_wpAnimationComponent = CreateActorComponent<CAnimationComponent>(L"AnimationComponent");
	m_wpAnimationComponent.lock()->SettingAnimationInfo(L"BlackBomb0_0", 0, 13, L"Idle", EAnimationType::LOOP, 1.0f);
	SetRootComponent(m_wpAnimationComponent);

	// 큐브 콜라이더 컴포넌트
	m_wpCubeColliderComponent = CreateActorComponent<CCubeColliderComponent>(L"CubeColliderComponent");
	m_wpCubeColliderComponent.lock()->SetCollisionLayerType(ECollisionLayerType::PROJECTILE);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::GROUND);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::WALL);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::PLAYER);
	m_wpCubeColliderComponent.lock()->SetOwnerComponent(m_wpAnimationComponent);
	CCollisionManager::GetInstance()->AddColliderComponent(m_wpCubeColliderComponent.lock());

	// 피직스 컴포넌트
	m_wpPhysicsComponent = CreateActorComponent<CPhysicsComponent>(L"PhysicsComponent");
	m_wpPhysicsComponent.lock()->SetGravityValue(39.8f);

	SetRenderType(ERenderType::ALPHA_TEST);
	SetMobility(EMobilityType::DYNAMIC);
	CProjectile::Initialize();
}

void CWarmechMissile::BeginPlay()
{
	m_wpAnimationComponent.lock()->AddState(L"Idle", 0, 5);
	m_wpAnimationComponent.lock()->SetCurrentState(L"Idle");

	m_wpTarget = GetLevel().lock()->FindActor(L"Player");
	m_fGravity = m_wpPhysicsComponent.lock()->GetGravityValue();
	CProjectile::BeginPlay();
}

int32 CWarmechMissile::Update(const float& _fDeltaSeconds)
{
	m_fSumFireSeconds += _fDeltaSeconds;
	m_fSpeed -= m_fGravity * powf(28 * _fDeltaSeconds, 2) * 0.5f;
	if (m_fSpeed <= 0.0f) { m_fSpeed = 0.0f; }

	float fDistance = 0.0f;

#pragma region 11.20 싼데비스탄을 위해 추가

	if (m_bIsTimeSlipped)
	{
		fDistance = 3 * m_fSpeed * _fDeltaSeconds / 50.0f;
	}
	else
	{
		fDistance = 3 * m_fSpeed * _fDeltaSeconds;
	}

#pragma endregion

	SetActorPosition(GetActorPosition() + fDistance * m_vDirection);

	return CProjectile::Update(_fDeltaSeconds);
}

int32 CWarmechMissile::LateUpdate(const float& _fDeltaSeconds)
{
	if (m_bIsDead)
	{
		CRenderManager::GetInstance()->RemoveActor(m_eRenderType, dynamic_pointer_cast<CActor>(shared_from_this()));
		GetLevel().lock()->RemoveActor(GetActorName());
		return -1;
	}
	return CProjectile::LateUpdate(_fDeltaSeconds);
}

void CWarmechMissile::Render()
{
	CProjectile::Render();
}

void CWarmechMissile::EndPlay()
{
	CProjectile::EndPlay();
}

void CWarmechMissile::Release()
{
	CProjectile::Release();
}

int32 CWarmechMissile::OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	if (_wpSrcCollider.lock()->GetCollisionLayerType() == ECollisionLayerType::PROJECTILE && _wpDstCollider.lock()->GetCollisionLayerType() == ECollisionLayerType::GROUND)
	{
		m_fSpeed = 50.0f;
		m_fSumFireSeconds = 0.0f;

		if (++m_iNumBounce >= 8) { m_bIsDead = true; }
	}

	if (_wpSrcCollider.lock()->GetCollisionLayerType() == ECollisionLayerType::PROJECTILE && _wpDstCollider.lock()->GetCollisionLayerType() == ECollisionLayerType::WALL)
	{
		m_bIsDead = true;
	}

	return 0;
}
