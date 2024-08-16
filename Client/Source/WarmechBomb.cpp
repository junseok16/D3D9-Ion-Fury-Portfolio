#include "pch.h"
#include "WarmechBomb.h"

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
#include "EffectComponent.h"
#include "SoundComponent.h"

// Client
#include "PlayerActor.h"
using namespace std;

void CWarmechBomb::Initialize()
{
	SetActorScale({ 3.0f, 3.0f, 3.0f });

	InitializeAnimationComponent();

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

	// 이펙트 컴포넌트
	InitializeEffectComponent();
	InitializeSoundComponent();

	SetRenderType(ERenderType::ALPHA_TEST);
	SetMobility(EMobilityType::DYNAMIC);
	CProjectile::Initialize();
}

void CWarmechBomb::BeginPlay()
{
	m_wpAnimationComponent.lock()->AddState(L"Idle", 0, 13);
	m_wpAnimationComponent.lock()->SetCurrentState(L"Idle");

	m_fGravityConstant = m_wpPhysicsComponent.lock()->GetGravityValue();

	m_vBounceDirConstant = 2 * m_vDirection + 15.0f * FVector3(0.0f, 1.0f, 0.0f);
	m_vBounceDirConstant *= 8;
	m_vBounceDir = m_vBounceDirConstant;

	// 사운드 컴포넌트를 설정합니다.
	shared_ptr<CPlayerActor> spPlayer = dynamic_pointer_cast<CPlayerActor>(m_wpTarget.lock());
	m_wpSoundComponent.lock()->SetSoundComponentInfo(spPlayer->GetCurCamera(), EDistanceModel::Linear, 1.0f, 300.0f, 0.0f, 100.0f);
	CProjectile::BeginPlay();
}

int32 CWarmechBomb::Update(const float& _fDeltaSeconds)
{
	if (!m_bIsExploded)
	{
#pragma region 11.20 싼데비스탄을 위해 추가

		if (m_bIsTimeSlipped)
		{
			m_vTranslate += m_vBounceDir * _fDeltaSeconds / 50.0f;
			m_vBounceDir += FVector3(0, -78.4f, 0) * _fDeltaSeconds / 50.0f;
		}
		else
		{
			m_vTranslate += m_vBounceDir * _fDeltaSeconds;
			m_vBounceDir += FVector3(0, -78.4f, 0) * _fDeltaSeconds;
		}

#pragma endregion

		if (m_vTranslate.y <= 1.0f)
		{
			m_vBounceDir = m_vBounceDirConstant * 9 / 10;
		}
	}
	else
	{
		m_wpPhysicsComponent.lock()->SetGravityValue(0.0f);
	}

	return CProjectile::Update(_fDeltaSeconds);
}

int32 CWarmechBomb::LateUpdate(const float& _fDeltaSeconds)
{
	SetBillBoard(m_wpEffectComponent);
	return CProjectile::LateUpdate(_fDeltaSeconds);
}

void CWarmechBomb::Render()
{
	CProjectile::Render();
}

void CWarmechBomb::EndPlay()
{
	CProjectile::EndPlay();
}

void CWarmechBomb::Release()
{
	CProjectile::Release();
}

void CWarmechBomb::InitializeEffectComponent()
{
	m_wpEffectComponent = CreateActorComponent<CEffectComponent>(L"EffectComponent");
	m_wpEffectComponent.lock()->SetComponentScale({ 4.0f, 4.0f, 4.0f });
	m_wpEffectComponent.lock()->SettingAnimationInfo(L"Explosion0_0", 0, 31, L"Idle", EAnimationType::DESIGNATED_TIME, 1.0f);
	m_wpEffectComponent.lock()->AddState(L"Idle", 0, 0);
	m_wpEffectComponent.lock()->AddState(L"Explode", 0, 31);
	m_wpEffectComponent.lock()->SetIsAnimate(false);
	m_wpEffectComponent.lock()->SetIsRender(false);
	m_wpEffectComponent.lock()->SetAnimationCount(0);
	m_wpEffectComponent.lock()->SetFrame(0, 0, 0);
	SetRootComponent(m_wpEffectComponent.lock());
}

void CWarmechBomb::InitializeAnimationComponent()
{
	m_wpAnimationComponent = CreateActorComponent<CAnimationComponent>(L"AnimationComponent");
	m_wpAnimationComponent.lock()->SettingAnimationInfo(L"BlackBomb0_0", 0, 13, L"Idle", EAnimationType::LOOP, 1.0f);
	SetRootComponent(m_wpAnimationComponent);
}

void CWarmechBomb::InitializeSoundComponent()
{
	m_wpSoundComponent = CreateActorComponent<CSoundComponent>(L"SoundComponent");
}

int32 CWarmechBomb::OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	if (m_bIsExploded) { return 0; }

	if (_wpDstCollider.lock()->GetCollisionLayerType() == ECollisionLayerType::WALL)
	{
		m_wpSoundComponent.lock()->PlaySoundByDistance("mech_bomb_explosion", ESoundType::FIRE);

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
		m_wpSoundComponent.lock()->PlaySoundByDistance("mech_bomb_explosion", ESoundType::FIRE);

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
