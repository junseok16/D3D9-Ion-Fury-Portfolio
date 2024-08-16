#pragma once
#include "Actor.h"

class CAnimationComponent;

class CWeaponLHActor : public CActor
{
public:
	explicit CWeaponLHActor() = default;
	virtual ~CWeaponLHActor() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

protected:
	std::weak_ptr<CAnimationComponent>		m_wpAnimationComponent;
};

