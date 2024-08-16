#include "pch.h"
#include "TextUI.h"

#include "TextUIComponent.h"
#include "Actor.h"
using namespace std;

void CTextUI::Initialize()
{
	CUI::Initialize();
}

void CTextUI::BeginPlay()
{
	CUI::BeginPlay();
}

int32 CTextUI::Update(const float& _fDeltaSeconds)
{
	return CUI::Update(_fDeltaSeconds);
}

int32 CTextUI::LateUpdate(const float& _fDeltaSeconds)
{
	return CUI::LateUpdate(_fDeltaSeconds);
}

void CTextUI::Render()
{
	CUI::Render();
}

void CTextUI::EndPlay()
{
	CUI::EndPlay();
}

void CTextUI::Release()
{
	CUI::Release();
}

void CTextUI::SetTextUI(std::wstring _wstrText)
{
    int32 iSize = static_cast<int32>(_wstrText.length());
    std::vector<std::weak_ptr<CTextUIComponent>> m_wpTextUIComponent(iSize);

    for (int32 i = 0; i < iSize; ++i) 
    {
        m_wpTextUIComponent[i] = CreateActorComponent<CTextUIComponent>(L"Yellow_Font_UI_"+ i);
		m_wpTextUIComponent[i].lock()->SetIsRootComponent(true);
		m_wpTextUIComponent[i].lock()->SettingUserInterfaceInfo(L"Yellow_Font_UI_" + i, 0, 25, L"Yellow_Font_UI_" + i, EUserInterfaceType::STATIC);
		m_wpTextUIComponent[i].lock()->SetComponentScale({ 20.f + i, 20.f, 0.f });
		m_wpTextUIComponent[i].lock()->SetComponentLocalPosition({ 0.f, 0.f, 0.f });
		m_wpTextUIComponent[i].lock()->SetCurrentUI(0);
    }


}

//void CUI::SetUINumber(const int32& _iCurFrame)
//{
//}


