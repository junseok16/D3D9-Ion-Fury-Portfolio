#include "pch.h"
#include "WarmechBullet.h"

// Framework
#include "Level.h"

// Manager
#include "TimerManager.h"
#include "CollisionManager.h"
#include "RenderManager.h"

// Component
#include "AnimationComponent.h"
#include "CubeColliderComponent.h"
#include "EffectComponent.h"
#include "SoundComponent.h"

// Client
#include "PlayerActor.h"
#include "Stage3.h"
using namespace std;

void CWarmechBullet::Initialize()
{
	SetActorScale({ 7.0f, 7.0f, 7.0f });

	// 애니메이션 컴포넌트
	m_wpAnimationComponent = CreateActorComponent<CAnimationComponent>(L"AnimationComponent");
	m_wpAnimationComponent.lock()->SettingAnimationInfo(L"FireEnergyBall0_", 0, 5, L"Idle", EAnimationType::LOOP, 1.0f);
	SetRootComponent(m_wpAnimationComponent);

	// 큐브 콜라이더 컴포넌트
	m_wpCubeColliderComponent = CreateActorComponent<CCubeColliderComponent>(L"CubeColliderComponent");
	m_wpCubeColliderComponent.lock()->SetCollisionLayerType(ECollisionLayerType::PROJECTILE);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::GROUND);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::WALL);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::PLAYER);
	m_wpCubeColliderComponent.lock()->SetOwnerComponent(m_wpAnimationComponent);
	CCollisionManager::GetInstance()->AddColliderComponent(m_wpCubeColliderComponent.lock());

	// 이펙트 컴포넌트
	m_wpEffectComponent = CreateActorComponent<CEffectComponent>(L"EffectComponent");
	m_wpEffectComponent.lock()->SetComponentScale({ 4.0f, 4.0f, 4.0f });
	m_wpEffectComponent.lock()->SettingAnimationInfo(L"FireEnergyBall1_0", 0, 5, L"Idle", EAnimationType::DESIGNATED_TIME, 1.0f);
	m_wpEffectComponent.lock()->AddState(L"Idle", 0, 0);
	m_wpEffectComponent.lock()->AddState(L"Explode", 0, 5);
	m_wpEffectComponent.lock()->SetIsAnimate(false);
	m_wpEffectComponent.lock()->SetIsRender(false);
	m_wpEffectComponent.lock()->SetAnimationCount(0);
	m_wpEffectComponent.lock()->SetFrame(0, 0, 0);
	SetRootComponent(m_wpEffectComponent.lock());

	InitializeSoundComponent();
	SetRenderType(ERenderType::ALPHA_TEST);
	SetMobility(EMobilityType::DYNAMIC);
	CProjectile::Initialize();
}

void CWarmechBullet::BeginPlay()
{
	m_wpAnimationComponent.lock()->AddState(L"Idle", 0, 5);
	m_wpAnimationComponent.lock()->SetCurrentState(L"Idle");

	m_vDirection = m_wpTarget.lock()->GetActorWorldPosition() - GetActorPosition();
	D3DXVec3Normalize(&m_vDirection, &m_vDirection);

	// 사운드 컴포넌트를 설정합니다.
	shared_ptr<CPlayerActor> spPlayer = dynamic_pointer_cast<CPlayerActor>(m_wpTarget.lock());
	m_wpSoundComponent.lock()->SetSoundComponentInfo(spPlayer->GetCurCamera(), EDistanceModel::Linear, 1.0f, 300.0f, 0.0f, 100.0f);

	CProjectile::BeginPlay();
}

int32 CWarmechBullet::Update(const float& _fDeltaSeconds)
{
	if (!m_bIsExploded)
	{
		// 11.20 싼데비스탄을 위해 추가
		if (m_bIsTimeSlipped)
		{
			SetActorPosition(GetActorPosition() + m_vDirection * m_fSpeed * _fDeltaSeconds / 50.0f);
		}
		else
		{
			SetActorPosition(GetActorPosition() + m_vDirection * m_fSpeed * _fDeltaSeconds);
		}
	}
	return CProjectile::Update(_fDeltaSeconds);
}

int32 CWarmechBullet::LateUpdate(const float& _fDeltaSeconds)
{/*
	if (m_bIsDead)
	{
		CRenderManager::GetInstance()->RemoveActor(m_eRenderType, dynamic_pointer_cast<CActor>(shared_from_this()));
		GetLevel().lock()->RemoveActor(GetActorName());
		return -1;
	}*/

	SetBillBoard(m_wpEffectComponent);
	return CProjectile::LateUpdate(_fDeltaSeconds);
}

void CWarmechBullet::Render()
{
	CProjectile::Render();
}

void CWarmechBullet::EndPlay()
{
	CProjectile::EndPlay();
}

void CWarmechBullet::Release()
{
	CProjectile::Release();
}

void CWarmechBullet::InitializeSoundComponent()
{
	m_wpSoundComponent = CreateActorComponent<CSoundComponent>(L"SoundComponent");
}

int32 CWarmechBullet::OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	if (m_bIsExploded) { return 0; }

	if (_wpDstCollider.lock()->GetCollisionLayerType() == ECollisionLayerType::GROUND ||
		_wpDstCollider.lock()->GetCollisionLayerType() == ECollisionLayerType::WALL)
	{
		m_wpSoundComponent.lock()->PlaySoundByDistance("mech_gun_explosion", ESoundType::FIRE);

		m_wpAnimationComponent.lock()->SetIsAnimate(false);
		m_wpAnimationComponent.lock()->SetIsRender(false);

		m_wpEffectComponent.lock()->SetIsAnimate(true);
		m_wpEffectComponent.lock()->SetIsRender(true);
		m_wpEffectComponent.lock()->SetCurrentAnimationCount(0);
		m_wpEffectComponent.lock()->SetFrame(0, 0, m_wpEffectComponent.lock()->GetFileEndIndex());
		m_wpEffectComponent.lock()->SetCurrentState(L"Explode");
		m_bIsExploded = true;
	}

	if (_wpDstCollider.lock()->GetCollisionLayerType() == ECollisionLayerType::PLAYER)
	{
		m_wpSoundComponent.lock()->PlaySoundByDistance("mech_gun_explosion", ESoundType::FIRE);

		m_wpAnimationComponent.lock()->SetIsAnimate(false);
		m_wpAnimationComponent.lock()->SetIsRender(false);

		m_wpEffectComponent.lock()->SetIsAnimate(true);
		m_wpEffectComponent.lock()->SetIsRender(true);
		m_wpEffectComponent.lock()->SetCurrentAnimationCount(0);
		m_wpEffectComponent.lock()->SetFrame(0, 0, m_wpEffectComponent.lock()->GetFileEndIndex());
		m_wpEffectComponent.lock()->SetCurrentState(L"Explode");
		m_bIsExploded = true;

		dynamic_pointer_cast<CPlayerActor>(m_wpTarget.lock())->GetDamaged(m_fDamage);
	}

	return 0;
}
