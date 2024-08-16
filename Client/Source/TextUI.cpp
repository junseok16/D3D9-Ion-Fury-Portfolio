#include "pch.h"
#include "OutGameUI.h"


#include "TextUI.h"
#include "TextUIComponent.h"

void CTextUI::Initialize()
{
	//m_wpTextUIComponent = CreateActorComponent<CTextUIComponent>(L"Yellow_Font_Num_UI_");
	//m_wpTextUIComponent.lock()->SetIsRootComponent(true);
	//m_wpTextUIComponent.lock()->SettingUserInterfaceInfo(L"Yellow_Font_Num_UI_", 0, 9, L"Yellow_Font_Num_UI_", EUserInterfaceType::STATIC);
	//m_wpTextUIComponent.lock()->SetComponentScale({ 50.f, 60.f, 0.f });
	//m_wpTextUIComponent.lock()->SetComponentLocalPosition({ 500.f, -300.f, 0.f });
	//m_wpTextUIComponent.lock()->SetCurrentUI(2);

	SetTextUI(L"LEE");


	SetRenderType(ERenderType::USER_INTERFACE);
	CUI::Initialize();
}

void CTextUI::BeginPlay()
{
	for (int32 i = 0; i < iSize; ++i)
	{
		m_wpTextUIComponent[i].lock()->AddUIState(L"Yellow_Font_Num_UI_" + i, 0, 9);
	}

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

//void CTextUI::SetUINumber(const int32& _iCurFrame)
//{
//	//int32 Num[3];
//	//string strNum = to_string(_iCurFrame);
//	//
//	//if (_iCurFrame <= 999 && _iCurFrame >= 0) {
//	//	if (_iCurFrame > 99 && _iCurFrame <= 999) {
//	//		Num[0] = strNum[0] - '0';
//	//		Num[1] = strNum[1] - '0';
//	//		Num[2] = strNum[2] - '0';
//	//	}
//	//	else if (_iCurFrame > 9 && _iCurFrame <= 99) {
//	//		Num[0] = 10;
//	//		Num[1] = strNum[0] - '0';
//	//		Num[2] = strNum[1] - '0';
//	//	}
//	//	else if (_iCurFrame >= 0 && _iCurFrame <= 9) {
//	//		Num[0] = 10;
//	//		Num[1] = 10;
//	//		Num[2] = strNum[0] - '0';
//	//	}
//	//}
//	//else {
//	//	Num[0] = 10;
//	//	Num[1] = 10;
//	//	Num[2] = 10;
//	//}
//	//m_wpUIHpHundredsPlaceComponent.lock()->SetCurrentUI(Num[0]);
//	//m_wpUIHpTensPlaceComponent.lock()->SetCurrentUI(Num[1]);
//	//m_wpUIHpOnesPlaceComponent.lock()->SetCurrentUI(Num[2]);
//	//CUI::SetUINumber(_iCurFrame);
//}

void CTextUI::SetTextUI(std::wstring _wstrText)
{
	iSize = static_cast<int32>(_wstrText.length());

	for (int32 i = 0; i < iSize; ++i)
	{
		m_wpTextUIComponent[i] = CreateActorComponent<CTextUIComponent>(L"Yellow_Font_UI_" + i);
		m_wpTextUIComponent[i].lock()->SetIsRootComponent(true);
		m_wpTextUIComponent[i].lock()->SettingUserInterfaceInfo(L"Yellow_Font_UI_" + i, 0, 25, L"Yellow_Font_UI_" + i, EUserInterfaceType::STATIC);
		m_wpTextUIComponent[i].lock()->SetComponentScale({ 20.f, 20.f, 0.f });
		m_wpTextUIComponent[i].lock()->SetComponentLocalPosition({ 0.f + i, 0.f, 0.f });
		m_wpTextUIComponent[i].lock()->SetCurrentUI(i);
	}


}
