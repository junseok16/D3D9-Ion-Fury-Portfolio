#pragma once
#include "Monster.h"

enum class EWarmechHeadAnimType
{
	IDLE,
	FIRE_GUN,
	FIRE_BOMB,
	FIRE_MISSILE,
	ENUM_END
};

enum class EWarmechHeadState
{
	IDLE,
	RESERVE,
	FIRE_STRAIGHT_GUN,
	FIRE_PARABOLA_BOMB,
	FIRE_STRAIGHT_MISSILE,
	SPAWN_MONSTER,
	SELF_DESTRUCT,
	DEAD,
	ENUM_END
};

class CPlayerActor;
class CWarmechLeg;
class COutGameUI;

class CWarmechHead : public CMonster
{
	friend CWarmechLeg;

public:
	explicit CWarmechHead() = default;
	virtual ~CWarmechHead() = default;

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
	void SetWarmechLeg(std::shared_ptr<CWarmechLeg> _spWarmechLeg);

	void UpdateHeadPosition();

	void UpdateHeadPhase(float _fDeltaSeconds);

	void UpdateHeadState(float _fDeltaSeconds);

	void UpdateHeadAnim();

	void UpdateHeadDirection();

	void UpdateHeadDirectionByPhase(uint32 _iPhaseIndex);

public:
	void Reserve(float _fDeltaSeconds);

	void FireGun(EFireType _eFireType, float _fDeltaSeconds);

	void FireBomb(EFireType _eFireType, float _fDeltaSeconds);

	void FireMissile(EFireType _eFireType, float _fDeltaSeconds);

	void SpawnMonster(float _fDeltaSeconds);

	void SelfDestruct(float _fDeltaSeconds);

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

	virtual void ParticleSetting() override;

/********************
	Getter/Setter
********************/
public:
	virtual void SetMonsterState(int32 _iMonsterState) override;

	virtual int32 GetMonsterState() const override;

	virtual void SetMonsterPhase(int32 _iMonsterPhase) override;

	virtual int32 GetMonsterPhase() const override;

	virtual void SetMonsterAnim(int32 _iMonsterAnim) override;

	virtual int32 GetMonsterAnim() const override;

	virtual void GetDamaged(const float& _fDamage) override;

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
	// 현재 머리 상태
	EWarmechHeadState m_eCurWarmechHeadState = EWarmechHeadState::IDLE;

	EWarmechHeadState m_ePrevWarmechHeadState = EWarmechHeadState::ENUM_END;

	EWarmechHeadState m_ePostWarmechHeadState = EWarmechHeadState::ENUM_END;

	// 현재 보스 페이즈
	EWarmechPhase m_eCurWarmechHeadPhase = EWarmechPhase::READY;

	EWarmechPhase m_ePrevWarmechHeadPhase = EWarmechPhase::ENUM_END;

	// 현재 머리 애니메이션 상태
	EWarmechHeadAnimType m_eCurWarmechHeadAnimType = EWarmechHeadAnimType::IDLE;

	EWarmechHeadAnimType m_ePrevWarmechHeadAnimType = EWarmechHeadAnimType::ENUM_END;

private:
	std::weak_ptr<COutGameUI> m_wpOutGameUI;

	std::weak_ptr<CPlayerActor> m_wpPlayer;

	std::weak_ptr<CWarmechLeg> m_wpWarmechLeg;

private:
	// 예약된 상태를 변경하기 전 대기할 시간
	float m_fReserveDeltaSeconds = 3.0f;

	// 상태를 변화시키기 위해 있는 누적된 델타 타임
	float m_fSumDeltaSeconds = 0.0f;

	// 상태를 변화하라고 요청을 했는지 여부
	bool m_bIsCalled = false;

private:
	static uint32 s_iGunBulletCounter;

	// FIRE_..._GUN 횟수
	uint32 m_iFireGunCounter;

	// 한 번에 발사할 탄 수
	uint32 m_iGunBullets = 6;

	// 발사된 탄 수
	uint32 m_iSumGunBullets = 0;

	// 탄 사이의 시간 간격
	float m_fGunFireInterval = 0.3f;

	// 누적된 탄 사이의 시간 간격
	float m_fSumGunFireInterval = 0.0f;

	// 탄의 이동 속도
	float m_fGunSpeed = 30.0f;

	// 탄의 대미지
	float m_fGunDamage = 2.0f;

private:
	static uint32 s_iBombCounter;

	// FIRE_..._BOMB 횟수
	uint32 m_iFireBombCounter;

	// 한 번에 발사할 폭탄 수
	uint32 m_iBombs = 6;

	// 발사된 폭탄 수
	uint32 m_iSumBombs = 0;

	// 폭탄 사이의 시간 간격
	float m_fBombFireInterval = 0.5f;

	// 누적된 폭탄 사이의 시간 간격
	float m_fSumBombFireInterval = 0.0f;

	// 폭탄의 이동 속도
	float m_fBombSpeed = 30.0f;

	// 폭탄의 대미지
	float m_fBombDamage = 3.0f;

	// 폭탄의 중력
	float m_fBombGravityConstant = 9.8f;

	// 폭탄이 튕겨질 횟수
	uint32 m_iBombNumBounce = 1;

private:
	static uint32 s_iMonsterCounter;

	// 전장의 너비
	float m_fWidth = 100.0f;

	// 전장의 높이
	float m_fHeight = 100.0f;

	// 스폰할 몬스터
	EMonsterType m_eMonsterType = EMonsterType::MECHSECT;

	// 스폰할 몬스터 마리 수
	uint32 m_iNumMonsters = 6;
};

