#pragma once
#include "InteractiveUIComponent.h"

class CSelectionButtonUIComponent : public CInteractiveUIComponent
{
public:
	explicit CSelectionButtonUIComponent() = default;
	virtual ~CSelectionButtonUIComponent() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;
};

