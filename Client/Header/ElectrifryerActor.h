#pragma once
#include "WeaponActor.h"
class CElectrifryerActor : public CWeaponActor
{
public:
	explicit CElectrifryerActor() = default;
	virtual ~CElectrifryerActor() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

public:
	void Input();
	virtual void UpdateFSM();

private:
	FVector3 vOut;
};

