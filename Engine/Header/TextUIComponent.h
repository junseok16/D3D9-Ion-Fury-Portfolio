#pragma once
#include "NonInteractiveUIComponent.h"

class CTextUIComponent : public CNonInteractiveUIComponent
{
public:
	explicit CTextUIComponent() = default;
	virtual ~CTextUIComponent() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;
};

