#pragma once
#include "UIComponent.h"

class CInteractiveUIComponent : public CUIComponent
{
public:
	explicit CInteractiveUIComponent() = default;
	virtual ~CInteractiveUIComponent() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

public:
	void HandleKeyboardEvent(int32 _iKey);
	void HandleMouseEvent(int32 _iX, int _iY);
    void Select() { m_bIsSelected = true; }
    void DeSelect() { m_bIsSelected = false; }

private:
    bool m_bIsSelected;
};

