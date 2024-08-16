#include "pch.h"
#include "TextUIComponent.h"

void CTextUIComponent::Initialize()
{
	//for (auto& pair : m_umapElements)
	//{
	//	pair.second->Initialize();
	//}
    CNonInteractiveUIComponent::Initialize();
}

void CTextUIComponent::BeginPlay()
{
	//for (auto& pair : m_umapElements)
	//{
	//	pair.second->BeginPlay();
	//}
    CNonInteractiveUIComponent::BeginPlay();
}

int32 CTextUIComponent::Update(const float& _fDeltaSeconds)
{
	//for (auto& pair : m_umapElements)
	//{
	//	int32 iResult = pair.second->Update(_fDeltaSeconds);
	//	if (iResult != 0) { return -1; }
	//}
    return CNonInteractiveUIComponent::Update(_fDeltaSeconds);
}

int32 CTextUIComponent::LateUpdate(const float& _fDeltaSeconds)
{
	//for (auto& pair : m_umapElements)
	//{
	//	int32 iResult = pair.second->LateUpdate(_fDeltaSeconds);
	//	if (iResult != 0) { return -1; }
	//}
    return CNonInteractiveUIComponent::LateUpdate(_fDeltaSeconds);
}

void CTextUIComponent::Render()
{
	//for (auto& pair : m_umapElements)
	//{
	//	pair.second->Render();
	//}
    CNonInteractiveUIComponent::Render();
}

void CTextUIComponent::EndPlay()
{
	//for (auto& pair : m_umapElements)
	//{
	//	pair.second->EndPlay();
	//}
    CNonInteractiveUIComponent::EndPlay();
}

void CTextUIComponent::Release()
{
	//for (auto& pair : m_umapElements)
	//{
	//	pair.second->Release();
	//}
    CNonInteractiveUIComponent::Release();
}


