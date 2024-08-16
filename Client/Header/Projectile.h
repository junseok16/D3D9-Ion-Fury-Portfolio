#pragma once
#include "CubeColliderActor.h"

class CAnimationComponent;
class CPhysicsComponent;
class CEffectComponent;
class CSoundComponent;

class CProjectile : public CCubeColliderActor
{
public:
	explicit CProjectile() = default;
	virtual ~CProjectile() = default;

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

public:
	virtual bool IsDead(const float& _fDeltaSeconds);

public:
	void SetTarget(std::shared_ptr<CActor> _spTarget) { m_wpTarget = _spTarget; }
	std::weak_ptr<CActor> GetTarget() const { return m_wpTarget; }

	void SetDamage(float _fDamage) { m_fDamage = _fDamage; }
	float GetDamage() const { return m_fDamage; }

	void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }
	float GetSpeed() const { return m_fSpeed; }

	void SetIsDead(bool _bIsDead) { m_bIsDead = _bIsDead; }
	bool GetIsDead() const { return m_bIsDead; }

	void SetDirection(FVector3 _vDirection) { m_vDirection = _vDirection; }
	const FVector3& GetDirection() const { return m_vDirection; }

	void SetBillBoard(std::weak_ptr<CPrimitiveComponent> _wpPrimitiveComponent);

protected:
	// 투사체 애니메이션 컴포넌트
	std::weak_ptr<CAnimationComponent> m_wpAnimationComponent;

	// 투사체 피직스 컴포넌트
	std::weak_ptr<CPhysicsComponent> m_wpPhysicsComponent;

	// 투사체 이펙트 컴포넌트
	std::weak_ptr<CEffectComponent> m_wpEffectComponent;

	// 투사체 사운드 컴포넌트
	std::weak_ptr<CSoundComponent> m_wpSoundComponent;

	// 투사체의 방향
	FVector3 m_vDirection = { 0.0f, 0.0f, -1.0f };

	// 투사체의 목표
	std::weak_ptr<CActor> m_wpTarget;

	// 투사체 대미지
	float m_fDamage = 0.0f;

	// 투사체 속도
	float m_fSpeed = 1.0f;

	// 투사체 사망(?) 여부
	bool m_bIsDead = false;

	// 투사체 사망 후 메모리에서 해제하기 전 지연할 시간
	float m_fSumDeadDelay = 0.0f;
};

