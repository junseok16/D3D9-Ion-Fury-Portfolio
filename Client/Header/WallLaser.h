#pragma once
#include "CubeColliderActor.h"

enum class ELaserMovementType
{
	STATIC,
	VERTICAL,
	HORIZONTAL
};

class CAnimationComponent;

class CWallLaser : public CCubeColliderActor
{
public:
	explicit CWallLaser() = default;
	virtual ~CWallLaser() = default;

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

	void SetMovementType(ELaserMovementType _eLaserMovementType) { m_eLaserMovementType = _eLaserMovementType; }

/********************
	Callbacks
********************/
	virtual int32 OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider);

private:
	std::weak_ptr<CAnimationComponent> m_wpAnimationComponent;

	// 레이저 속도
	float m_fSpeed = 10.0f;

	// 레이저 대미지
	float m_fDamage = 10.0f;

	// 레이저가 이동할 시간
	float m_fMovementTime = 10.0f;

	// 레이저가 총 이동한 시간
	float m_fSumMovementTime = 0.0f;

	// 레이저 이동 타입
	ELaserMovementType m_eLaserMovementType = ELaserMovementType::STATIC;

	FVector3 m_vUp = { 0.0f, 1.0f, 0.0f };

	FVector3 m_vRight = { 1.0f, 0.0f, 0.0f };
};

