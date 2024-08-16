#include "pch.h"
#include "BossTrigger.h"

// Framework
#include "Level.h"

// Player
#include "PlayerActor.h"

// Boss
#include "WarmechLeg.h"
#include "WarmechHead.h"
#include "Skinjob.h"

// Manager
#include "CollisionManager.h"

// Component
#include "CubeColliderComponent.h"
#include "PhysicsComponent.h"
#include "SoundComponent.h"
using namespace std;

void CBossTrigger::Initialize()
{
	// 큐브 콜라이더 컴포넌트
	m_wpCubeColliderComponent = CreateActorComponent<CCubeColliderComponent>(L"CubeColliderComponent");
	m_wpCubeColliderComponent.lock()->SetCollisionLayerType(ECollisionLayerType::INTERACTION);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::PLAYER);
	SetRootComponent(m_wpCubeColliderComponent);

	CCollisionManager::GetInstance()->AddColliderComponent(m_wpCubeColliderComponent.lock());
	CCubeColliderActor::Initialize();
}

void CBossTrigger::BeginPlay()
{
	m_wpPlayer = dynamic_pointer_cast<CPlayerActor>(GetLevel().lock()->FindActor(L"Player"));
	CCubeColliderActor::BeginPlay();
}

int32 CBossTrigger::Update(const float& _fDeltaSeconds)
{
	return CCubeColliderActor::Update(_fDeltaSeconds);
}

int32 CBossTrigger::LateUpdate(const float& _fDeltaSeconds)
{
	return CCubeColliderActor::LateUpdate(_fDeltaSeconds);
}

void CBossTrigger::Render()
{
	CCubeColliderActor::Render();
}

void CBossTrigger::EndPlay()
{
	CCubeColliderActor::EndPlay();
}

void CBossTrigger::Release()
{
	CCubeColliderActor::Release();
}

int32 CBossTrigger::OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	if (!m_bIsTriggered)
	{
		if (L"WarmechTrigger" == m_wstrActorName)
		{
			m_wpWarmechLeg.lock()->GetPhysicsComponent().lock()->SetGravityValue(78.4f);
			m_wpWarmechLeg.lock()->SetMonsterPhase((int32)EWarmechPhase::PHASE_0);
			m_wpWarmechLeg.lock()->SetMonsterState(((int32)EWarmechLegState::FALL_FROM_SKY));

			m_wpWarmechHead.lock()->SetMonsterPhase((int32)EWarmechPhase::PHASE_0);
			m_wpWarmechHead.lock()->SetMonsterState((int32)EWarmechHeadState::IDLE);
			
			m_wpPlayer.lock()->GetSoundComponent().lock()->PlaySoundByDistance("mech_siren_loop", ESoundType::WARNING);
		}

		if (L"SkinjobTrigger" == m_wstrActorName)
		{

		}
		m_bIsTriggered = true;
	}
	return 0;
}
