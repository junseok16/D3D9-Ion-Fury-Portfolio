#pragma once
#include "UIComponent.h"

class CNonInteractiveUIComponent : public CUIComponent
{
public:
	explicit CNonInteractiveUIComponent() = default;
	virtual ~CNonInteractiveUIComponent() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;
};

