#pragma once
#include "Creature.h"

class CPlayerActor;
class CSensorComponent;
class CAnimationComponent;
class CBlackBoardComponent;
class CBehaviorTreeComponent;

class CMonster : public CCreature
{
public:
	explicit CMonster() = default;
	virtual ~CMonster() = default;

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
	Getter/Setter
********************/
public:
	virtual void SetMonsterState(int32 _eMonsterState);

	virtual int32 GetMonsterState() const;

	virtual void SetMonsterPhase(int32 _eMonsterPhase);

	virtual int32 GetMonsterPhase() const;

	virtual void SetMonsterAnim(int32 _eMonsterAnim);

	virtual int32 GetMonsterAnim() const;

	void SetAttackTerm(const float& _fAttackTerm) { m_fAttackTerm = _fAttackTerm; }
	const float& GetAttackTerm() { return m_fAttackTerm; }

/********************
	Methods
********************/
public:
	virtual int32 DeadCheck(const float& _fDeltaSeconds);

	virtual void PlayDeathSound() {};

	virtual void SetBillboard(std::weak_ptr<CPrimitiveComponent> _wpPrimitiveComponent);

	virtual void AnimationStateSetting() {};

	virtual void AnimationSpeedSetting() {};

/********************
	Overrides
********************/
protected:
	virtual void UpdateMonsterPhase();

	virtual void UpdateMonsterState();

	virtual void UpdateMonsterDirection();

	virtual int32 OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider) override;

	virtual void OnCollisionStay(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider) override;

	virtual void OnCollisionExit(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider) override;

	// 동준 추가, 몬스터 머리 위 해골 관련 함수 
	void InitSkullUI();
	void BeginPlaySkullUI();
	void UpdateSkullUI(std::weak_ptr<CAnimationComponent> _wpMonseterActor);

/********************
	Data Members
********************/
protected:
	std::weak_ptr<CPlayerActor> m_wpPlayerActor;
	std::weak_ptr<CSensorComponent> m_wpSensorComponent;
	std::weak_ptr<CBlackBoardComponent> m_wpBlackBoardComponent;
	std::weak_ptr<CAnimationComponent> m_wpMonsterSkullComponent;
	std::weak_ptr<CBehaviorTreeComponent> m_wpBehaviorTreeComponent;

	EMonsterState m_eCurMonsterState = EMonsterState::IDLE;

	EMonsterState m_ePrevMonsterState = EMonsterState::IDLE;

	// 콜라이더 삭제 여부
	bool m_bIsColliderDeleted = false;

	// 공격 내부쿨타임
	float m_fAttackTerm = 0.0f;
};