#pragma once
#include "Monster.h"

enum class ESkinjobAnim
{
	IDLE,
	WALK,
	LOTUS,
	ROAR,
	SHOCK,
	DEAD,
	ENUM_END
};

enum class ESkinjobPhase
{
	READY,		// 준비
	TO_PHASE_0,	// 페이즈 0으로 이동
	PHASE_0,	// ▦
	TO_PHASE_1,	// 페이즈 1으로 이동
	PHASE_1,	// +
	TO_PHASE_2,	// 페이즈 2으로 이동
	PHASE_2,	// -
	DEAD,		// 사망
	ENUM_END
};

enum class ESkinjobState
{
	SEPARATE_BOX,		// 필드 분리하기
	EMIT_LASER,			// 레이저 생성하기
	NON_EMIT_LASER,
	EMIT_FLAME,			// 화염 생성하기
	NON_EMIT_FLAME,
	PUSH_OBSTACLE,		// 상자 생성하기

	CONBINE_BOX,		// 필드 결합하기
	FLOAT_THROWING_BOX,
	THROW_THROWING_BOX,	// 상자 던지기
	SPAWN_MONSTER,		// 몬스터 생성하기

	IDLE,				//
	BLUE_ENERGY_BALL,	// 가운데에서 에너지볼 퍼뜨리기
	RED_ENERGY_BALL,	// 복제된 보스가 사방에서 에너지볼 발사하기
	DEAD,				// 사망
	ENUM_END
};

class CFloatingBox;
class CThrowingBox;

class CSkinjob : public CMonster
{
public:
	explicit CSkinjob() = default;
	virtual ~CSkinjob() = default;

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
	Component
********************/
private:
	void InitializeAnimationCompnent();

	void InitializeColliderComponent();

	void InitializeParticleComponent();

/********************
	Overrides
********************/
public:
	virtual void UpdateMonsterPhase() override;

	virtual void UpdateMonsterState() override;

	void UpdateMonsterAnim();

private:
	void UpdateMonsterDirection();

/********************
	Methods
********************/
public:
	void AscendFloatingBox(int32 _iBoxIndex);

	void DescendFloatingBox(int32 _iBoxIndex);

	void SeparateFloatingBox(int32 _iBoxIndex);

	void CombineFloatingBox(int32 _iBoxIndex);

public:
	void EmitFlame();

	void NonEmitFlame();

	void EmitLaser();

	void NonEmitLaser();

	void FloatRandomBox();

	void ThrowRandomBox();

	void SeparateBox();

	void CombineBox();

private:
	int32 GetRandomInteger(int32 _iMin, int32 _iMax);

	float GetRandomFloat(float _fMin, float _fMax);

/********************
	Callbacks
********************/
private:
	virtual int32 OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider);

	virtual void OnCollisionStay(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider);

	virtual void OnCollisionExit(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider);

/********************
	Getter/Setter
********************/
	virtual void SetMonsterState(int32 _iMonsterState) override;

	virtual int32 GetMonsterState() const override;

	virtual void SetMonsterPhase(int32 _iMonsterPhase) override;

	virtual int32 GetMonsterPhase() const override;

	virtual void SetMonsterAnim(int32 _iMonsterAnim) override;

	virtual int32 GetMonsterAnim() const override;

/********************
	Data Members
********************/
private:
	// 현재 보스 상태
	ESkinjobState m_eCurSkinjobState = ESkinjobState::IDLE;

	ESkinjobState m_ePrevSkinjobState = ESkinjobState::ENUM_END;

	// 현재 보스 페이즈
	ESkinjobPhase m_eCurSkinjobPhase = ESkinjobPhase::READY;

	ESkinjobPhase m_ePrevSkinjobPhase = ESkinjobPhase::ENUM_END;

	// 현재 보스 애니메이션
	ESkinjobAnim m_eCurSkinjobAnim = ESkinjobAnim::IDLE;

	ESkinjobAnim m_ePrevSkinjobAnim = ESkinjobAnim::ENUM_END;

private:
	// 플레이어
	std::weak_ptr<CActor> m_wpPlayer;

	// 3 x 3 발판
	std::weak_ptr<CFloatingBox> m_wpFloatingBox[3][3];

	// 랜덤 박스
	std::weak_ptr<CThrowingBox> m_wpThrowingBox[6];

	float m_fRadian = 0.0f;

private:
	// 상태를 변화시키기 위해 있는 누적된 델타 타임
	float m_fSumDeltaSeconds = 0.0f;

	// 상태를 변화하라고 요청을 했는지 여부
	bool m_bIsCalled = false;

	// 레이저를 분출한 횟수
	uint32 m_iEmitLaserCounter = 0;

	// 화염을 분출한 횟수
	uint32 m_iEmitFlameCounter = 0;
};

