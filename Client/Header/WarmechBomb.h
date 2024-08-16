#pragma once
#include "Projectile.h"

class CWarmechBomb : public CProjectile
{
public:
	explicit CWarmechBomb() = default;
	virtual ~CWarmechBomb() = default;

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
	Initialize
********************/
public:
	void InitializeEffectComponent();

	void InitializeAnimationComponent();

	void InitializeSoundComponent();

/********************
	Callbacks
********************/
public:
	virtual int32 OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider);

private:
	// ÆøÅºÀÌ ¹ÞÀ» Áß·Â »ó¼ö
	float m_fGravityConstant = 9.8f;

	float m_fSumDeltaSeconds = 0.0f;

	// ÆøÅºÀÌ Æ¨°ÜÁø È½¼ö
	uint32 m_iBombNumBounce = 0;

	FVector3 m_vBounceDirConstant = { 0.0f, 1.0f, 0.0f };

	FVector3 m_vBounceDir = { 0.0f, 1.0f, 0.0f };

	bool m_bIsExploded = false;
};

