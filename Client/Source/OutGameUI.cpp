#include "pch.h"
#include "OutGameUI.h"

#include "World.h"
#include "Level.h"
#include "Stage2.h"

#include "InputManager.h"
#include "CollisionManager.h"

#include "Actor.h"
#include "LeverBox.h"
#include "PlayerActor.h"
#include "WeaponActor.h"
#include "RecoveryActor.h"

#include "SoundComponent.h"
#include "TextUIComponent.h"
#include "SpriteUIComponent.h"
#include "CubeColliderComponent.h"

void COutGameUI::Initialize()
{
	OutGameUISetting();

	SetRenderType(ERenderType::USER_INTERFACE);
	CUI::Initialize();
}

void COutGameUI::BeginPlay()
{
	m_wpPlayerActor = dynamic_pointer_cast<CPlayerActor>(GetLevel().lock()->FindActor(L"Player"));
	m_wpLeverBoxActor = dynamic_pointer_cast<CLeverBox>(GetLevel().lock()->FindActor(L"LeverBox"));
	m_wpRecoveryActor = dynamic_pointer_cast<CRecoveryActor>(GetLevel().lock()->FindActor(L"Recovery"));
	OutGameUIBegingPlaySetting();

	CUI::BeginPlay();
}

int32 COutGameUI::Update(const float& _fDeltaSeconds)
{
	// UI 관련된 코드, 플레이어 HP,아머 체력 상태, 잔탄수, 숫자 설정 
	SetPlayerUINumber((int32)m_wpPlayerActor.lock()->GetCurHp());
	SetPlayerIconUI((int32)m_wpPlayerActor.lock()->GetCurHp());
	SetBulletUINumber(m_wpPlayerActor.lock()->GetCurrentWeapon().lock()->GetCurBullet());
	SetBulletIconUI(m_wpPlayerActor.lock()->GetCurrentWeapon().lock()->GetWeaponType());

	SetArmorUINumber((int32)m_wpPlayerActor.lock()->GetCurArmor());
	SetArmorIconUI((int32)m_wpPlayerActor.lock()->GetMaxArmor());
	SetItemIconUI((int32)m_wpPlayerActor.lock()->GetCardKeyItem());

	KeyInput();
	InteractiveBoxTextUI();
	return CUI::Update(_fDeltaSeconds);
}

int32 COutGameUI::LateUpdate(const float& _fDeltaSeconds)
{
	return CUI::LateUpdate(_fDeltaSeconds);
}

void COutGameUI::Render()
{
	CUI::Render();
}

void COutGameUI::EndPlay()
{
	CUI::EndPlay();
}

void COutGameUI::Release()
{
	CUI::Release();
}

