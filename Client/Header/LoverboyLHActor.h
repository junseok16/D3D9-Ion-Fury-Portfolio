#pragma once
#include "WeaponLHActor.h"

class CAnimationComponent;

class CLoverboyLHActor : public CWeaponLHActor
{
public:
	explicit CLoverboyLHActor() = default;
	virtual ~CLoverboyLHActor() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

public:
	void InputSetting();
	void Aiming();

private:
	float m_fSpeed = 200.f;
	
};

