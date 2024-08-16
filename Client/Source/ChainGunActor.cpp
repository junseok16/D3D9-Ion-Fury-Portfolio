#include "pch.h"
#include "ChainGunActor.h"

#include "RenderManager.h"
#include "SoundManager.h"
#include "TimerManager.h"
#include "InputManager.h"

#include "Level.h"
#include "Actor.h"
#include "PlayerActor.h"
#include "ItemObjectActor.h"
#include "AnimationComponent.h"
#include "SoundComponent.h"
#include "CubeColliderComponent.h"
#include "ParticleComponent.h"
using namespace std;

void CChainGunActor::Initialize()
{
	m_eWeaponType = EWeaponType::CHAINGUN;

	m_iDamage = 20;
	m_iBulletHolding = 200;
	m_iBulletMaximum = 400;

	m_vBasePosition = { 200.0f, -150.0f, 5.0f };

	m_wpAnimationComponent = CreateActorComponent<CAnimationComponent>(L"AnimationComponent");
	m_wpAnimationComponent.lock()->SetIsRootComponent(true);
	m_wpAnimationComponent.lock()->SettingAnimationInfo(L"ChainGun_", 0, 14, L"Idle", EAnimationType::LOOP, 1.0f);

	m_wpAnimationComponent.lock()->SetComponentScale({ 6.0f, 6.0f, 6.0f });

	// 파티클 컴포넌트
	m_wpParticleComponent = CreateActorComponent<CParticleComponent>(L"ParticleComponent");
	SetRootComponent(m_wpParticleComponent);
	m_wpParticleComponent.lock()->SetIsRemove(true);
	m_wpParticleComponent.lock()->SetIsActive(false);
	m_wpParticleComponent.lock()->SetParticleMeshInfo(L"Bullet0_", 0, 0);
	m_wpParticleComponent.lock()->SetComponentLocalPosition({ 0.8f, -0.6f, -1.0f });
	m_wpParticleComponent.lock()->SetParticleInfo(EParticleType::ERUPTION, 1);
	m_wpParticleComponent.lock()->SetParticleSize(15.0f);
	m_wpParticleComponent.lock()->SetParticleLifeTime(5.0f);
	m_wpParticleComponent.lock()->SetParticleSpeed(3.0f);
	m_wpParticleComponent.lock()->SetParticleAcceleration(3.0f);
	m_wpParticleComponent.lock()->SetParticleCreateTime(0.0f);
	m_wpParticleComponent.lock()->SetParticleSpreadDegreeXZ(1.5f);
	m_wpParticleComponent.lock()->SetParticleSpreadDegreeY(3.0f);

	CWeaponActor::Initialize();
}

void CChainGunActor::BeginPlay()
{
	m_wpAnimationComponent.lock()->AddState(L"Idle", 0, 0);
	m_wpAnimationComponent.lock()->AddState(L"Preheat", 1, 7);
	m_wpAnimationComponent.lock()->AddState(L"Attack1", 8, 14);

	m_wpAnimationComponent.lock()->SetFrameTime(L"Attack1", 8, 14, 0.015f);
	CWeaponActor::BeginPlay();
}

int32 CChainGunActor::Update(const float& _fDeltaSeconds)
{
	if (m_bEnable)
	{
		SubAccel();
		AnimationSetting();
		Input();
	}

	return CWeaponActor::Update(_fDeltaSeconds);
}

int32 CChainGunActor::LateUpdate(const float& _fDeltaSeconds)
{
	UpdateFSM();
	return CWeaponActor::LateUpdate(_fDeltaSeconds);
}

void CChainGunActor::Render()
{
	CWeaponActor::Render();
}

void CChainGunActor::EndPlay()
{
	CWeaponActor::EndPlay();
}

void CChainGunActor::Release()
{
	CWeaponActor::Release();
}

void CChainGunActor::UpdateFSM()
{
	if (0 < m_wpAnimationComponent.lock()->GetCurrentAnimationCount())
	{
		if (L"Attack1" == m_wpAnimationComponent.lock()->GetCurrentState())
		{
			m_wpAnimationComponent.lock()->SetIsAnimate(true);
			SetActivate(true);
		}
	}
}

