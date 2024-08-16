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
	READY,		// �غ�
	TO_PHASE_0,	// ������ 0���� �̵�
	PHASE_0,	// ��
	TO_PHASE_1,	// ������ 1���� �̵�
	PHASE_1,	// +
	TO_PHASE_2,	// ������ 2���� �̵�
	PHASE_2,	// -
	DEAD,		// ���
	ENUM_END
};

enum class ESkinjobState
{
	SEPARATE_BOX,		// �ʵ� �и��ϱ�
	EMIT_LASER,			// ������ �����ϱ�
	NON_EMIT_LASER,
	EMIT_FLAME,			// ȭ�� �����ϱ�
	NON_EMIT_FLAME,
	PUSH_OBSTACLE,		// ���� �����ϱ�

	CONBINE_BOX,		// �ʵ� �����ϱ�
	FLOAT_THROWING_BOX,
	THROW_THROWING_BOX,	// ���� ������
	SPAWN_MONSTER,		// ���� �����ϱ�

	IDLE,				//
	BLUE_ENERGY_BALL,	// ������� �������� �۶߸���
	RED_ENERGY_BALL,	// ������ ������ ��濡�� �������� �߻��ϱ�
	DEAD,				// ���
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
	// ���� ���� ����
	ESkinjobState m_eCurSkinjobState = ESkinjobState::IDLE;

	ESkinjobState m_ePrevSkinjobState = ESkinjobState::ENUM_END;

	// ���� ���� ������
	ESkinjobPhase m_eCurSkinjobPhase = ESkinjobPhase::READY;

	ESkinjobPhase m_ePrevSkinjobPhase = ESkinjobPhase::ENUM_END;

	// ���� ���� �ִϸ��̼�
	ESkinjobAnim m_eCurSkinjobAnim = ESkinjobAnim::IDLE;

	ESkinjobAnim m_ePrevSkinjobAnim = ESkinjobAnim::ENUM_END;

private:
	// �÷��̾�
	std::weak_ptr<CActor> m_wpPlayer;

	// 3 x 3 ����
	std::weak_ptr<CFloatingBox> m_wpFloatingBox[3][3];

	// ���� �ڽ�
	std::weak_ptr<CThrowingBox> m_wpThrowingBox[6];

	float m_fRadian = 0.0f;

private:
	// ���¸� ��ȭ��Ű�� ���� �ִ� ������ ��Ÿ Ÿ��
	float m_fSumDeltaSeconds = 0.0f;

	// ���¸� ��ȭ�϶�� ��û�� �ߴ��� ����
	bool m_bIsCalled = false;

	// �������� ������ Ƚ��
	uint32 m_iEmitLaserCounter = 0;

	// ȭ���� ������ Ƚ��
	uint32 m_iEmitFlameCounter = 0;
};

