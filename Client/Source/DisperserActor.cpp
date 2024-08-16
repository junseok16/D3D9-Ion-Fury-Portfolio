#include "pch.h"
#include "DisperserActor.h"

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

void CDisperserActor::Initialize()
{
	m_eWeaponType = EWeaponType::DISPERSER;

	m_iDamage = 80;
	m_iBulletLoaded = 6;
	m_iBulletHolding = 18;
	m_iMagazine = 6;
	m_iBulletMaximum = 48;

	m_vBasePosition = { 100.0f, -100.f, 5.0f };

	m_wpAnimationComponent = CreateActorComponent<CAnimationComponent>(L"AnimationComponent");
	m_wpAnimationComponent.lock()->SetIsRootComponent(true);
	m_wpAnimationComponent.lock()->SettingAnimationInfo(L"Disperser_", 0, 38, L"Idle", EAnimationType::LOOP, 0.5f);
	m_wpAnimationComponent.lock()->SetComponentScale({ 6.0f, 6.0f, 6.0f });

	CWeaponActor::Initialize();
}

void CDisperserActor::BeginPlay()
{
	m_wpAnimationComponent.lock()->AddState(L"Idle", 0, 0);
	m_wpAnimationComponent.lock()->AddState(L"Attack1", 1, 12);
	m_wpAnimationComponent.lock()->AddState(L"Reload", 13, 38);

	m_wpAnimationComponent.lock()->SetFrameTime(L"Attack1", 1, 1, 0.05f);
	m_wpAnimationComponent.lock()->SetFrameTime(L"Attack1", 2, 12, 0.03f);
	m_wpAnimationComponent.lock()->SetFrameTime(L"Reload", 13, 38, 0.03f);
	m_wpAnimationComponent.lock()->SetFrameTime(L"Reload", 26, 26, 0.2f);
	CWeaponActor::BeginPlay();
}

int32 CDisperserActor::Update(const float& _fDeltaSeconds)
{
	if (m_bEnable)
	{
		AnimationSetting();
		AutoReload();
	}

	return CWeaponActor::Update(_fDeltaSeconds);
}

int32 CDisperserActor::LateUpdate(const float& _fDeltaSeconds)
{
	CWeaponActor::UpdateFSM();
	return CWeaponActor::LateUpdate(_fDeltaSeconds);
}

void CDisperserActor::Render()
{
	CWeaponActor::Render();
}

void CDisperserActor::EndPlay()
{
	CWeaponActor::EndPlay();
}

void CDisperserActor::Release()
{
	CWeaponActor::Release();
}

void CDisperserActor::SetFrameInteract(int32 OffFire)
{
	if (m_wpAnimationComponent.lock()->GetCurFrame() == OffFire)
	{
		if (m_bFrameButton)
		{
			m_wpSoundComponent.lock()->PlayPlayerSound("Disperser_Fire", 100.f, ESoundType::EFFECT);

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

void CDisperserActor::AnimationSetting()
{
	if (m_wpAnimationComponent.lock()->GetCurrentState() == L"Attack1")
	{
		m_wpAnimationComponent.lock()->SetAnimationType(EAnimationType::DESIGNATED_TIME);
		m_wpAnimationComponent.lock()->SetAnimationCount(1);
	}

	SetFrameInteract(2);

	if (m_wpAnimationComponent.lock()->GetCurFrame() == 6)
	{
		if (m_bFrameButton)
		{
			m_wpSoundComponent.lock()->PlayPlayerSound("Disperser_Boltback", 100.f, ESoundType::EFFECT);
			m_bFrameButton = false;
		}
	}

	if (m_wpAnimationComponent.lock()->GetCurFrame() == 7)
	{
		m_bFrameButton = true;
	}

	if (m_wpAnimationComponent.lock()->GetCurFrame() == 18)
	{
		if (m_bFrameButton)
		{
			m_wpSoundComponent.lock()->PlayPlayerSound("Disperser_Eject", 100.f, ESoundType::EFFECT);
			m_bFrameButton = false;
		}
	}

	if (m_wpAnimationComponent.lock()->GetCurFrame() == 19)
	{
		m_bFrameButton = true;
	}

	if (m_wpAnimationComponent.lock()->GetCurFrame() == 25)
	{
		if (m_bFrameButton)
		{
			m_wpSoundComponent.lock()->PlayPlayerSound("Disperser_Insert", 100.f, ESoundType::EFFECT);
			m_bFrameButton = false;
		}
	}

	if (m_wpAnimationComponent.lock()->GetCurFrame() == 26)
	{
		m_bFrameButton = true;
	}

	if (m_wpAnimationComponent.lock()->GetCurFrame() == 38)
	{
		Reload();
		SetActivate(true);
	}
}

void CDisperserActor::AutoReload()
{
	if (m_iBulletLoaded == 0 && m_iBulletHolding > 0 && m_wpAnimationComponent.lock()->GetCurFrame() == 5)
	{
		m_wpAnimationComponent.lock()->SetCurrentState(L"Reload");
	}
}