void COutGameUI::OutGameUISetting()
{
	m_wpCrossHairUIComponent = CreateActorComponent<CSpriteUIComponent>(L"CrossHair_UI_");
	m_wpCrossHairUIComponent.lock()->SettingUserInterfaceInfo(L"CrossHair_UI_", 0, 2, L"CrossHair_UI_", EUserInterfaceType::STATIC);
	m_wpCrossHairUIComponent.lock()->SetComponentScale({ 25.f, 25.f, 0.f });
	m_wpCrossHairUIComponent.lock()->SetComponentLocalPosition({ 0.f, 0.f, 0.f });
	m_wpCrossHairUIComponent.lock()->SetCurrentUI(0);
	SetRootComponent(m_wpCrossHairUIComponent);

	m_wpCrossHairRedUIComponent = CreateActorComponent<CSpriteUIComponent>(L"CrossHair_Red_UI_");
	m_wpCrossHairRedUIComponent.lock()->SetIsRootComponent(true);
	m_wpCrossHairRedUIComponent.lock()->SettingUserInterfaceInfo(L"CrossHair_UI_", 0, 2, L"CrossHair_UI_", EUserInterfaceType::STATIC);
	m_wpCrossHairRedUIComponent.lock()->SetComponentScale({ 25.f, 25.f, 0.f });
	m_wpCrossHairRedUIComponent.lock()->SetComponentLocalPosition({ 0.f, 0.f, 0.f });
	m_wpCrossHairRedUIComponent.lock()->SetCurrentUI(2);

	m_wpPlayerUIComponent = CreateActorComponent<CSpriteUIComponent>(L"Player_UI_");
	m_wpPlayerUIComponent.lock()->SetIsRootComponent(true);
	m_wpPlayerUIComponent.lock()->SettingUserInterfaceInfo(L"Player_UI_", 0, 24, L"Player_UI_", EUserInterfaceType::STATIC);
	m_wpPlayerUIComponent.lock()->SetComponentScale({ 100.f, 100.f, 0.f });
	m_wpPlayerUIComponent.lock()->SetComponentLocalPosition({ -605.f, -310.f, 0.f });
	m_wpPlayerUIComponent.lock()->SetCurrentUI(0);

	m_wpBulletUIComponent = CreateActorComponent<CSpriteUIComponent>(L"Weapon_UI_Bullet_");
	m_wpBulletUIComponent.lock()->SetIsRootComponent(true);
	m_wpBulletUIComponent.lock()->SettingUserInterfaceInfo(L"Weapon_UI_Bullet_", 0, 4, L"Weapon_UI_Bullet_", EUserInterfaceType::STATIC);
	m_wpBulletUIComponent.lock()->SetComponentScale({ 50.f, 50.f, 0.f });
	m_wpBulletUIComponent.lock()->SetComponentLocalPosition({ 595.f, -318.f, 0.f });
	m_wpBulletUIComponent.lock()->SetCurrentUI(1);

	m_wpArmorUIComponent = CreateActorComponent<CSpriteUIComponent>(L"Armor_UI_");
	m_wpArmorUIComponent.lock()->SetIsRootComponent(true);
	m_wpArmorUIComponent.lock()->SettingUserInterfaceInfo(L"Armor_UI_", 0, 3, L"Armor_UI_", EUserInterfaceType::STATIC);
	m_wpArmorUIComponent.lock()->SetComponentScale({ 80.f, 80.f, 0.f });
	m_wpArmorUIComponent.lock()->SetComponentLocalPosition({ -420.f, -318.f, 0.f });
	m_wpArmorUIComponent.lock()->SetCurrentUI(3);

	m_wpItemUIComponent = CreateActorComponent<CSpriteUIComponent>(L"Item_UI_");
	m_wpItemUIComponent.lock()->SetIsRootComponent(true);
	m_wpItemUIComponent.lock()->SettingUserInterfaceInfo(L"Item_UI_", 0, 5, L"Item_UI_", EUserInterfaceType::STATIC);
	m_wpItemUIComponent.lock()->SetComponentScale({ 60.f, 50.f, 0.f });
	m_wpItemUIComponent.lock()->SetComponentLocalPosition({ -603.f, -225.f, 0.f });
	m_wpItemUIComponent.lock()->SetCurrentUI(2);

	m_wpItemTextComponent = CreateActorComponent<CSpriteUIComponent>(L"Item_Skill_Text_UI_");
	m_wpItemTextComponent.lock()->SetIsRootComponent(true);
	m_wpItemTextComponent.lock()->SettingUserInterfaceInfo(L"Yellow_Font_UI_", 0, 26, L"Yellow_Font_UI_", EUserInterfaceType::STATIC);
	m_wpItemTextComponent.lock()->SetComponentScale({ 20.f, 20.f, 0.f });
	m_wpItemTextComponent.lock()->SetComponentLocalPosition({ -575.f, -245.f, 0.f });
	m_wpItemTextComponent.lock()->SetCurrentUI(23);

	m_wpItemNumComponent = CreateActorComponent<CSpriteUIComponent>(L"Item_Skill_Num_UI_");
	m_wpItemNumComponent.lock()->SetIsRootComponent(true);
	m_wpItemNumComponent.lock()->SettingUserInterfaceInfo(L"Yellow_Font_Num_UI_", 0, 10, L"Yellow_Font_Num_UI_", EUserInterfaceType::STATIC);
	m_wpItemNumComponent.lock()->SetComponentScale({ 25.f, 30.f, 0.f });
	m_wpItemNumComponent.lock()->SetComponentLocalPosition({ -550.f, -241.f, 0.f });
	m_wpItemNumComponent.lock()->SetCurrentUI(5);

	m_wpBossBarComponent = CreateActorComponent<CSpriteUIComponent>(L"Boss_Bar_");
	m_wpBossBarComponent.lock()->SetIsRootComponent(true);
	m_wpBossBarComponent.lock()->SettingUserInterfaceInfo(L"Boss_Bar_", 0, 1, L"Boss_Bar_", EUserInterfaceType::STATIC);
	m_wpBossBarComponent.lock()->SetComponentScale({ 225.f, 35.f, 0.f });
	m_wpBossBarComponent.lock()->SetComponentLocalPosition({ 0.f, 300.f, 0.f });
	m_wpBossBarComponent.lock()->SetCurrentUI(0);

	m_wpBossHpBarComponent = CreateActorComponent<CSpriteUIComponent>(L"Boss_Hp_Bar_");
	m_wpBossHpBarComponent.lock()->SetIsRootComponent(true);
	m_wpBossHpBarComponent.lock()->SettingUserInterfaceInfo(L"Boss_Hp_Bar_", 0, 1, L"Boss_Hp_Bar_", EUserInterfaceType::STATIC);
	m_wpBossHpBarComponent.lock()->SetComponentScale({ 225.f, 35.f, 0.f });
	m_wpBossHpBarComponent.lock()->SetComponentLocalPosition({ 0.f, 300.f, 0.f });
	m_wpBossHpBarComponent.lock()->SetCurrentUI(0);



	////////////백의 자리
	m_wpPlayerHpHundredsPlaceComponent = CreateActorComponent<CSpriteUIComponent>(L"Yellow_Font_Num_UI_1");
	m_wpPlayerHpHundredsPlaceComponent.lock()->SetIsRootComponent(true);
	m_wpPlayerHpHundredsPlaceComponent.lock()->SettingUserInterfaceInfo(L"Yellow_Font_Num_UI_", 0, 10, L"Yellow_Font_Num_UI_", EUserInterfaceType::STATIC);
	m_wpPlayerHpHundredsPlaceComponent.lock()->SetComponentScale({ 35.f, 40.f, 0.f });
	m_wpPlayerHpHundredsPlaceComponent.lock()->SetComponentLocalPosition({ -550.f, -318.f, 0.f });
	///////////////십의 자리
	m_wpPlayerHpTensPlaceComponent = CreateActorComponent<CSpriteUIComponent>(L"Yellow_Font_Num_UI_2");
	m_wpPlayerHpTensPlaceComponent.lock()->SetIsRootComponent(true);
	m_wpPlayerHpTensPlaceComponent.lock()->SettingUserInterfaceInfo(L"Yellow_Font_Num_UI_", 0, 10, L"Yellow_Font_Num_UI_", EUserInterfaceType::STATIC);
	m_wpPlayerHpTensPlaceComponent.lock()->SetComponentScale({ 35.f, 40.f, 0.f });
	m_wpPlayerHpTensPlaceComponent.lock()->SetComponentLocalPosition({ -514.f, -318.f, 0.f });
	///////////////일의 자리
	m_wpPlayerHpOnesPlaceComponent = CreateActorComponent<CSpriteUIComponent>(L"Yellow_Font_Num_UI_3");
	m_wpPlayerHpOnesPlaceComponent.lock()->SetIsRootComponent(true);
	m_wpPlayerHpOnesPlaceComponent.lock()->SettingUserInterfaceInfo(L"Yellow_Font_Num_UI_", 0, 10, L"Yellow_Font_Num_UI_", EUserInterfaceType::STATIC);
	m_wpPlayerHpOnesPlaceComponent.lock()->SetComponentScale({ 35.f, 40.f, 0.f });
	m_wpPlayerHpOnesPlaceComponent.lock()->SetComponentLocalPosition({ -479.f, -318.f, 0.f });
	SetPlayerUINumber(109);



	////////////백의 자리
	m_wpArmorHpHundredsPlaceComponent = CreateActorComponent<CSpriteUIComponent>(L"Yellow_Font_Num_UI_4");
	m_wpArmorHpHundredsPlaceComponent.lock()->SetIsRootComponent(true);
	m_wpArmorHpHundredsPlaceComponent.lock()->SettingUserInterfaceInfo(L"Yellow_Font_Num_UI_", 0, 10, L"Yellow_Font_Num_UI_", EUserInterfaceType::STATIC);
	m_wpArmorHpHundredsPlaceComponent.lock()->SetComponentScale({ 35.f, 40.f, 0.f });
	m_wpArmorHpHundredsPlaceComponent.lock()->SetComponentLocalPosition({ -360.f, -318.f, 0.f });
	///////////////십의 자리
	m_wpArmorHpTensPlaceComponent = CreateActorComponent<CSpriteUIComponent>(L"Yellow_Font_Num_UI_5");
	m_wpArmorHpTensPlaceComponent.lock()->SetIsRootComponent(true);
	m_wpArmorHpTensPlaceComponent.lock()->SettingUserInterfaceInfo(L"Yellow_Font_Num_UI_", 0, 10, L"Yellow_Font_Num_UI_", EUserInterfaceType::STATIC);
	m_wpArmorHpTensPlaceComponent.lock()->SetComponentScale({ 35.f, 40.f, 0.f });
	m_wpArmorHpTensPlaceComponent.lock()->SetComponentLocalPosition({ -324.f, -318.f, 0.f });
	///////////////일의 자리
	m_wpArmorHpOnesPlaceComponent = CreateActorComponent<CSpriteUIComponent>(L"Yellow_Font_Num_UI_6");
	m_wpArmorHpOnesPlaceComponent.lock()->SetIsRootComponent(true);
	m_wpArmorHpOnesPlaceComponent.lock()->SettingUserInterfaceInfo(L"Yellow_Font_Num_UI_", 0, 10, L"Yellow_Font_Num_UI_", EUserInterfaceType::STATIC);
	m_wpArmorHpOnesPlaceComponent.lock()->SetComponentScale({ 35.f, 40.f, 0.f });
	m_wpArmorHpOnesPlaceComponent.lock()->SetComponentLocalPosition({ -289.f, -318.f, 0.f });
	SetArmorUINumber(109);

	//
	////////////////백의 자리
	m_wpBulletHpHundredsPlaceComponent = CreateActorComponent<CSpriteUIComponent>(L"Yellow_Font_Num_UI_7");
	m_wpBulletHpHundredsPlaceComponent.lock()->SetIsRootComponent(true);
	m_wpBulletHpHundredsPlaceComponent.lock()->SettingUserInterfaceInfo(L"Yellow_Font_Num_UI_", 0, 10, L"Yellow_Font_Num_UI_", EUserInterfaceType::STATIC);
	m_wpBulletHpHundredsPlaceComponent.lock()->SetComponentScale({ 35.f, 40.f, 0.f });
	m_wpBulletHpHundredsPlaceComponent.lock()->SetComponentLocalPosition({ 473.f, -318.f, 0.f });
	///////////////십의 자리
	m_wpBulletHpTensPlaceComponent = CreateActorComponent<CSpriteUIComponent>(L"Yellow_Font_Num_UI_8");
	m_wpBulletHpTensPlaceComponent.lock()->SetIsRootComponent(true);
	m_wpBulletHpTensPlaceComponent.lock()->SettingUserInterfaceInfo(L"Yellow_Font_Num_UI_", 0, 10, L"Yellow_Font_Num_UI_", EUserInterfaceType::STATIC);
	m_wpBulletHpTensPlaceComponent.lock()->SetComponentScale({ 35.f, 40.f, 0.f });
	m_wpBulletHpTensPlaceComponent.lock()->SetComponentLocalPosition({ 508.f, -318.f, 0.f });
	///////////////일의 자리
	m_wpBulletHpOnesPlaceComponent = CreateActorComponent<CSpriteUIComponent>(L"Yellow_Font_Num_UI_9");
	m_wpBulletHpOnesPlaceComponent.lock()->SetIsRootComponent(true);
	m_wpBulletHpOnesPlaceComponent.lock()->SettingUserInterfaceInfo(L"Yellow_Font_Num_UI_", 0, 10, L"Yellow_Font_Num_UI_", EUserInterfaceType::STATIC);
	m_wpBulletHpOnesPlaceComponent.lock()->SetComponentScale({ 35.f, 40.f, 0.f });
	m_wpBulletHpOnesPlaceComponent.lock()->SetComponentLocalPosition({ 544.f, -318.f, 0.f });
	SetBulletUINumber(999);

	SetInitTextUI(m_vecInteractiveBoxUIComponent, L"PRESS F TO UNLOCK THIS TERMINAL", L"Yellow_Font_UI_InteractiveBox", L"Yellow_Font_UI_", 13.f, 18.f, -190.f, -200.f);
	
	std::wstring wstrText = L"PRESS F TO UNLOCK THIS TERMINAL";
	int32 iSize = static_cast<int32>(wstrText.length());
	
	for (int32 i = 0; i < iSize; ++i)
	{
		m_vecInteractiveBoxUIComponent[i].lock()->SetCurrentUI(26);
	}


	//SetInitNumberUI(m_vecPlayerHpUIComponent, L"100", L"Yellow_Font_Num_UI_0", 35.f, 40.f, -550.f, -318.f);
	//SetInitNumberUI(m_vecArmorHpUIComponent, L"109", L"Yellow_Font_Num_UI_1", 35.f, 40.f, -360.f, -318.f);
	//SetInitNumberUI(m_vecBulletHpUIComponent, L"109", L"Yellow_Font_Num_UI_2", 35.f, 40.f, 473.f, -318.f);
}

