#pragma once
#include "Monster.h"

// 동준 임시 코드입니다 
class CPlayerActor;
class CCameraComponent;
class CSpriteUIComponent;
class CAnimationComponent;
/////////////////////////////

enum class EMechsectHittedSound
{
	NUM_1,
	NUM_2,
	ENUM_END
};

class CMechsect : public CMonster
{
public:
	explicit CMechsect() = default;
	virtual ~CMechsect() = default;

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

	virtual void AnimationSetting() override;

	virtual void AnimationStateSetting() override;

	virtual void AnimationSpeedSetting() override;

	virtual void ColliderSetting() override;

	virtual void PhysicsSetting() override;

	virtual void ParticleSetting() override;

	virtual void SoundSetting() override;

/********************
	Methods
********************/
	virtual void UpdateMonsterState() override;

	virtual void UpdateMonsterDirection() override;

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
	virtual void PlayDeathSound() override;

	void OnSeeingEnterDelegate();
	
	void OnSeeingExitDelegate();
	
/********************
	Data Members
********************/
private:
	EMechsectHittedSound m_eMechsectHittedSound = EMechsectHittedSound::NUM_1;
};