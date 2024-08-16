#include "pch.h"
#include "PlayerUI.h"

#include "UIComponent.h"

using namespace std;

void CPlayerUI::Initialize()
{
	//////////////////백의 자리
	//m_wpUIHpHundredsPlaceComponent = CreateActorComponent<CUIComponent>(L"UI_Hp_Hundreds_Place_Component");
	//m_wpUIHpHundredsPlaceComponent.lock()->SetIsRootComponent(true);
	//m_wpUIHpHundredsPlaceComponent.lock()->SettingUserInterfaceInfo(L"Num_", 0, 10,  L"Hp_Hundreds_Place", EUserInterfaceType::STATIC);
	//m_wpUIHpHundredsPlaceComponent.lock()->SetComponentScale({ 7.f, 8.f, 10.f });
	//m_wpUIHpHundredsPlaceComponent.lock()->SetComponentLocalPosition({ -40.f, -3.f, 0.f });
	//
	/////////////////십의 자리
	//m_wpUIHpTensPlaceComponent = CreateActorComponent<CUIComponent>(L"UI_Hp_Tens_Place_Component");
	//m_wpUIHpTensPlaceComponent.lock()->SetIsRootComponent(true);
	//m_wpUIHpTensPlaceComponent.lock()->SettingUserInterfaceInfo(L"Num_", 0, 10, L"Hp_Tens_Place", EUserInterfaceType::STATIC);
	//m_wpUIHpTensPlaceComponent.lock()->SetComponentScale({ 7.f, 8.f, 10.f });
	//m_wpUIHpTensPlaceComponent.lock()->SetComponentLocalPosition({ -33.f, -3.f, 0.f });
	//
	/////////////////일의 자리
	//m_wpUIHpOnesPlaceComponent = CreateActorComponent<CUIComponent>(L"UI_Hp_Ones_Place_Component");
	//m_wpUIHpOnesPlaceComponent.lock()->SetIsRootComponent(true);
	//m_wpUIHpOnesPlaceComponent.lock()->SettingUserInterfaceInfo( L"Num_", 0, 10, L"Hp_Ones_Place", EUserInterfaceType::STATIC);
	//m_wpUIHpOnesPlaceComponent.lock()->SetComponentScale({ 7.f, 8.f, 10.f });
	//m_wpUIHpOnesPlaceComponent.lock()->SetComponentLocalPosition({ -26.f, -3.f, 0.f });


	///////////////////플레이어 얼굴 표정///////////////
	//m_wpPlayerUIComponent = CreateActorComponent<CUIComponent>(L"Player_UI");
	//m_wpPlayerUIComponent.lock()->SetIsRootComponent(true);
	//m_wpPlayerUIComponent.lock()->SettingUserInterfaceInfo(L"Player_UI_", 0, 24, L"Player_UI_", EUserInterfaceType::STATIC);
	//m_wpPlayerUIComponent.lock()->SetComponentScale({ 16.f, 16.f, 10.f });
	//m_wpPlayerUIComponent.lock()->SetComponentLocalPosition({ -50.f, -2.f, 0.f });
	//m_wpPlayerUIComponent.lock()->SetCurrentUI(1);

	//원하는 숫자 텍스쳐 지정
	//SetUINumber(100);
	SetRenderType(ERenderType::USER_INTERFACE);
	CUI::Initialize();
}

void CPlayerUI::BeginPlay()
{
	//백의 자리
	m_wpUIHpHundredsPlaceComponent.lock()->AddUIState(L"Hp_Hundreds_Place", 0, 10);

	//십의 자리
	m_wpUIHpTensPlaceComponent.lock()->AddUIState(L"Hp_Tens_Place", 0, 10);

	//일의 자리
	m_wpUIHpOnesPlaceComponent.lock()->AddUIState(L"Hp_Ones_Place", 0, 10);

	//플레이어 표정
	m_wpPlayerUIComponent.lock()->AddUIState(L"Player_UI_", 0, 24);

	CUI::BeginPlay();
}

int32 CPlayerUI::Update(const float& _fDeltaSeconds)
{
	return CUI::Update(_fDeltaSeconds);
}

int32 CPlayerUI::LateUpdate(const float& _fDeltaSeconds)
{
	return CUI::LateUpdate(_fDeltaSeconds);
}

void CPlayerUI::Render()
{
	CUI::Render();
}

void CPlayerUI::EndPlay()
{
	CUI::EndPlay();
}

void CPlayerUI::Release()
{
	CUI::Release();
}

//oid CPlayerUI::SetUINumber(const int32& _iCurFrame)
//
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
//
