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
	// ����ü �ִϸ��̼� ������Ʈ
	std::weak_ptr<CAnimationComponent> m_wpAnimationComponent;

	// ����ü ������ ������Ʈ
	std::weak_ptr<CPhysicsComponent> m_wpPhysicsComponent;

	// ����ü ����Ʈ ������Ʈ
	std::weak_ptr<CEffectComponent> m_wpEffectComponent;

	// ����ü ���� ������Ʈ
	std::weak_ptr<CSoundComponent> m_wpSoundComponent;

	// ����ü�� ����
	FVector3 m_vDirection = { 0.0f, 0.0f, -1.0f };

	// ����ü�� ��ǥ
	std::weak_ptr<CActor> m_wpTarget;

	// ����ü �����
	float m_fDamage = 0.0f;

	// ����ü �ӵ�
	float m_fSpeed = 1.0f;

	// ����ü ���(?) ����
	bool m_bIsDead = false;

	// ����ü ��� �� �޸𸮿��� �����ϱ� �� ������ �ð�
	float m_fSumDeadDelay = 0.0f;
};

