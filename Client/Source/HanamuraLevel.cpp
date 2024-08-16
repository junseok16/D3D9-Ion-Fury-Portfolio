// default
#include "pch.h"
#include "HanamuraLevel.h"

// framework
#include "World.h"

// manager
#include "DeviceManager.h"
#include "RenderManager.h"
#include "SoundManager.h"

// actor
#include "SunActor.h"
#include "PlayerEffectActor.h"

// weapon
#include "PlayerActor.h"
#include "ElectrifryerActor.h"
#include "LoverboyActor.h"
#include "LoverboyLHActor.h"
#include "DisperserActor.h"
#include "PenetratorActor.h"
#include "ChainGunActor.h"

#include "DisperserItemActor.h"

#include "LoverboyBulletActor.h"
#include "HealthPackActor.h"
#include "SyringeActor.h"
#include "ArmorActor.h"
#include "ArmorPieceActor.h"
#include "FluorescentLampActor.h"
#include "ParticleTestActor.h"

// item actor
#include "GarbageActor.h"
#include "TrashCanActor.h"
////////////////UI/////
#include "ItemUI.h"
#include "PlayerUI.h"
#include "ArmorUI.h"
#include "WeaponUI.h"
#include "OutGameUI.h"
#include "InGameUI.h"
#include "LeverBox.h"
#include "LeverGate.h"
#include "CardKeyBox.h"
#include "CardKeyGate.h"
#include "ElevatorFloor.h"
#include "FinalGateBox.h"
#include "FinalGate.h"

// moster
#include "TestBossMonster.h"
#include "Mechsect.h"
#include "Cultist.h"
#include "Pustule.h"
#include "Deacon.h"

// user interface
#include "ItemUI.h"
#include "PlayerUI.h"
#include "ArmorUI.h"
#include "WeaponUI.h"
#include "OutGameUI.h"
#include "InGameUI.h"
using namespace std;