void COutGameUI::OutGameUIBegingPlaySetting()
{
	m_wpCrossHairUIComponent.lock()->AddUIState(L"CrossHair_UI_", 0, 2);

	m_wpCrossHairRedUIComponent.lock()->AddUIState(L"CrossHair_Red_UI_", 0, 2);

	m_wpPlayerUIComponent.lock()->AddUIState(L"Player_UI_", 0, 24);

	m_wpBulletUIComponent.lock()->AddUIState(L"Weapon_UI_Bullet_", 0, 4);

	m_wpArmorUIComponent.lock()->AddUIState(L"Armor_UI_", 0, 2);

	m_wpItemUIComponent.lock()->AddUIState(L"Item_UI_", 0, 5);

	// 아이템 숫자
	m_wpItemNumComponent.lock()->AddUIState(L"Yellow_Font_Num_UI_", 0, 10);

	// 아이템 x 
	m_wpItemTextComponent.lock()->AddUIState(L"Yellow_Font_UI_", 0, 25);

	// 보스 몬스터 출현시 위에 체력 바
	m_wpBossBarComponent.lock()->AddUIState(L"Boss_Bar_", 0, 1);

	m_wpBossHpBarComponent.lock()->AddUIState(L"Boss_Hp_Bar_", 0, 1);

	//백의 자리
	m_wpPlayerHpHundredsPlaceComponent.lock()->AddUIState(L"Yellow_Font_Num_UI_", 0, 10);

	//십의 자리
	m_wpPlayerHpTensPlaceComponent.lock()->AddUIState(L"Yellow_Font_Num_UI_", 0, 10);

	//일의 자리
	m_wpPlayerHpOnesPlaceComponent.lock()->AddUIState(L"Yellow_Font_Num_UI_", 0, 10);


	m_wpArmorHpHundredsPlaceComponent.lock()->AddUIState(L"Yellow_Font_Num_UI_", 0, 10);

	//십의 자리
	m_wpArmorHpTensPlaceComponent.lock()->AddUIState(L"Yellow_Font_Num_UI_", 0, 10);

	////일의 자리
	m_wpArmorHpOnesPlaceComponent.lock()->AddUIState(L"Yellow_Font_Num_UI_", 0, 10);

	m_wpBulletHpHundredsPlaceComponent.lock()->AddUIState(L"Yellow_Font_Num_UI_", 0, 10);

	//십의 자리
	m_wpBulletHpTensPlaceComponent.lock()->AddUIState(L"Yellow_Font_Num_UI_", 0, 10);

	////일의 자리
	m_wpBulletHpOnesPlaceComponent.lock()->AddUIState(L"Yellow_Font_Num_UI_", 0, 10);

	SetBeginPlayTextUI(m_vecInteractiveBoxUIComponent, L"PRESS F TO UNLOCK THIS TERMINAL", L"Yellow_Font_UI_InteractiveBox", L"Yellow_Font_UI_");
	//SetBeginPlayNumberUI(m_vecPlayerHpUIComponent, L"100", L"Yellow_Font_Num_UI_0");
	//SetBeginPlayNumberUI(m_vecArmorHpUIComponent, L"109", L"Yellow_Font_Num_UI_1");
	//SetBeginPlayNumberUI(m_vecBulletHpUIComponent, L"109", L"Yellow_Font_Num_UI_2");
	//SetBeginPlayTextUI(m_vecAlphabetUIComponent, L"jusin game academia", L"Silver_Font_UI_1", L"Silver_Font_UI_");
}

