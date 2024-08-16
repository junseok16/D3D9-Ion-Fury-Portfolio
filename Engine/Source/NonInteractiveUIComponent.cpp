#include "pch.h"
#include "NonInteractiveUIComponent.h"

void CNonInteractiveUIComponent::Initialize()
{
    CUIComponent::Initialize();
}

void CNonInteractiveUIComponent::BeginPlay()
{
    CUIComponent::BeginPlay();
}

int32 CNonInteractiveUIComponent::Update(const float& _fDeltaSeconds)
{
    return CUIComponent::Update(_fDeltaSeconds);
}

int32 CNonInteractiveUIComponent::LateUpdate(const float& _fDeltaSeconds)
{
    return CUIComponent::LateUpdate(_fDeltaSeconds);
}

void CNonInteractiveUIComponent::Render()
{
    CUIComponent::Render();
}

void CNonInteractiveUIComponent::EndPlay()
{
    CUIComponent::EndPlay();
}

void CNonInteractiveUIComponent::Release()
{
    CUIComponent::Release();
}