void CChainGunActor::SetFrameInteract(int32 OffFire)
{
	if (m_wpAnimationComponent.lock()->GetCurFrame() == OffFire)
	{
		if (m_bFrameButton)
		{
			// 공격 시 탄피 파티클 생성
			m_wpParticleComponent.lock()->SetIsActive(true);
			m_wpParticleComponent.lock()->AddParticle();

			m_wpSoundComponent.lock()->PlayPlayerSound("ChainGun_Fire", 100.f, ESoundType::EFFECT);
			SetActorPosition(m_vBasePosition + FVector3{ 0.f, -5.f, 0.f });
			m_iBulletHolding -= 1;
			m_bFrameButton = false;

			weak_ptr<CPlayerActor> wpPlayer = dynamic_pointer_cast<CPlayerActor>(GetLevel().lock()->FindActor(L"Player"));
			weak_ptr<CCubeColliderActor> wpHitedCubeActor = wpPlayer.lock()->HitScan();

			weak_ptr<CCreature> wpHitedCreature;
			weak_ptr<CItemObjectActor> wpHitedItemObjectActor;

			if (wpHitedCubeActor.expired())
				return;

			ECollisionLayerType eTargetCollisionLayer = wpHitedCubeActor.lock()->GetCubeColliderComponent().lock()->GetCollisionLayerType();

			switch (eTargetCollisionLayer)
			{
			case ECollisionLayerType::PLAYER:
			case ECollisionLayerType::GROUND:
			case ECollisionLayerType::WALL:
			case ECollisionLayerType::INTERACTION:
			case ECollisionLayerType::ITEM:
				break;
			case ECollisionLayerType::ITEMOBJECT:
				wpHitedItemObjectActor = dynamic_pointer_cast<CItemObjectActor>(wpHitedCubeActor.lock());
				wpHitedItemObjectActor.lock()->GetDamaged();
				break;
			case ECollisionLayerType::MONSTER:
				wpHitedCreature = dynamic_pointer_cast<CCreature>(wpHitedCubeActor.lock());
				wpHitedCreature.lock()->GetDamaged(GetDamage());
				break;

			default:
				break;
			}
		}
	}
	else if (m_wpAnimationComponent.lock()->GetCurFrame() == OffFire + 1)
	{
		m_bFrameButton = true;
		SetActorPosition(m_vBasePosition);
	}
}

void CChainGunActor::Input()		// 현재 체인건만 마우스로 인풋 받게 해둠. 나중에 바꿀때 유의해야함
{
	float fInnerDeltaSeconds = CTimerManager::GetInstance()->GetDeltaSeconds(L"TimerInner");

	if(CInputManager::GetInstance()->IsMousePressed(EMouseButtonType::LEFT_BUTTON) && m_iBulletHolding > 0)
	{
		m_bShoot = true;
		m_fAccel += fInnerDeltaSeconds * 3.f;
	}

	if (CInputManager::GetInstance()->IsMouseUp(EMouseButtonType::LEFT_BUTTON))
	{
		m_bShoot = false;
	}
}

void CChainGunActor::SubAccel()
{
	float fInnerDeltaSeconds = CTimerManager::GetInstance()->GetDeltaSeconds(L"TimerInner");

	if(!m_bShoot)
	{
		m_fAccel -= fInnerDeltaSeconds;
	}

	if (m_fAccel < 0.f)
	{
		m_fAccel = 0.f;
	}
}

void CChainGunActor::AnimationSetting()
{
	m_wpAnimationComponent.lock()->SetFrameTime(L"Preheat", 1, 7, 0.03f / m_fAccel);

	if (m_fAccel > 0.f)
	{
		if (m_fAccel < 3.0f)
		{
			m_wpAnimationComponent.lock()->SetCurrentState(L"Preheat");

		}
		else if (m_fAccel >= 3.0f)
		{
			m_fAccel = 3.0f;
			m_wpAnimationComponent.lock()->SetCurrentState(L"Attack1");

			SetFrameInteract(8);
			SetFrameInteract(12);
		}
	}
}