void COutGameUI::KeyInput()
{
	// 크로스헤어 빨간색
	if (CInputManager::GetInstance()->IsMousePressed(EMouseButtonType::RIGHT_BUTTON) && m_wpPlayerActor.lock()->GetCurrentWeapon().lock()->GetWeaponType()==EWeaponType::LOVERBOY)
	{
		m_fRotationZ -= 2.f;
		m_wpCrossHairRedUIComponent.lock()->SetComponentRotation({ 0.f,0.f,m_fRotationZ });
		m_wpCrossHairRedUIComponent.lock()->SetCurrentUI(1);
	}
	else
	{
		m_wpCrossHairRedUIComponent.lock()->SetCurrentUI(2);
	}


	// 보스가 등장했다고 가정하기 위한 if문
	if (CInputManager::GetInstance()->IsKeyDown(DIK_P)/*if(Get_Scene == stage3*/)
	{
		m_wpBossBarComponent.lock()->SetCurrentUI(1);
		m_wpBossHpBarComponent.lock()->SetCurrentUI(1);
	}

	
	// 보스 몬스터 제력바를 위한 테스트 용 코드입니다 
	if (CInputManager::GetInstance()->IsKeyDown(DIK_K))
	{
		float fScaleX = m_wpBossHpBarComponent.lock()->GetComponentScale().x;
		float fHpBarPosX = m_wpBossHpBarComponent.lock()->GetComponentLocalPosition().x;

		// 받아온 플레이어 공격력을 특정 비율값을 곱해줌
		float fAtkRatio = 300.f * m_fDamagePerHit;

		// 특정 공격력 비율을 가지고 Hp바의 위치값을 조정해줌
		float fHpBarPosRatio = fAtkRatio * (2.f / 5.f);

		fScaleX -= fAtkRatio;
		fHpBarPosX -= fHpBarPosRatio;
		m_wpBossHpBarComponent.lock()->SetComponentScale({ fScaleX, 35.f, 0.f });
		m_wpBossHpBarComponent.lock()->SetComponentLocalPosition({ fHpBarPosX , 300.f, 0.f });
	}
	
}

