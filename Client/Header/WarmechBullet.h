#pragma once
#include "Projectile.h"

class COutGameUI;

class CWarmechBullet : public CProjectile
{
public:
	explicit CWarmechBullet() = default;
	virtual ~CWarmechBullet() = default;

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
public:
	void InitializeSoundComponent();


/********************
	Callbacks
********************/
public:
	virtual int32 OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider);

private:
	bool m_bIsExploded = false;
};