void CHanamuraLevel::Initialize()
{
	LoadLevelFromFile(L"Stage314");

	m_wpPlayerActor = CreateActor<CPlayerActor>(L"Player", L"Player", L"Actor");
	m_wpPlayerActor.lock()->SetActorPosition({ 10.0f, 60.0f, 10.0f });
	m_wpPlayerActor.lock()->SetActorScale({ 4.f, 12.f, 4.f });

#pragma region 무기

	m_wpElectrifryerActor = CreateActor<CElectrifryerActor>(L"Electrifryer", L"Weapon", L"Actor");	
	m_wpElectrifryerActor.lock()->SetActorScale({ 150.f, 150.f, 0.f });
	m_wpElectrifryerActor.lock()->SetActorPosition({ 50.0f, -150.0f, 5.0f });

	m_wpLoverboyActor = CreateActor<CLoverboyActor>(L"Loverboy", L"Weapon", L"Actor");
	m_wpLoverboyActor.lock()->SetActorScale({150.f, 150.f, 0.f });
	m_wpLoverboyActor.lock()->SetActorPosition({ 50.0f, -150.0f, 5.0f });
	
	m_wpDisperserActor = CreateActor<CDisperserActor>(L"Disperser", L"Weapon", L"Actor");
	m_wpDisperserActor.lock()->SetActorScale({ 150.f, 150.f, 0.f });
	m_wpDisperserActor.lock()->SetActorPosition({ 100.0f, -150.0f, 5.0f });

	m_wpPenetratorActor = CreateActor<CPenetratorActor>(L"Penetrator", L"Weapon", L"Actor");
	m_wpPenetratorActor.lock()->SetActorScale({ 150.f, 150.f, 0.f });
	m_wpPenetratorActor.lock()->SetActorPosition({ 50.0f, -150.0f, 5.0f });

	m_wpChainGunActor = CreateActor<CChainGunActor>(L"ChainGun", L"Weapon", L"Actor");
	m_wpChainGunActor.lock()->SetActorScale({ 150.f, 150.f, 0.f });
	m_wpChainGunActor.lock()->SetActorPosition({ 200.0f, -150.0f, 5.0f });

	m_wpLoverboyBulletActor = CreateActor<CLoverboyBulletActor>(L"LoverboyBullet", L"Item", L"Actor");
	m_wpLoverboyBulletActor.lock()->SetActorPosition({ 0.f, -3.0f, 40.0f });
	m_wpLoverboyBulletActor.lock()->SetCapaType(1);

#pragma endregion

#pragma region 아이템

	m_wpDisperserItemActor = CreateActor<CDisperserItemActor>(L"DisperserItem", L"Item", L"Actor");
	m_wpDisperserItemActor.lock()->SetActorPosition({ 213.f, 5.0f, -137.0f });
	m_wpDisperserItemActor.lock()->SetActorScale({ 5.f, 5.f, 5.f });

	m_wpHealthPackActor = CreateActor<CHealthPackActor>(L"HealthPack", L"Item", L"Actor");
	m_wpHealthPackActor.lock()->SetActorPosition({ 0.f, 10.0f, 0.0f });
	m_wpHealthPackActor.lock()->SetCapaType(1);

	m_wpSyringeActor = CreateActor<CSyringeActor>(L"Syringe", L"Item", L"Actor");
	m_wpSyringeActor.lock()->SetActorPosition({ 0.f, 10.0f, 10.0f });

	m_wpArmorPieceActor = CreateActor<CArmorPieceActor>(L"ArmorPiece", L"Item", L"Actor");
	m_wpArmorPieceActor.lock()->SetActorPosition({ 0.f, 10.0f, 20.0f });

	m_wpArmorActor = CreateActor<CArmorActor>(L"Armor", L"Item", L"Actor");
	m_wpArmorActor.lock()->SetActorPosition({ 0.f, 10.0f, 25.0f });
	m_wpArmorActor.lock()->SetCapaType(0);

	m_wpArmorActor = CreateActor<CArmorActor>(L"Armor1", L"Item", L"Actor");
	m_wpArmorActor.lock()->SetActorPosition({ 0.f, 10.0f, 30.0f });
	m_wpArmorActor.lock()->SetCapaType(1);

	m_wpArmorActor = CreateActor<CArmorActor>(L"Armor2", L"Item", L"Actor");
	m_wpArmorActor.lock()->SetActorPosition({ 0.f, 10.0f, 35.0f });
	m_wpArmorActor.lock()->SetCapaType(2);

#pragma endregion

#pragma region 오브젝트

	m_wpGarbage = CreateActor<CGarbageActor>(L"Garbage", L"Item", L"Actor");
	m_wpGarbage.lock()->SetActorPosition({ 213.f, 5.0f, -137.0f });
	m_wpGarbage.lock()->SetRecoveryType(ERecoveryType::HEALTHPACK);
	m_wpGarbage.lock()->SetCapaType(0);

	m_wpGarbage = CreateActor<CGarbageActor>(L"Garbage1", L"Item", L"Actor");
	m_wpGarbage.lock()->SetActorPosition({ 0.f, 0.0f, 40.0f });
	m_wpGarbage.lock()->SetRecoveryType(ERecoveryType::HEALTHPACK);
	m_wpGarbage.lock()->SetCapaType(0);

#pragma endregion 

#pragma region 몬스터
	for (int32 i = 0; i < 4; i++)
	{
		// 거미
		m_wpMechsect = CreateActor<CMechsect>(L"Mechsect" + i, L"Mechsect" + i, L"Monster");
		m_wpMechsect.lock()->SetActorPosition({ 100.0f + (5.0f * float(i)), 25.0f, -100.0f + (5.0f * float(i)) });
		m_wpMechsect.lock()->SetActorScale({ 10.0f, 10.0f, 10.0f });
	}

	 for (int32 i = 0; i < 4; i++)
	 {
	 	// 소총수
	 	m_wpCultist = CreateActor<CCultist>(L"Cultist" + i, L"Cultist" + i, L"Monster");
	 	m_wpCultist.lock()->SetActorPosition({ -160.0f - (5.0f * float(i)) , 15.0f, 175.f + (5.0f * float(i)) });
	 	m_wpCultist.lock()->SetActorScale({ 8.0f, 8.0f, 8.0f });
	 }
	 
	 for (int32 i = 0; i < 4; i++)
	 {
	 	// 좀비
	 	m_wpPustule = CreateActor<CPustule>(L"Pustule" + i, L"Pustule" + i, L"Monster");
	 	m_wpPustule.lock()->SetActorPosition({ 100.0f , 15.0f, 0.0f });
	 	m_wpPustule.lock()->SetActorScale({ 8.0f, 8.0f, 8.0f });
	 }
	 
	for (int32 i = 0; i < 4; i++)
	{
		// 디콘
		m_wpDeacon = CreateActor<CDeacon>(L"Deacon" + i, L"Deacon" + i, L"Monster");
		m_wpDeacon.lock()->SetActorPosition({ 130.0f + (5.0f * float(i)), 10.0f, -120.0f + (5.0f * float(i)) });
		m_wpDeacon.lock()->SetActorScale({ 6.0f, 6.0f, 6.0f });
	}
	
#pragma endregion

#pragma region 조명
	// 임시 태양
	m_wpSunActor = CreateActor<CSunActor>(L"Sun", L"Light", L"Actor");

#pragma endregion

#pragma region UI

	// 무기 이펙트도 UI라고 판단하여 여기 집어넣음 - 동연 -
	m_wpPlayerEffectActor = CreateActor<CPlayerEffectActor>(L"PlayerEffect", L"UI", L"Actor");
	m_wpPlayerEffectActor.lock()->SetActorPosition({ CFWINCX * 0.5f, CFWINCY * 0.5f, 0.f });
	m_wpPlayerEffectActor.lock()->SetActorScale({ CFWINCX, CFWINCY, 1.f });

	m_wpOutGameUI = CreateActor<COutGameUI>(L"OutGameUI", L"UI", L"Actor");
	m_wpOutGameUI.lock()->SetActorPosition({ 0.f,0.f,1.f }); 
	m_wpOutGameUI.lock()->SetActorScale({ 1.f, 1.f, 0.f });

	//m_wpInGameUI = CreateActor<CInGameUI>(L"InGameUI", L"UI", L"Actor");
	//m_wpInGameUI.lock()->SetActorPosition({ 0.f,0.f,0.f });
	//m_wpInGameUI.lock()->SetActorScale({ 1.f, 1.f, 0.f });

	//// 문 액터
	//m_wpLeverGate = CreateActor<CLeverGate>(L"LeverGate", L"InteractiveBox", L"Actor");
	//m_wpLeverGate.lock()->SetActorPosition({ 300.0f, 21.0f, -97.0f });
	//m_wpLeverGate.lock()->SetActorRotation({ 0.0f, 154.0f, 0.0f });
	//m_wpLeverGate.lock()->SetActorScale({ 50.f, 45.f, 10.f });
	//
	//// 손잡이 액터
	//m_wpLeverBox = CreateActor<CLeverBox>(L"LeverBox", L"InteractiveBox", L"Actor");
	//m_wpLeverBox.lock()->SetActorPosition({ 342.0f, 10.0f, -105.0f });
	//m_wpLeverBox.lock()->SetActorRotation({ 0.0f, -25.0f, 0.0f });
	//m_wpLeverBox.lock()->SetActorScale({ 5.f, 5.f, 0.f });
	//m_wpLeverBox.lock()->SetLeverGateActor(m_wpLeverGate.lock());

	// 카드 키 문 액터
	//m_wpCardKeyGate = CreateActor<CCardKeyGate>(L"CardKeyGate", L"InteractiveBox", L"Actor");
	//m_wpCardKeyGate.lock()->SetActorPosition({ 300.f, 21.0f, -97.0f });
	//m_wpCardKeyGate.lock()->SetActorRotation({ 0.0f, 154.f, 0.0f });
	//m_wpCardKeyGate.lock()->SetActorScale({ 50.f, 45.f, 10.f });
	//
	//// 카드 키 인식 액터
	//m_wpCardKeyBox = CreateActor<CCardKeyBox>(L"CardKeyBox", L"InteractiveBox", L"Actor");
	//m_wpCardKeyBox.lock()->SetActorPosition({ 342, 30.0f, -104.0f });
	//m_wpCardKeyBox.lock()->SetActorRotation({ 0.0f, 154.0f, 0.0f });
	//m_wpCardKeyBox.lock()->SetActorScale({ 5.f, 5.f, 0.f });
	//m_wpCardKeyBox.lock()->SetCardKeyGateActor(m_wpCardKeyGate.lock());

	// 엘레베이터 오른쪽 문 액터
	//m_wpElevatorRightGate = CreateActor<CElevatorRightGate>(L"ElevatorRightGate", L"InteractiveBox", L"Actor");
	//m_wpElevatorRightGate.lock()->SetActorPosition({ 252.f, 22.f, 3.0f });
	//m_wpElevatorRightGate.lock()->SetActorRotation({ 0.0f, 62.0f, 0.0f });
	//m_wpElevatorRightGate.lock()->SetActorScale({ 20.f, 50.f, 1.f });
	//
	//// 엘레베이터 버튼 액터
	//m_wpElevatorBox = CreateActor<CElevatorBox>(L"ElevatorBox", L"InteractiveBox", L"Actor");
	//m_wpElevatorBox.lock()->SetActorPosition({ 255.0f, 7.0f, -4.0f });
	//m_wpElevatorBox.lock()->SetActorRotation({ 0.0f, 62.0f, 0.0f });
	//m_wpElevatorBox.lock()->SetActorScale({ 3.f, 5.f, 1.f });
	//m_wpElevatorBox.lock()->SetElevatorRightGateActor(m_wpElevatorRightGate.lock());

	//////////////////////////////////////////////
#pragma endregion

	CLevel::Initialize();  
}

void CHanamuraLevel::BeginPlay()
{
	// 무기
	m_wpPlayerActor.lock()->AddWeapon(m_wpElectrifryerActor);
	m_wpPlayerActor.lock()->AddWeapon(m_wpLoverboyActor);
	m_wpPlayerActor.lock()->AddWeapon(m_wpDisperserActor);
	m_wpPlayerActor.lock()->AddWeapon(m_wpPenetratorActor);
	m_wpPlayerActor.lock()->AddWeapon(m_wpChainGunActor);

	// 이펙트
	m_wpPlayerActor.lock()->AddEffect(m_wpPlayerEffectActor);

	CLevel::BeginPlay();
}

int32 CHanamuraLevel::Update(const float& _fDeltaSeconds)
{
	return CLevel::Update(_fDeltaSeconds);
}

int32 CHanamuraLevel::LateUpdate(const float& _fDeltaSeconds)
{
	return CLevel::LateUpdate(_fDeltaSeconds);
}

void CHanamuraLevel::Render()
{
	CLevel::Render();
}

void CHanamuraLevel::EndPlay()
{
	CLevel::EndPlay();
}

void CHanamuraLevel::Release()
{
	CLevel::Release();
}