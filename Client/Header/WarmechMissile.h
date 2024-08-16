#pragma once
#include "Projectile.h"

class CWarmechMissile : public CProjectile
{
public:
	explicit CWarmechMissile() = default;
	virtual ~CWarmechMissile() = default;

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
	Callbacks
********************/
public:
	virtual int32 OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider);

private:
	float m_fGravity = 9.8f;

	float m_fSumFireSeconds = 0.0f;

	uint32 m_iNumBounce = 0;
};