void COutGameUI::SetAlphabetSprites(const std::vector<std::weak_ptr<CTextUIComponent>>& _vecAlphabetComponents, const std::wstring& _wstrText)
{
	int32 iSize = static_cast<int32>(_wstrText.length());
	
	for (int32 i = 0; i < iSize; ++i)
	{	
		//auto lockedComponent = _vecAlphabetComponents[i].lock();
	
		std::shared_ptr<CTextUIComponent> vecAlphabetComponents = _vecAlphabetComponents[i].lock();
	
		if (vecAlphabetComponents)
		{
			if (i < _wstrText.length())
			{
				wchar_t wcAlphabet = _wstrText[i];
				int32 iNumValue = (int32)(wcAlphabet - L'A'); // 'A'부터의 거리를 구해서 숫자로 변환
				vecAlphabetComponents->SetCurrentUI(iNumValue);
			}
			else
			{
				// 벡터 컨테이너의 크기보다 텍스트의 길이가 짧을 때, 나머지 컴포넌트는 숨기거나 초기화할 수 있습니다.
				vecAlphabetComponents->SetCurrentUI(26);/* 어떤 초기값으로 설정할지 결정 */
			}
		}
	}
}

void COutGameUI::SetAlphabetSprites1(const std::wstring& _wstrText)
{
	//int32 iSize = static_cast<int32>(_wstrText.length());
	//
	//SetInitTextUI(m_vecInteractiveBoxUIComponent, _wstrText, L"KeyState",L"Yellow_Font_UI_", 10.f, 10.f, 0.f, 0.f);
	//CUI::Initialize();
}

