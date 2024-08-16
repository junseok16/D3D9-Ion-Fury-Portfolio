#include "pch.h"
#include "Creature.h"

#include "TimerManager.h"
#include "RenderManager.h"

#include "Level.h"

#include "AnimationComponent.h"

void CCreature::Initialize()
{
	CCubeColliderActor::Initialize();
}

void CCreature::BeginPlay()
{
	CCubeColliderActor::BeginPlay();
}

int32 CCreature::Update(const float& _fDeltaSeconds)
{
	return CCubeColliderActor::Update(_fDeltaSeconds);
}

int32 CCreature::LateUpdate(const float& _fDeltaSeconds)
{
	return CCubeColliderActor::LateUpdate(_fDeltaSeconds);
}

void CCreature::Render()
{
	CCubeColliderActor::Render();
}

void CCreature::EndPlay()
{
	CCubeColliderActor::EndPlay();
}

void CCreature::Release()
{
	CCubeColliderActor::Release();
}

void CCreature::AnimationSetting()
{
}

void CCreature::ColliderSetting()
{
}

void CCreature::PhysicsSetting()
{
}

void CCreature::ParticleSetting()
{
}

void CCreature::SoundSetting()
{
}

void CCreature::GetDamaged(const float& _fDamage)
{
	if (m_fCurHp > _fDamage)
	{
		m_fCurHp -= _fDamage;
		return;
	}

	m_fCurHp = 0.0f;
	CRenderManager::GetInstance()->RemoveActor(m_eRenderType, dynamic_pointer_cast<CActor>(shared_from_this()));
	GetLevel().lock()->RemoveActor(GetActorName());
}

int32 CCreature::DeadCheck(const float& _fDeltaSeconds)
{
	if (L"Dead" == m_wpAnimationComponent.lock()->GetCurrentState())
	{
		m_fDeadTime += _fDeltaSeconds;

		if (m_fDeadTime >= 1.0f)
		{
			CRenderManager::GetInstance()->RemoveActor(m_eRenderType, dynamic_pointer_cast<CActor>(shared_from_this()));
			GetLevel().lock()->RemoveActor(GetActorName());
			return 1;
		}
	}
	return 0;
}
