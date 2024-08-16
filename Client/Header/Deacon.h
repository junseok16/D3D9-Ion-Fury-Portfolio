#pragma once
#include "Monster.h"

enum class EDeaconHittedSound
{
	NUM_1,
	NUM_2,
	ENUM_END
};

class CDeacon : public CMonster
{
public:
	explicit CDeacon() = default;
	virtual ~CDeacon() = default;

/********************
	Framework
********************/
public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

/********************
	Component Initialize
********************/
private:
	void InitializeAIComponent();

	void InitializeSensorComponent();

	void UpdateMonsterState();

	virtual void UpdateMonsterDirection() override;

	virtual void AnimationSetting() override;

	virtual void AnimationStateSetting() override;

	virtual void AnimationSpeedSetting() override;

	virtual void ColliderSetting() override;

	virtual void PhysicsSetting() override;

	virtual void ParticleSetting() override;

	virtual void SoundSetting() override;

/********************
	Getter/Setter
********************/
public:
	virtual void SetMonsterState(int32 _iMonsterState) override;

	virtual int32 GetMonsterState() const override;

	virtual void GetDamaged(const float& _fDamage) override;

/********************
	Callbacks
********************/
private:
	virtual void PlayDeathSound();

	void OnSeeingEnterDelegate();

	void OnSeeingExitDelegate();

/********************
	Data Members
********************/
private:
	EDeaconHittedSound m_eDeaconHittedSound = EDeaconHittedSound::NUM_1;
};