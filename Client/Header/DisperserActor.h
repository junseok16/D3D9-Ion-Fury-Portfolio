#pragma once
#include "WeaponActor.h"

class CSoundComponent;

class CDisperserActor : public CWeaponActor
{
public:
	explicit CDisperserActor() = default;
	virtual ~CDisperserActor() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

public:
	virtual void SetFrameInteract(int32 OffFire) override;

private:
	void AnimationSetting();
	void AutoReload();

private:
	std::weak_ptr<CSoundComponent> m_wpSoundComponent;
};

