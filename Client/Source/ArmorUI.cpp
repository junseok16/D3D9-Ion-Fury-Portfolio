#include "pch.h"
#include "ArmorUI.h"

#include "UIComponent.h"
#include "SpriteUIComponent.h"

using namespace std;

void CArmorUI::Initialize()
{
	//////////////////백의 자리
	//m_wpUIHpHundredsPlaceComponent = CreateActorComponent<CUIComponent>(L"UI_Hp_Hundreds_Place_Component");
	//m_wpUIHpHundredsPlaceComponent.lock()->SetIsRootComponent(true);
	//m_wpUIHpHundredsPlaceComponent.lock()->SettingUserInterfaceInfo(L"Num_", 0, 20, L"Hp_Hundreds_Place", EUserInterfaceType::STATIC);
	//m_wpUIHpHundredsPlaceComponent.lock()->SetComponentScale({ 7.f, 8.f, 10.f });
	//m_wpUIHpHundredsPlaceComponent.lock()->SetComponentLocalPosition({ -21.f, -3.f, 0.f });
	//
	/////////////////십의 자리
	//m_wpUIHpTensPlaceComponent = CreateActorComponent<CUIComponent>(L"UI_Hp_Tens_Place_Component");
	//m_wpUIHpTensPlaceComponent.lock()->SetIsRootComponent(true);
	//m_wpUIHpTensPlaceComponent.lock()->SettingUserInterfaceInfo(L"Num_", 0, 10, L"Hp_Tens_Place", EUserInterfaceType::STATIC);
	//m_wpUIHpTensPlaceComponent.lock()->SetComponentScale({ 7.f, 8.f, 10.f });
	//m_wpUIHpTensPlaceComponent.lock()->SetComponentLocalPosition({ -14.f, -3.f, 0.f });
	//
	/////////////////일의 자리
	//m_wpUIHpOnesPlaceComponent = CreateActorComponent<CUIComponent>(L"UI_Hp_Ones_Place_Component");
	//m_wpUIHpOnesPlaceComponent.lock()->SetIsRootComponent(true);
	//m_wpUIHpOnesPlaceComponent.lock()->SettingUserInterfaceInfo(L"Num_", 0, 10, L"Hp_Ones_Place", EUserInterfaceType::STATIC);
	//m_wpUIHpOnesPlaceComponent.lock()->SetComponentScale({ 7.f, 8.f, 10.f });
	//m_wpUIHpOnesPlaceComponent.lock()->SetComponentLocalPosition({ -7.f, -3.f, 0.f });
	//
	///////////////// 아머 상태 ///////////////
	//m_wpArmorUIComponent = CreateActorComponent<CUIComponent>(L"Armor_UI");
	//m_wpArmorUIComponent.lock()->SetIsRootComponent(true);
	//m_wpArmorUIComponent.lock()->SettingUserInterfaceInfo(L"Armor_UI_", 0, 1, L"Armor_UI_", EUserInterfaceType::STATIC);
	//m_wpArmorUIComponent.lock()->SetComponentScale({ 14.f, 14.f, 10.f });
	//m_wpArmorUIComponent.lock()->SetComponentLocalPosition({ -32.f, -2.f, 0.f });
	//m_wpArmorUIComponent.lock()->SetCurrentUI(0);

	//// 크로스헤어 UI 스프라이트
	//m_wpCrossHairUIComponent = CreateActorComponent<CSpriteUIComponent>(L"SpriteComponent");
	//m_wpCrossHairUIComponent.lock()->SetIsRootComponent(true);
	//m_wpCrossHairUIComponent.lock()->SettingUserInterfaceInfo(L"CrossHair_UI_", 0, 2, L"CrossHair_UI_", EUserInterfaceType::STATIC);
	//m_wpCrossHairUIComponent.lock()->SetComponentLocalPosition({ 0.0f, 0.0f, 10.0f });
	//m_wpCrossHairUIComponent.lock()->SetComponentScale({ 10.0f, 10.0f, 0.0f });
	//m_wpCrossHairUIComponent.lock()->SetCurrentUI(0);

	//원하는 숫자 텍스쳐 지정
	//SetUINumber(89);
	SetRenderType(ERenderType::USER_INTERFACE);
	CUI::Initialize();
}

void CArmorUI::BeginPlay()
{
	//백의 자리
	m_wpUIHpOnesPlaceComponent.lock()->AddUIState(L"Hp_Hundreds_Place", 0, 10);

	//십의 자리
	m_wpUIHpTensPlaceComponent.lock()->AddUIState(L"Hp_Tens_Place", 0, 10);

	//일의 자리
	m_wpUIHpOnesPlaceComponent.lock()->AddUIState(L"Hp_Ones_Place", 0, 10);

	//Armor UI
	m_wpArmorUIComponent.lock()->AddUIState(L"Armor_UI_", 0, 1);


	//m_wpCrossHairUIComponent.lock()->AddUIState(L"CrossHair_UI_", 0, 2);

	CUI::BeginPlay();
}

int32 CArmorUI::Update(const float& _fDeltaSeconds)
{
	return CUI::Update(_fDeltaSeconds);
}

int32 CArmorUI::LateUpdate(const float& _fDeltaSeconds)
{
	return CUI::LateUpdate(_fDeltaSeconds);
}

void CArmorUI::Render()
{
	CUI::Render();
}

void CArmorUI::EndPlay()
{
	CUI::EndPlay();
}

void CArmorUI::Release()
{
	CUI::Release();
}

//void CArmorUI::SetUINumber(const int32& _iCurFrame)
//{
//	int32 Num[3];
//	string strNum = to_string(_iCurFrame);
//
//	if (_iCurFrame <= 999 && _iCurFrame >= 0) {
//		if (_iCurFrame > 99 && _iCurFrame <= 999) {
//			Num[0] = strNum[0] - '0';
//			Num[1] = strNum[1] - '0';
//			Num[2] = strNum[2] - '0';
//		}
//		else if (_iCurFrame > 9 && _iCurFrame <= 99) {
//			Num[0] = 10;
//			Num[1] = strNum[0] - '0';
//			Num[2] = strNum[1] - '0';
//		}
//		else if (_iCurFrame >= 0 && _iCurFrame <= 9) {
//			Num[0] = 10;
//			Num[1] = 10;
//			Num[2] = strNum[0] - '0';
//		}
//	}
//	else {
//		Num[0] = 10;
//		Num[1] = 10;
//		Num[2] = 10;
//	}
//	m_wpUIHpHundredsPlaceComponent.lock()->SetCurrentUI(Num[0]);
//	m_wpUIHpTensPlaceComponent.lock()->SetCurrentUI(Num[1]);
//	m_wpUIHpOnesPlaceComponent.lock()->SetCurrentUI(Num[2]);
//}
