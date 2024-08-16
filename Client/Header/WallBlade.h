#pragma once
#include "CubeColliderActor.h"

enum class EBladeMovementType
{
	STATIC,
	VERTICAL,
	HORIZONTAL
};

class CAnimationComponent;

class CWallBlade : public CCubeColliderActor
{
public:
	explicit CWallBlade() = default;
	virtual ~CWallBlade() = default;

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
	void SetDamage(float _fDamage) { m_fDamage = _fDamage; }
	float GetDamage() const { return m_fDamage; }

	void SetMovementTime(float _fMovementTime) { m_fMovementTime = _fMovementTime; }

	void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }

	void SetMovementType(EBladeMovementType _eBladeMovementType) { m_eBladeMovementType = _eBladeMovementType; }

/********************
	Callbacks
********************/
	virtual int32 OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider);

private:
	std::weak_ptr<CAnimationComponent> m_wpAnimationComponent;

	// Į�� �ӵ�
	float m_fSpeed = 10.0f;

	// Į�� �����
	float m_fDamage = 10.0f;

	// Į���� �̵��� �ð�
	float m_fMovementTime = 10.0f;

	// Į���� �� �̵��� �ð�
	float m_fSumMovementTime = 0.0f;

	FVector3 m_vUp = { 0.0f, 1.0f, 0.0f };

	FVector3 m_vRight = { 1.0f, 0.0f, 0.0f };

	// Į�� �̵� Ÿ��
	EBladeMovementType m_eBladeMovementType = EBladeMovementType::STATIC;
};
