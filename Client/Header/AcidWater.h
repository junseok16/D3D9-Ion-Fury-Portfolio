#pragma once
#include "CubeColliderActor.h"

class CAnimationComponent;

class CAcidWater : public CCubeColliderActor
{
public:
	explicit CAcidWater() = default;
	virtual ~CAcidWater() = default;

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
	void InitializeAnimationComponent();

/********************
	Callbacks
********************/
	virtual int32 OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider);

/********************
	Data Members
********************/
private:
	std::weak_ptr<CAnimationComponent> m_wpAnimationComponent;

};

