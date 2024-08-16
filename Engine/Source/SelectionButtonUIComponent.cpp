#include "pch.h"
#include "SelectionButtonUIComponent.h"

void CSelectionButtonUIComponent::Initialize()
{
    CInteractiveUIComponent::Initialize();
}

void CSelectionButtonUIComponent::BeginPlay()
{
    CInteractiveUIComponent::BeginPlay();
}

int32 CSelectionButtonUIComponent::Update(const float& _fDeltaSeconds)
{
    return CInteractiveUIComponent::Update(_fDeltaSeconds);
}

int32 CSelectionButtonUIComponent::LateUpdate(const float& _fDeltaSeconds)
{
    return CInteractiveUIComponent::LateUpdate(_fDeltaSeconds);
}

void CSelectionButtonUIComponent::Render()
{
    CInteractiveUIComponent::Render();
}

void CSelectionButtonUIComponent::EndPlay()
{
    CInteractiveUIComponent::EndPlay();
}

void CSelectionButtonUIComponent::Release()
{
    CInteractiveUIComponent::Release();
}