void COutGameUI::SetPlayerUINumber(const int32& _iCurFrame)
{
	//int32 Num[3] = {};
	////std::string strNum = std::to_string(_iCurFrame);
	//
	//std::wstring wstrNum = std::to_wstring(m_wpPlayerActor.lock()->GetCurHp());
	//
	//if (_iCurFrame <= 999 && _iCurFrame >= 0) {
	//	if (_iCurFrame > 99 && _iCurFrame <= 999) {
	//		if (_iCurFrame >= 100 && _iCurFrame <= 199) {
	//			m_wpPlayerHpTensPlaceComponent.lock()->SetComponentLocalPosition({ -520.f, -318.f, 0.f });
	//			m_wpPlayerHpOnesPlaceComponent.lock()->SetComponentLocalPosition({ -485.f, -318.f, 0.f });
	//		}
	//		else {
	//			m_wpPlayerHpTensPlaceComponent.lock()->SetComponentLocalPosition({ -514.f, -318.f, 0.f });
	//			m_wpPlayerHpOnesPlaceComponent.lock()->SetComponentLocalPosition({ -479.f, -318.f, 0.f });
	//			SetInitNumberUI(m_vecPlayerHpUIComponent, wstrNum, L"Yellow_Font_Num_UI_0", 35.f, 40.f, -550.f, -318.f);
	//
	//			//SetBeginPlayNumberUI(m_vecPlayerHpUIComponent, L"100", L"Yellow_Font_Num_UI_0");
	//		}
	//		Num[0] = strNum[0] - '0';
	//		Num[1] = strNum[1] - '0';
	//		Num[2] = strNum[2] - '0';
	//	}
	//	else if (_iCurFrame > 9 && _iCurFrame <= 99) {
	//		if (_iCurFrame >= 10 && _iCurFrame <= 19) {
	//			m_wpPlayerHpTensPlaceComponent.lock()->SetComponentLocalPosition({ -520.f, -318.f, 0.f });
	//			m_wpPlayerHpOnesPlaceComponent.lock()->SetComponentLocalPosition({ -485.f, -318.f, 0.f });
	//		}
	//		else {
	//			m_wpPlayerHpTensPlaceComponent.lock()->SetComponentLocalPosition({ -514.f, -318.f, 0.f });
	//			m_wpPlayerHpOnesPlaceComponent.lock()->SetComponentLocalPosition({ -479.f, -318.f, 0.f });
	//		}
	//		Num[0] = strNum[0] - '0';
	//		Num[1] = strNum[1] - '0';
	//		Num[2] = 10;
	//	}
	//	else if (_iCurFrame >= 0 && _iCurFrame <= 9) {
	//		Num[0] = strNum[0] - '0';
	//		Num[1] = 10;
	//		Num[2] = 10;
	//	}
	//}
	//else {
	//	Num[0] = 10;
	//	Num[1] = 10;
	//	Num[2] = 10;
	//}


	int32 Num[3] = {};
	std::string strNum = std::to_string(_iCurFrame);

	if (_iCurFrame <= 999 && _iCurFrame >= 0)
	{
		if (99 < _iCurFrame && _iCurFrame <= 999)
		{
			if (_iCurFrame >= 100 && _iCurFrame <= 199)
			{
				m_wpPlayerHpTensPlaceComponent.lock()->SetComponentLocalPosition({ -520.f, -318.f, 0.f });
				m_wpPlayerHpOnesPlaceComponent.lock()->SetComponentLocalPosition({ -485.f, -318.f, 0.f });
			}
			else {
				m_wpPlayerHpTensPlaceComponent.lock()->SetComponentLocalPosition({ -514.f, -318.f, 0.f });
				m_wpPlayerHpOnesPlaceComponent.lock()->SetComponentLocalPosition({ -479.f, -318.f, 0.f });
			}
			Num[0] = strNum[0] - '0';
			Num[1] = strNum[1] - '0';
			Num[2] = strNum[2] - '0';
		}
		else if (_iCurFrame > 9 && _iCurFrame <= 99)
		{
			if (_iCurFrame >= 10 && _iCurFrame <= 19)
			{
				m_wpPlayerHpTensPlaceComponent.lock()->SetComponentLocalPosition({ -520.f, -318.f, 0.f });
				m_wpPlayerHpOnesPlaceComponent.lock()->SetComponentLocalPosition({ -485.f, -318.f, 0.f });
			}
			else
			{
				m_wpPlayerHpTensPlaceComponent.lock()->SetComponentLocalPosition({ -514.f, -318.f, 0.f });
				m_wpPlayerHpOnesPlaceComponent.lock()->SetComponentLocalPosition({ -479.f, -318.f, 0.f });
			}
			Num[0] = strNum[0] - '0';
			Num[1] = strNum[1] - '0';
			Num[2] = 10;
		}
		else if (_iCurFrame >= 0 && _iCurFrame <= 9)
		{
			Num[0] = strNum[0] - '0';
			Num[1] = 10;
			Num[2] = 10;
		}
	}
	else
	{
		Num[0] = 10;
		Num[1] = 10;
		Num[2] = 10;
	}
	m_wpPlayerHpHundredsPlaceComponent.lock()->SetCurrentUI(Num[0]);
	m_wpPlayerHpTensPlaceComponent.lock()->SetCurrentUI(Num[1]);
	m_wpPlayerHpOnesPlaceComponent.lock()->SetCurrentUI(Num[2]);
}

void COutGameUI::SetArmorUINumber(const int32& _iCurFrame)
{
	int32 Num[3] = {};
	std::string strNum = std::to_string(_iCurFrame);

	if (_iCurFrame <= 999 && _iCurFrame >= 0) {
		if (_iCurFrame > 99 && _iCurFrame <= 999) {
			if (_iCurFrame >= 100 && _iCurFrame <= 199) {
				m_wpArmorHpTensPlaceComponent.lock()->SetComponentLocalPosition({ -330.f, -318.f, 0.f });
				m_wpArmorHpOnesPlaceComponent.lock()->SetComponentLocalPosition({ -295.f, -318.f, 0.f });
			}
			else {
				m_wpArmorHpTensPlaceComponent.lock()->SetComponentLocalPosition({ -324.f, -318.f, 0.f });
				m_wpArmorHpOnesPlaceComponent.lock()->SetComponentLocalPosition({ -289.f, -318.f, 0.f });
			}
			Num[0] = strNum[0] - '0';
			Num[1] = strNum[1] - '0';
			Num[2] = strNum[2] - '0';
		}
		else if (_iCurFrame > 9 && _iCurFrame <= 99) {
			if (_iCurFrame >= 10 && _iCurFrame <= 19) {
				m_wpArmorHpTensPlaceComponent.lock()->SetComponentLocalPosition({ -330.f, -318.f, 0.f });
				m_wpArmorHpOnesPlaceComponent.lock()->SetComponentLocalPosition({ -295.f, -318.f, 0.f });
			}
			else {
				m_wpArmorHpTensPlaceComponent.lock()->SetComponentLocalPosition({ -324.f, -318.f, 0.f });
				m_wpArmorHpOnesPlaceComponent.lock()->SetComponentLocalPosition({ -289.f, -318.f, 0.f });
			}
			Num[0] = strNum[0] - '0';
			Num[1] = strNum[1] - '0';
			Num[2] = 10;
		}
		else if (_iCurFrame >= 0 && _iCurFrame <= 9) {
			Num[0] = strNum[0] - '0';
			Num[1] = 10;
			Num[2] = 10;
		}
	}
	else {
		Num[0] = 10;
		Num[1] = 10;
		Num[2] = 10;
	}

	m_wpArmorHpHundredsPlaceComponent.lock()->SetCurrentUI(Num[0]);
	m_wpArmorHpTensPlaceComponent.lock()->SetCurrentUI(Num[1]);
	m_wpArmorHpOnesPlaceComponent.lock()->SetCurrentUI(Num[2]);
}

