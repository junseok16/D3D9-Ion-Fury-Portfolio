#pragma once
#include "AnimationComponent.h"

class CEffectComponent : public CAnimationComponent
{
public:
	explicit CEffectComponent() = default;
	virtual ~CEffectComponent() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

	virtual void UpdateAnimation(const float& _fDeltaSeconds);
};

