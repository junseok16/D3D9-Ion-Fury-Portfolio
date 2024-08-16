#pragma once
#include "Monster.h"

enum class EWarmechLegAnimType
{
	IDLE,
	WALK,
	RUN,
	ENUM_END
};

enum class EWarmechLegState
{
	IDLE,
	RESERVE,
	SMASH,
	FALL_FROM_SKY,
	MOVE_TO_CENTER,
	MOVE_TO_RANDOM,
	MOVE_TO_PLAYER,
	READY_TO_CHARGE,
	CHARGE_TO_PLAYER,
	JUMP_TO_CENTER,

	MOVE_TO_SELF_DESTRUCT,
	SELF_DESTRUCT,
	BREAK_SAFE_FLOOR,
	DEAD,
	ENUM_END
};

class CWarmechHead;
class CParticleComponent;
class CWarmechCharge;
class CWarmechSmash;
class CPlayerActor;
class COutGameUI;

class CWarmechLeg : public CMonster
{
public:
	explicit CWarmechLeg() = default;
	virtual ~CWarmechLeg() = default;

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
	Methods
********************/
public:
	void UpdateLegPhase(float _fDeltaSeconds);

	void UpdateLegState(float _fDeltaSeconds);

	void UpdateLegAnim(float _fDeltaSeconds);

	void UpdateLegDirection();

	void UpdateLegDirectionByPhase(uint32 _iPhaseIndex);

	void UpdateSkillPosition(float _fDeltaSeconds);

public:
	void Reserve(float _fDeltaSeconds);

	void JumpToCenter(float _fDeltaSeconds);

	void MoveToCenter(float _fDeltaSeconds);

	void MoveToRandom(float _fDeltaSeconds);

	void MoveToPlayer(float _fDeltaSeconds);

	void MoveToSelfDestruct(float _fDeltaSeconds);

	void ReadyToRush(float _fDeltaSeconds);

	void RushToPlayer(float _fDeltaSeconds);

	void Smash(float _fDeltaSeconds);

	void SelfDestruct(float _fDeltaSeconds);

	void BreakSafeFloor(float _fDeltaSeconds);

	void Dead(float _fDeltaSeconds);

private:
	int32 GetRandomInteger(int32 _iMin, int32 _iMax);

	float GetRandomFloat(float _fMin, float _fMax);

/********************
	Component
********************/
private:
	void InitializeEffectComponent();

	void InitializeSoundComponent();

	virtual void AnimationSetting() override;

	virtual void ColliderSetting() override;

	virtual void PhysicsSetting() override;

	virtual void ParticleSetting() override;

/********************
	Getter/Setter
********************/
public:
	void SetWarmechHead(std::shared_ptr<CWarmechHead> _spWarmechHead);

	virtual void SetMonsterState(int32 _iMonsterState) override;

	virtual int32 GetMonsterState() const override;

	virtual void SetMonsterPhase(int32 _iMonsterPhase) override;

	virtual int32 GetMonsterPhase() const override;

	virtual void SetMonsterAnim(int32 _iMonsterAnim) override;

	virtual int32 GetMonsterAnim() const override;

	virtual void GetDamaged(const float& _fDamage) override;

	void SetCharge(std::weak_ptr<CWarmechCharge> _wpCharge) { m_wpCharge = _wpCharge; }

	void SetSmash(std::weak_ptr<CWarmechSmash> _wpSmash) { m_wpSmash = _wpSmash; }

/********************
	Callbacks
********************/
private:
	virtual int32 OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider);

	virtual void OnCollisionStay(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider);

	virtual void OnCollisionExit(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider);

/********************
	Data Members
********************/
private:
	// 현재 다리 상태
	EWarmechLegState m_eCurWarmechLegState = EWarmechLegState::IDLE;

	EWarmechLegState m_ePrevWarmechLegState = EWarmechLegState::ENUM_END;

	EWarmechLegState m_ePostWarmechLegState = EWarmechLegState::ENUM_END;

	// 현재 보스 페이즈
	EWarmechPhase m_eCurWarmechLegPhase = EWarmechPhase::READY;

	EWarmechPhase m_ePrevWarmechLegPhase = EWarmechPhase::ENUM_END;

	// 현재 다리 애니메이션 상태
	EWarmechLegAnimType m_eCurWarmechLegAnimType = EWarmechLegAnimType::IDLE;

	EWarmechLegAnimType m_ePrevWarmechLegAnimType = EWarmechLegAnimType::ENUM_END;

private:
	std::weak_ptr<CPlayerActor> m_wpPlayer;

	std::weak_ptr<CWarmechHead> m_wpWarmechHead;

	std::weak_ptr<CWarmechSmash> m_wpSmash;

	std::weak_ptr<CWarmechCharge> m_wpCharge;

	std::weak_ptr<COutGameUI> m_wpOutGameUI;

	std::weak_ptr<CParticleComponent> m_wpParticleComponent;

private:
	// 다리의 도착점
	FVector3 m_vDst = { 0.0f, 0.0f, -50.0f };

	// 다리의 방향 벡터
	FVector3 m_vJumpDir = { 0.0f, 1.0f, 0.0f };

	float m_fY = 0.0f;

	// 전장의 너비
	float m_fWidth = 180.0f;

	// 전장의 높이
	float m_fHeight = 180.0f;

private:
	// 예약된 상태를 변경하기 전 대기할 시간
	float m_fReserveDeltaSeconds = 3.0f;

	// 상태를 변화시키기 위해 있는 누적된 델타 타임
	float m_fSumDeltaSeconds = 0.0f;

	// 상태를 변화하라고 요청을 했는지 여부
	bool m_bIsCalled = false;

private:
	float m_fSumMoveDeltaSeconds = 0.0f;

	float m_fSmashDamage = 10.0f;

	float m_fSmashSize = 150.0f;

	bool m_bIsSmashed = false;

	bool m_bIsTriggered = false;
};

