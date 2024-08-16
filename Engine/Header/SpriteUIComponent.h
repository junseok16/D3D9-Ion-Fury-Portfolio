#pragma once
#include "NonInteractiveUIComponent.h"

class CSpriteUIComponent : public CNonInteractiveUIComponent
{
public:
	explicit CSpriteUIComponent() = default;
	virtual ~CSpriteUIComponent() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

	void SetUINumber(const int32& _iCurFrame);
};