void COutGameUI::SetBulletUINumber(const int32& _iCurFrame)
{
	int32 Num[3] = {};
	std::string strNum = std::to_string(_iCurFrame);

	if (_iCurFrame <= 999 && _iCurFrame >= 0) {
		if (_iCurFrame > 99 && _iCurFrame <= 999) {
			//if (_iCurFrame >= 100 && _iCurFrame <= 199) {
			//	m_wpBulletHpHundredsPlaceComponent.lock()->SetComponentLocalPosition({ 479.f, -318.f, 0.f });
			//}
			//else {
			//	m_wpBulletHpHundredsPlaceComponent.lock()->SetComponentLocalPosition({ 473.f, -318.f, 0.f });
			//}
			Num[0] = strNum[0] - '0';
			Num[1] = strNum[1] - '0';
			Num[2] = strNum[2] - '0';
		}
		else if (_iCurFrame > 9 && _iCurFrame <= 99) {
			if (_iCurFrame >= 10 && _iCurFrame <= 19) {
				m_wpBulletHpTensPlaceComponent.lock()->SetComponentLocalPosition({ 514.f, -318.f, 0.f });
			}
			else {
				m_wpBulletHpTensPlaceComponent.lock()->SetComponentLocalPosition({ 508.f, -318.f, 0.f });
			}
			Num[0] = 10;
			Num[1] = strNum[0] - '0';
			Num[2] = strNum[1] - '0';
		}
		else if (_iCurFrame >= 0 && _iCurFrame <= 9) {
			Num[0] = 10;
			Num[1] = 10;
			Num[2] = strNum[0] - '0';
		}
	}
	else {
		Num[0] = 10;
		Num[1] = 10;
		Num[2] = 10;
	}
	m_wpBulletHpHundredsPlaceComponent.lock()->SetCurrentUI(Num[0]);
	m_wpBulletHpTensPlaceComponent.lock()->SetCurrentUI(Num[1]);
	m_wpBulletHpOnesPlaceComponent.lock()->SetCurrentUI(Num[2]);
}

void COutGameUI::SetItemUINumber(const int32& _iCurFrame)
{

}

void COutGameUI::SetPlayerIconUI(const int32& _iCurFrame)
{
	if (_iCurFrame > 90 && _iCurFrame <= 100)
	{
		m_wpPlayerUIComponent.lock()->SetCurrentUI(0);
	}
	else if (_iCurFrame > 80 && _iCurFrame <= 90)
	{
		m_wpPlayerUIComponent.lock()->SetCurrentUI(5);
	}
	else if (_iCurFrame > 70 && _iCurFrame <= 80)
	{
		m_wpPlayerUIComponent.lock()->SetCurrentUI(8);
	}
	else if (_iCurFrame > 60 && _iCurFrame <= 70)
	{
		m_wpPlayerUIComponent.lock()->SetCurrentUI(11);
	}
	else if (_iCurFrame > 50 && _iCurFrame <= 60)
	{
		m_wpPlayerUIComponent.lock()->SetCurrentUI(12);
	}
	else if (_iCurFrame > 40 && _iCurFrame <= 50)
	{
		m_wpPlayerUIComponent.lock()->SetCurrentUI(13);
	}
	else if (_iCurFrame > 30 && _iCurFrame <= 40)
	{
		m_wpPlayerUIComponent.lock()->SetCurrentUI(14);
	}
	else if (_iCurFrame > 20 && _iCurFrame <= 30)
	{
		m_wpPlayerUIComponent.lock()->SetCurrentUI(16);
	}
	else if (_iCurFrame > 10 && _iCurFrame <= 20)
	{
		m_wpPlayerUIComponent.lock()->SetCurrentUI(18);
	}
	else if (_iCurFrame > 0 && _iCurFrame <= 10)
	{
		m_wpPlayerUIComponent.lock()->SetCurrentUI(21);
	}
	else if (_iCurFrame == 0)
	{
		m_wpPlayerUIComponent.lock()->SetCurrentUI(23);
	}
}

void COutGameUI::SetArmorIconUI(const int32& _iCurFrame)
{
	if (_iCurFrame == 49.f)
	{
		SetArmorUINumber(1000);
		m_wpArmorUIComponent.lock()->SetCurrentUI(3);
	}
	else if (_iCurFrame == 99.f)
	{
		m_wpArmorUIComponent.lock()->SetCurrentUI(0);
	}
	else if (_iCurFrame == 149.f)
	{
		m_wpArmorUIComponent.lock()->SetCurrentUI(1);
	}
	else if (_iCurFrame == 249.f)
	{
		m_wpArmorUIComponent.lock()->SetCurrentUI(2);
	}
}

void COutGameUI::SetBulletIconUI(EWeaponType _eWeaponType)
{
	switch (_eWeaponType)
	{
	case EWeaponType::ELECTRIFRYER:
		// 1000으로 할 경우 투명으로 바뀜
		SetBulletUINumber(1000);
		m_wpBulletUIComponent.lock()->SetCurrentUI(0);
		break;

	case EWeaponType::LOVERBOY:
		m_wpBulletUIComponent.lock()->SetCurrentUI(1);
		break;

	case EWeaponType::DISPERSER:
		m_wpBulletUIComponent.lock()->SetCurrentUI(2);
		break;

	case EWeaponType::PENETRATOR:
		m_wpBulletUIComponent.lock()->SetCurrentUI(3);
		break;

	case EWeaponType::CHAINGUN:
		m_wpBulletUIComponent.lock()->SetCurrentUI(4);
		if (_eWeaponType == EWeaponType::CHAINGUN) {
			m_wpBulletUIComponent.lock()->SetComponentScale({ 70.f, 50.f, 0.f });
			m_wpBulletUIComponent.lock()->SetComponentLocalPosition({ 600.f, -318.f, 0.f });
		}
		else {
			m_wpBulletUIComponent.lock()->SetComponentScale({ 50.f, 50.f, 0.f });
			m_wpBulletUIComponent.lock()->SetComponentLocalPosition({ 595.f, -318.f, 0.f });
		}
		break;

	case EWeaponType::BOWLINGBOMBS:
		break;

	case EWeaponType::IONBOW:
		break;

	case EWeaponType::CLUSTERPUCK:
		break;

	default:
		break;
	}

}

