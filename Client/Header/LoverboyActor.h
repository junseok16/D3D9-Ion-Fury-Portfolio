#pragma once
#include "WeaponActor.h"

class CCreature;
class CAnimationComponent;
class CSoundComponent;
class COutGameUI;
class CSpriteUIComponent;

class CLoverboyActor : public CWeaponActor
{
public:
	explicit CLoverboyActor() = default;
	virtual ~CLoverboyActor() = default;

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
	void LockOn(float _fDeltaSeconds);
	void AutoAttack();

private:
	std::weak_ptr<CSoundComponent> m_wpSoundComponent;
	std::weak_ptr<CSpriteUIComponent> m_wpOutGameUIComponent;
	std::list<std::weak_ptr<CCreature>> m_lstHitedCreatures;

	std::weak_ptr<CPlayerActor> m_wpPlayer;
	int32 m_iPreBulletLoaded = 0;
	bool m_bAutoAttack = false;
	bool m_bAutoAttackCycle = true;
	bool m_bSeokyangSound = false;
};

