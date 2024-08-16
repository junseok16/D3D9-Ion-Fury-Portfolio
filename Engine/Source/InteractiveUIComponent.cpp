#include "pch.h"
#include "InteractiveUIComponent.h"

void CInteractiveUIComponent::Initialize()
{
    CUIComponent::Initialize();
}

void CInteractiveUIComponent::BeginPlay()
{
    CUIComponent::BeginPlay();
}

int32 CInteractiveUIComponent::Update(const float& _fDeltaSeconds)
{
    return CUIComponent::Update(_fDeltaSeconds);
}

int32 CInteractiveUIComponent::LateUpdate(const float& _fDeltaSeconds)
{
    return CUIComponent::LateUpdate(_fDeltaSeconds);
}

void CInteractiveUIComponent::Render()
{
    CUIComponent::Render();
}

void CInteractiveUIComponent::EndPlay()
{
    CUIComponent::EndPlay();
}

void CInteractiveUIComponent::Release()
{
    CUIComponent::Release();
}

void CInteractiveUIComponent::HandleKeyboardEvent(int32 _iKey)
{
}

void CInteractiveUIComponent::HandleMouseEvent(int32 _iX, int _iY)
{
}