void COutGameUI::SetItemIconUI(int32 _eItemType)
{
	switch (_eItemType)
	{
	case 0:
		m_wpItemTextComponent.lock()->SetCurrentUI(26);
		m_wpItemNumComponent.lock()->SetCurrentUI(10);
		m_wpItemUIComponent.lock()->SetCurrentUI(2);
		break;

	case 1:
		m_wpItemTextComponent.lock()->SetCurrentUI(26);
		m_wpItemNumComponent.lock()->SetCurrentUI(10);
		m_wpItemUIComponent.lock()->SetCurrentUI(1);
		break;

	case 2:
		m_wpItemTextComponent.lock()->SetCurrentUI(23);
		m_wpItemNumComponent.lock()->SetCurrentUI(2);
		m_wpItemUIComponent.lock()->SetCurrentUI(1);
		break;

	default:
		break;
	}
}

void COutGameUI::SetItemNumIconUI(ESkillType _eSkillType)
{
}

void COutGameUI::SetItemTextIconUI(ESkillType _eSkillType)
{
}

void COutGameUI::InteractiveBoxTextUI()
{
	// 스테이지 1
	if (GetLevel().lock()->GetWorld().lock()->FindLevel(L"Stage1") == GetLevel().lock())
	{
		if ((m_fLeverDis <= 15.f && m_fLeverDis > 0.f) || (m_fCardKeyDis <= 15.f && m_fCardKeyDis > 0.f) || 
			(m_fElevatorButtonDis <= 15.f && m_fElevatorButtonDis > 0.f) || (m_fPowerMonitorDis <= 15.f && m_fPowerMonitorDis > 0.f) ||
			(m_fElevatorButtonDis1 <= 15.f && m_fElevatorButtonDis1 > 0.f) || (m_fPowerMonitorDis1 <= 15.f && m_fPowerMonitorDis1 > 0.f))
		{
			std::wstring wstrText = L"PRESS F TO UNLOCK THIS TERMINAL";
			int32 iSize = static_cast<int32>(wstrText.length());

			for (int32 i = 0; i < iSize; ++i)
			{
				wchar_t wcCurChar = wstrText[i];
				int32 iCurIndex = static_cast<int32>(wcCurChar);

				if (iCurIndex >= 'A' && iCurIndex <= 'Z')
				{
					iCurIndex -= 'A';
				}
				else if (iCurIndex >= 'a' && iCurIndex <= 'z')
				{
					iCurIndex -= 'a';
				}
				else
				{
					iCurIndex = 26;
				}
				m_vecInteractiveBoxUIComponent[i].lock()->SetCurrentUI(iCurIndex);
			}
		}
		else
		{
			std::wstring wstrText = L"PRESS F TO UNLOCK THIS TERMINAL";
			int32 iSize = static_cast<int32>(wstrText.length());

			for (int32 i = 0; i < iSize; ++i)
			{
				m_vecInteractiveBoxUIComponent[i].lock()->SetCurrentUI(26);
			}
		}
	}
	// 스테이지 2
	else if (GetLevel().lock()->GetWorld().lock()->FindLevel(L"Stage2") == GetLevel().lock())
	{

	}
	// 스테이지 3
	else if (GetLevel().lock()->GetWorld().lock()->FindLevel(L"Stage3") == GetLevel().lock())
	{

	}
}

void COutGameUI::InitBossMonsterInfo(float _fMaxHp)
{
	m_fBossMaxHp = _fMaxHp;
	m_fDamagePerHit = m_wpBossHpBarComponent.lock()->GetComponentScale().x / m_fBossMaxHp;
}

void COutGameUI::SetBossMonsterHpBar(float _fPlayerAtk)
{
	float fScaleX = m_wpBossHpBarComponent.lock()->GetComponentScale().x;
	float fHpBarPosX = m_wpBossHpBarComponent.lock()->GetComponentLocalPosition().x;

	// 받아온 플레이어 공격력을 특정 비율값을 곱해줌
	float fAtkRatio = _fPlayerAtk * m_fDamagePerHit;

	// 특정 공격력 비율을 가지고 Hp바의 위치값을 조정해줌
	float fHpBarPosRatio = fAtkRatio * (2.f / 5.f);

	fScaleX -= fAtkRatio;
	fHpBarPosX -= fHpBarPosRatio;
	m_wpBossHpBarComponent.lock()->SetComponentScale({ fScaleX, 35.f, 0.f });
	m_wpBossHpBarComponent.lock()->SetComponentLocalPosition({ fHpBarPosX , 300.f, 0.f });
}

void COutGameUI::ActivateBossHpBar()
{
	m_wpBossBarComponent.lock()->SetCurrentUI(1);
	m_wpBossHpBarComponent.lock()->SetCurrentUI(1);
}
