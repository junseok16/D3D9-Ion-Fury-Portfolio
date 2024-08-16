#include "pch.h"
#include "ItemUI.h"

#include "UIComponent.h"

using namespace std;

void CItemUI::Initialize()
{
	////////////////æ∆¿Ã≈€ UI
	m_wpItemUIComponent = CreateActorComponent<CUIComponent>(L"Item_UI");
	m_wpItemUIComponent.lock()->SetIsRootComponent(true);
	m_wpItemUIComponent.lock()->SettingUserInterfaceInfo(
		L"Item_UI_",
		0, 3,
		L"Item_UI_",
		EUserInterfaceType::STATIC);
	m_wpItemUIComponent.lock()->SetComponentScale({ 13.f, 13.f, 10.f });
	m_wpItemUIComponent.lock()->SetComponentLocalPosition({ 13.f, -2.f, 0.f });
	m_wpItemUIComponent.lock()->SetCurrentUI(2);

	SetRenderType(ERenderType::USER_INTERFACE);
	CUI::Initialize();
}

void CItemUI::BeginPlay()
{
	//ItemUI
	m_wpItemUIComponent.lock()->AddUIState(L"Item_UI_", 0, 3);

	CUI::BeginPlay();
}

int32 CItemUI::Update(const float& _fDeltaSeconds)
{
	return CUI::Update(_fDeltaSeconds);
}

int32 CItemUI::LateUpdate(const float& _fDeltaSeconds)
{
	return CUI::LateUpdate(_fDeltaSeconds);
}

void CItemUI::Render()
{
	CUI::Render();
}

void CItemUI::EndPlay()
{
	CUI::EndPlay();
}

void CItemUI::Release()
{
	CUI::Release();
}

