#include "pch.h"
#include "PenetratorActor.h"

#include "RenderManager.h"
#include "SoundManager.h"
#include "TimerManager.h"

#include "Level.h"
#include "Actor.h"
#include "PlayerActor.h"
#include "ItemObjectActor.h"
#include "AnimationComponent.h"
#include "SoundComponent.h"
#include "CubeColliderComponent.h"
using namespace std;

void CPenetratorActor::Initialize()
{
	m_eWeaponType = EWeaponType::PENETRATOR;

	m_iDamage = 15;
	m_iBulletLoaded = 40;
	m_iBulletHolding = 80;
	m_iMagazine = 40;
	m_iBulletMaximum = 320;

	m_vBasePosition = { 100.0f, -150.f, 5.0f };

	m_wpAnimationComponent = CreateActorComponent<CAnimationComponent>(L"AnimationComponent");
	m_wpAnimationComponent.lock()->SetIsRootComponent(true);
	m_wpAnimationComponent.lock()->SettingAnimationInfo(L"Penetrator_", 0, 26, L"Idle", EAnimationType::LOOP, 1.0f);

	m_wpAnimationComponent.lock()->SetComponentScale({ 6.0f, 6.0f, 6.0f });

	CWeaponActor::Initialize();
}

void CPenetratorActor::BeginPlay()
{
	m_wpAnimationComponent.lock()->AddState(L"Idle", 0, 0);
	m_wpAnimationComponent.lock()->AddState(L"Attack1", 1, 6);
	m_wpAnimationComponent.lock()->AddState(L"Reload", 7, 26);

	m_wpAnimationComponent.lock()->SetFrameTime(L"Attack1", 1, 6, 0.025f);

	CWeaponActor::BeginPlay();
}

int32 CPenetratorActor::Update(const float& _fDeltaSeconds)
{
	if(m_bEnable)
	{
		AnimationSetting();
		AutoReload();
	}
	return CWeaponActor::Update(_fDeltaSeconds);
}

int32 CPenetratorActor::LateUpdate(const float& _fDeltaSeconds)
{
	UpdateFSM();
	return CWeaponActor::LateUpdate(_fDeltaSeconds);
}

void CPenetratorActor::Render()
{
	CWeaponActor::Render();
}

void CPenetratorActor::EndPlay()
{
	CWeaponActor::EndPlay();
}

void CPenetratorActor::Release()
{
	CWeaponActor::Release();
}

void CPenetratorActor::SetFrameInteract(int32 OffFire)
{
	if (m_wpAnimationComponent.lock()->GetCurFrame() == OffFire)
	{
		if (m_bFrameButton)
		{
			m_wpSoundComponent.lock()->PlayPlayerSound("Penetrator_Fire", 100.f, ESoundType::EFFECT);

			m_iBulletLoaded -= 1;
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
	}
}

void CPenetratorActor::AnimationSetting()
{
	if (m_wpAnimationComponent.lock()->GetCurrentState() == L"Attack1")
	{
		m_wpAnimationComponent.lock()->SetAnimationType(EAnimationType::DESIGNATED_TIME);
		m_wpAnimationComponent.lock()->SetAnimationCount(1);
	}

	SetFrameInteract(2);

	if(m_iBulletLoaded > 0)
	{
		SetFrameInteract(5);
	}

	if (m_wpAnimationComponent.lock()->GetCurFrame() == 8)
	{
		if (m_bFrameButton)
		{
			m_wpSoundComponent.lock()->PlayPlayerSound("Penetrator_Reload", 100.f, ESoundType::EFFECT);
			m_bFrameButton = false;
		}
	}

	if (m_wpAnimationComponent.lock()->GetCurFrame() == 9)
	{
		m_bFrameButton = true;
	}

	if (m_wpAnimationComponent.lock()->GetCurFrame() == 20)
	{
		if (m_bFrameButton)
		{
			m_wpSoundComponent.lock()->PlayPlayerSound("Penetrator_Boltback", 100.f, ESoundType::EFFECT);
			m_bFrameButton = false;
		}
	}
	if (m_wpAnimationComponent.lock()->GetCurFrame() == 21)
	{
		m_bFrameButton = true;
	}

	if (m_wpAnimationComponent.lock()->GetCurFrame() == 26)
	{
		Reload();
		SetActivate(true);
	}
}

void CPenetratorActor::AutoReload()
{
	if (m_iBulletLoaded == 0 && m_iBulletHolding > 0 && m_wpAnimationComponent.lock()->GetCurrentState() == L"Idle")
	{
		m_wpAnimationComponent.lock()->SetCurrentState(L"Reload");
	}
}