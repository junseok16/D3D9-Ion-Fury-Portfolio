#include "pch.h"
#include "PhysicsComponent.h"

#include "TimerManager.h"

#include "Actor.h"
#include "Creature.h"

void CPhysicsComponent::Initialize()
{
	CActorComponent::Initialize();
}

void CPhysicsComponent::BeginPlay()
{
	CActorComponent::BeginPlay();
}

int32 CPhysicsComponent::Update(const float& _fDeltaSeconds)
{
	CHECK(!GetOwnerActor().expired());

	ApplyGravity(GetOwnerActor(), _fDeltaSeconds);
	return CActorComponent::Update(_fDeltaSeconds);
}

int32 CPhysicsComponent::LateUpdate(const float& _fDeltaSeconds)
{
	return CActorComponent::Update(_fDeltaSeconds);
}

void CPhysicsComponent::EndPlay()
{
	CActorComponent::EndPlay();
}

void CPhysicsComponent::Render()
{
	CActorComponent::Render();
}

void CPhysicsComponent::Release()
{
	CActorComponent::Release();
}

void CPhysicsComponent::ApplyGravity(std::weak_ptr<CActor> _wpOwnerActor, const float& fTimeDelta)
{
	float fTotalSpeed = -m_fGravityValue * fTimeDelta;

	_wpOwnerActor.lock()->SetActorPosition
	(
		{
			_wpOwnerActor.lock()->GetActorPosition().x,
			_wpOwnerActor.lock()->GetActorPosition().y + fTotalSpeed,
			_wpOwnerActor.lock()->GetActorPosition().z
		}
	);
};