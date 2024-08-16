#pragma once
#include "UI.h"

class CUIComponent;

class CItemUI : public CUI
{
public:
	explicit CItemUI() = default;
	virtual ~CItemUI() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

private:
	std::weak_ptr<CUIComponent> m_wpItemUIComponent;
};

