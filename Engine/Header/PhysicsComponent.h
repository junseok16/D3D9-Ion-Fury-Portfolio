#pragma once
#include "ActorComponent.h"

class CCreture;

class CPhysicsComponent : public CActorComponent
{
public:
	explicit CPhysicsComponent() = default;
	virtual ~CPhysicsComponent() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void EndPlay() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void SetGravityValue(const float& _fGravityValue) { m_fGravityValue = _fGravityValue; }
	const float& GetGravityValue() { return m_fGravityValue; }

	void SetFlightTime(const float& _fFlightTime) { m_fFlightTime = _fFlightTime; }
	const float& GetFlightTime() { return m_fFlightTime; }

private:
	void ApplyGravity(std::weak_ptr<CActor> _wpOwnerActor, const float& _fTimeDelta);

private:
	float	m_fGravityValue = 39.2f; // 중력
	float	m_fFlightTime = 0.0f; // 체공시간
};

