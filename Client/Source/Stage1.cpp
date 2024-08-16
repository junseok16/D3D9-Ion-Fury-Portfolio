// default
#include "pch.h"
#include "Stage1.h"
#include "Stage3.h"

// framework
#include "World.h"

// manager
#include "DeviceManager.h"
#include "RenderManager.h"
#include "SoundManager.h"
#include "InputManager.h"
#include "GameManager.h"

// actor
#include "SunActor.h"
#include "PlayerEffectActor.h"
#include "SceneChangerActor.h"
#include "SkyBox.h"

// weapon
#include "PlayerActor.h"
#include "ElectrifryerActor.h"
#include "LoverboyActor.h"
#include "LoverboyLHActor.h"
#include "DisperserActor.h"
#include "PenetratorActor.h"
#include "ChainGunActor.h"

#include "DisperserItemActor.h"
#include "PenetratorItemActor.h"
#include "ChainGunItemActor.h"

#include "LoverboyBulletActor.h"
#include "HealthPackActor.h"
#include "SyringeActor.h"
#include "ArmorActor.h"
#include "ArmorPieceActor.h"
#include "FluorescentLampActor.h"

// item actor
#include "GarbageActor.h"
#include "TrashCanActor.h"
#include "CardKeyActor.h"

// interactive actor
#include "LeverBox.h"
#include "LeverGate.h"
#include "CardKeyBox.h"
#include "CardKeyGate.h"
#include "ElevatorFloor.h"
#include "FinalGateBox.h"
#include "FinalGate.h"
#include "PowerMonitor.h"
#include "PowerMonitor1.h"
#include "ElevatorKeyBox.h"
#include "ElevatorKeyBox1.h"

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

void CStage1::Initialize()
{
	LoadLevelFromFile(L"Stage314");

#pragma region 플레이어

	//m_wpPlayerActor = CreateActor<CPlayerActor>(L"Player", L"Player", L"Actor");
	//m_wpPlayerActor.lock()->SetActorPosition({ 300.0f, 80.0f, -600.0f });
	//m_wpPlayerActor.lock()->SetActorScale({ 10.f, 24.f, 10.f });

	// 보관(v)
	m_wpPlayerActor = CreateActor<CPlayerActor>(L"Player", L"Player", L"Actor");
	m_wpPlayerActor.lock()->SetActorPosition({ 232.0f, 2.0f, -440.0f });
	m_wpPlayerActor.lock()->SetActorScale({ 10.f, 24.f, 10.f });

	// 보관(v)
	m_wpPlayerEffectActor = CreateActor<CPlayerEffectActor>(L"PlayerEffect", L"UI", L"Actor");
	m_wpPlayerEffectActor.lock()->SetActorPosition({ CFWINCX * 0.5f, CFWINCY * 0.5f, 0.f });
	m_wpPlayerEffectActor.lock()->SetActorScale({ CFWINCX, CFWINCY, 1.f });

	// 스카이박스
	m_wpSkyBox = CreateActor<CSkyBox>(L"SkyBox", L"Actor", L"Actor");
	m_wpSkyBox.lock()->SetSkybox(L"SkyBox0_0");
	m_wpSkyBox.lock()->SetActorPosition({ 300.0f, 120.0f, -600.0f });
	m_wpSkyBox.lock()->SetActorScale({ 1000.f, 1000.f, 1000.f });

#pragma endregion

	// 보관(v)
#pragma region 무기

	m_wpElectrifryerActor = CreateActor<CElectrifryerActor>(L"Electrifryer", L"Weapon", L"Actor");
	m_wpElectrifryerActor.lock()->SetActorScale({ 150.f, 150.f, 0.f });
	m_wpElectrifryerActor.lock()->SetActorPosition({ 50.0f, -150.0f, 5.0f });

	m_wpLoverboyActor = CreateActor<CLoverboyActor>(L"Loverboy", L"Weapon", L"Actor");
	m_wpLoverboyActor.lock()->SetActorScale({ 150.f, 150.f, 0.f });
	m_wpLoverboyActor.lock()->SetActorPosition({ 50.0f, -150.0f, 5.0f });

	m_wpDisperserActor = CreateActor<CDisperserActor>(L"Disperser", L"Weapon", L"Actor");
	m_wpDisperserActor.lock()->SetActorScale({ 150.f, 150.f, 0.f });
	m_wpDisperserActor.lock()->SetActorPosition({ 100.f, -150.f, 5.0f });

	m_wpPenetratorActor = CreateActor<CPenetratorActor>(L"Penetrator", L"Weapon", L"Actor");
	m_wpPenetratorActor.lock()->SetActorScale({ 150.f, 150.f, 0.f });
	m_wpPenetratorActor.lock()->SetActorPosition({ 50.0f, -150.f, 5.0f });

	m_wpChainGunActor = CreateActor<CChainGunActor>(L"ChainGun", L"Weapon", L"Actor");
	m_wpChainGunActor.lock()->SetActorScale({ 150.f, 150.f, 0.f });
	m_wpChainGunActor.lock()->SetActorPosition({ 200.0f, -150.0f, 5.0f });

#pragma endregion

#pragma region 아이템

	m_wpLoverboyBulletActor = CreateActor<CLoverboyBulletActor>(L"LoverboyBullet", L"Item", L"Actor");
	m_wpLoverboyBulletActor.lock()->SetActorPosition({ 0.f, -3.0f, 40.0f });
	m_wpLoverboyBulletActor.lock()->SetCapaType(1);

	m_wpHealthPackActor = CreateActor<CHealthPackActor>(L"HealthPack", L"Item", L"Actor");
	m_wpHealthPackActor.lock()->SetActorPosition({ 61.1f, 65.6f, 361.0f });
	m_wpHealthPackActor.lock()->SetCapaType(1);

	m_wpSyringeActor = CreateActor<CSyringeActor>(L"Syringe", L"Item", L"Actor");
	m_wpSyringeActor.lock()->SetActorPosition({ 252.8f, 35.27f, -294.3f });

	m_wpArmorPieceActor = CreateActor<CArmorPieceActor>(L"ArmorPiece", L"Item", L"Actor");
	m_wpArmorPieceActor.lock()->SetActorPosition({ 260.6f, 5.3f, 301.1f });

	// 기본으로 착용할지 아니면 먹을지 결정한 후 배치하기
	m_wpArmorActor = CreateActor<CArmorActor>(L"Armor", L"Item", L"Actor");
	m_wpArmorActor.lock()->SetActorPosition({ 210.f, 2.0f, -440.0f });
	m_wpArmorActor.lock()->SetCapaType(0);

	m_wpArmorActor = CreateActor<CArmorActor>(L"Armor1", L"Item", L"Actor");
	m_wpArmorActor.lock()->SetActorPosition({ 209.7f, 9.4f, -75.8f });
	m_wpArmorActor.lock()->SetCapaType(1);
	
	m_wpArmorActor = CreateActor<CArmorActor>(L"Armor2", L"Item", L"Actor");
	m_wpArmorActor.lock()->SetActorPosition({ -515.f, 10.3f, 471.0f });
	m_wpArmorActor.lock()->SetCapaType(2);

	m_wpCardKeyActor = CreateActor<CCardKeyActor>(L"CardKey", L"Item", L"Actor");
	m_wpCardKeyActor.lock()->SetActorPosition({ 762.f, 13.0f, -59.0f });
	m_wpCardKeyActor.lock()->SetCapaType(0);
	
	m_wpCardKeyActor = CreateActor<CCardKeyActor>(L"CardKey1", L"Item", L"Actor");
	m_wpCardKeyActor.lock()->SetActorPosition({ 302.f, 106.0f, -249.0f });
	m_wpCardKeyActor.lock()->SetCapaType(1);

#pragma endregion

#pragma region 오브젝트

	for (int32 i = 0; i < 2; i++)
	{
		m_wpGarbage = CreateActor<CGarbageActor>(L"Garbage" + i, L"Item" + i, L"Actor");
		m_wpGarbage.lock()->SetActorPosition({ 200.f, 1.5f, -100.f + (5.0f * float(i)) });
		m_wpGarbage.lock()->SetRecoveryType(ERecoveryType::HEALTHPACK);
		m_wpGarbage.lock()->SetCapaType(0);
	}

	for (int32 i = 2; i < 4; i++)
	{
		m_wpGarbage = CreateActor<CGarbageActor>(L"Garbage" + i, L"Item" + i, L"Actor");
		m_wpGarbage.lock()->SetActorPosition({ -500.0f, 1.5f, 520.f });
		m_wpGarbage.lock()->SetRecoveryType(ERecoveryType::HEALTHPACK);
		m_wpGarbage.lock()->SetCapaType(0);
	}

	for (int32 i = 4; i < 6; i++)
	{
		m_wpGarbage = CreateActor<CGarbageActor>(L"Garbage" + i, L"Item" + i, L"Actor");
		m_wpGarbage.lock()->SetActorPosition({ -42.8f, 10.6f, 390.6f + (5.0f * float(i)) });
		m_wpGarbage.lock()->SetRecoveryType(ERecoveryType::HEALTHPACK);
		m_wpGarbage.lock()->SetCapaType(0);
	}
	
	for (int32 i = 6; i < 8; i++)
	{
		m_wpGarbage = CreateActor<CGarbageActor>(L"Garbage" + i, L"Item" + i, L"Actor");
		m_wpGarbage.lock()->SetActorPosition({ -108.9f, 9.56f, 154.48f });
		m_wpGarbage.lock()->SetRecoveryType(ERecoveryType::HEALTHPACK);
		m_wpGarbage.lock()->SetCapaType(0);
	}

	m_wpDisperserItemActor = CreateActor<CDisperserItemActor>(L"DisperserItem", L"Item", L"Actor");
	m_wpDisperserItemActor.lock()->SetActorPosition({ 578.4f, 50.f, -392.3f });
	m_wpDisperserItemActor.lock()->SetActorScale({ 5.0f, 5.0f, 1.0f });

	m_wpPenetratorItemActor = CreateActor<CPenetratorItemActor>(L"PenetratorItem", L"Item", L"Actor");
	m_wpPenetratorItemActor.lock()->SetActorPosition({ -280.2f, 20.54f, 312.0f });
	m_wpPenetratorItemActor.lock()->SetActorScale({ 8.0f, 5.0f, 1.0f });

#pragma endregion 

#pragma region 몬스터

	////////////////////
	// == 1번 스팟 == //
	////////////////////
	for (int32 i = 0; i < 2; i++)
	{
		// 거미
		m_wpMechsect = CreateActor<CMechsect>(L"Mechsect" + (i), L"Mechsect", L"Monster");
		m_wpMechsect.lock()->SetActorPosition({ 130.f + 5.0f * float(i), 35.0f, -300.0f + (5.0f * float(i))});
		m_wpMechsect.lock()->SetActorScale({ 16.0f, 16.0f, 16.0f });
	
		m_wpMechsect = CreateActor<CMechsect>(L"Mechsect" + (i + 2), L"Mechsect", L"Monster");
		m_wpMechsect.lock()->SetActorPosition({ 130.f - 5.0f * float(i), 40.0f, -300.0f - (5.0f * float(i)) });
		m_wpMechsect.lock()->SetActorScale({ 16.0f, 16.0f, 16.0f });
	}
	
	////////////////////
	// == 2번 스팟 == //
	////////////////////
	for (int32 i = 4; i < 6; i++)
	{
		// 거미
		m_wpMechsect = CreateActor<CMechsect>(L"Mechsect" + (i), L"Mechsect", L"Monster");
		m_wpMechsect.lock()->SetActorPosition({ 430.f + 5.0f * float(i), 80.0f, -300.0f + (5.0f * float(i)) });
		m_wpMechsect.lock()->SetActorScale({ 16.0f, 16.0f, 16.0f });
	
		m_wpMechsect = CreateActor<CMechsect>(L"Mechsect" + (i + 2), L"Mechsect", L"Monster");
		m_wpMechsect.lock()->SetActorPosition({ 430.f - 5.0f * float(i), 80.0f, -300.0f - (5.0f * float(i)) });
		m_wpMechsect.lock()->SetActorScale({ 16.0f, 16.0f, 16.0f });
	}
	
	////////////////////
	// == 3번 스팟 == //
	////////////////////
	for (int32 i = 0; i < 2; i++)
	{
		// 좀비
		m_wpPustule = CreateActor<CPustule>(L"Pustule" + i, L"Pustule", L"Monster");
		m_wpPustule.lock()->SetActorPosition({ 235.0f + 5.0f * float(i), 30.0f, -230.0f + (5.0f * float(i)) });
		m_wpPustule.lock()->SetActorScale({ 24.0f, 24.0f, 24.0f });
	
		m_wpPustule = CreateActor<CPustule>(L"Pustule" + (i + 2), L"Pustule", L"Monster");
		m_wpPustule.lock()->SetActorPosition({ 235.0f - 5.0f * float(i), 30.0f, -230.0f - (5.0f * float(i)) });
		m_wpPustule.lock()->SetActorScale({ 24.0f, 24.0f, 24.0f });
	}
	
	////////////////////
	// == 4번 스팟 == //
	////////////////////	- 소총수 1마리 -
	//m_wpCultist = CreateActor<CCultist>(L"Cultist312321", L"Cultist", L"Monster");
	//m_wpCultist.lock()->SetActorPosition({ 362.0f , 80.0f, -274.0f });
	//m_wpCultist.lock()->SetActorScale({ 24.0f, 24.0f, 24.0f });
	
	////////////////////
	// == 5번 스팟 == //
	////////////////////
	// for (int32 i = 4; i < 6; i++)
	// {
	// 	// 좀비
	// 	m_wpPustule = CreateActor<CPustule>(L"Pustule" + i, L"Pustule", L"Monster");
	// 	m_wpPustule.lock()->SetActorPosition({ 530.0f + 5.0f * float(i), 20.0f, -450.0f + (5.0f * float(i)) });
	// 	m_wpPustule.lock()->SetActorScale({ 24.0f, 24.0f, 24.0f });
	// 
	// 	m_wpPustule = CreateActor<CPustule>(L"Pustule" + (i + 2), L"Pustule", L"Monster");
	// 	m_wpPustule.lock()->SetActorPosition({ 530.0f - 5.0f * float(i), 20.0f, -450.0f - (5.0f * float(i)) });
	// 	m_wpPustule.lock()->SetActorScale({ 24.0f, 24.0f, 24.0f });
	// }
	
	////////////////////
	// == 6번 스팟 == //
	////////////////////
	for (int32 i = 0; i < 2; i++)
	{
		// 소총수
		m_wpCultist = CreateActor<CCultist>(L"Cultist" + i, L"Cultist", L"Monster");
		m_wpCultist.lock()->SetActorPosition({ 470.0f + 10.0f * float(i), 70.0f, -225.0f + (10.0f * float(i)) });
		m_wpCultist.lock()->SetActorScale({ 24.0f, 24.0f, 24.0f });
	
		m_wpCultist = CreateActor<CCultist>(L"Cultist" + (i + 2), L"Cultist", L"Monster");
		m_wpCultist.lock()->SetActorPosition({ 470.0f - 10.0f * float(i), 70.0f, -225.0f - (10.0f * float(i)) });
		m_wpCultist.lock()->SetActorScale({ 24.0f, 24.0f, 24.0f });
	}
	
	////////////////////
	// == 7번 스팟 == //
	////////////////////
	// 좀비
	//m_wpPustule = CreateActor<CPustule>(L"좀비8", L"Pustule", L"Monster");
	//m_wpPustule.lock()->SetActorPosition({ 615.0f + 6.0f, 40.0f, -30.0f + 6.0f });
	//m_wpPustule.lock()->SetActorScale({ 24.0f, 24.0f, 24.0f });
	//
	//m_wpPustule = CreateActor<CPustule>(L"좀비9", L"Pustule", L"Monster");
	//m_wpPustule.lock()->SetActorPosition({ 615.0f - 6.0f, 40.0f, -30.0f - 6.0f });
	//m_wpPustule.lock()->SetActorScale({ 24.0f, 24.0f, 24.0f });
	//
	//m_wpPustule = CreateActor<CPustule>(L"좀비10", L"Pustule", L"Monster");
	//m_wpPustule.lock()->SetActorPosition({ 615.0f + 11.0f, 40.0f, -30.0f + 11.0f });
	//m_wpPustule.lock()->SetActorScale({ 24.0f, 24.0f, 24.0f });
	//
	//m_wpPustule = CreateActor<CPustule>(L"좀비11", L"Pustule", L"Monster");
	//m_wpPustule.lock()->SetActorPosition({ 615.0f - 11.0f, 40.0f, -30.0f - 11.0f });
	//m_wpPustule.lock()->SetActorScale({ 24.0f, 24.0f, 24.0f });
	
	////////////////////
	// == 8번 스팟 == //
	////////////////////
	// 거미
	m_wpMechsect = CreateActor<CMechsect>(L"거미1", L"Mechsect", L"Monster");
	m_wpMechsect.lock()->SetActorPosition({ 301.f + 5.0f, 80.0f, -160.0f + 5.0f });
	m_wpMechsect.lock()->SetActorScale({ 16.0f, 16.0f, 16.0f });
	
	m_wpMechsect = CreateActor<CMechsect>(L"거미2", L"Mechsect", L"Monster");
	m_wpMechsect.lock()->SetActorPosition({ 301.f - 5.0f, 80.0f, -160.0f - 5.0f });
	m_wpMechsect.lock()->SetActorScale({ 16.0f, 16.0f, 16.0f });
	
	m_wpMechsect = CreateActor<CMechsect>(L"거미3", L"Mechsect", L"Monster");
	m_wpMechsect.lock()->SetActorPosition({ 301.f + 10.0f, 80.0f, -160.0f + 10.0f });
	m_wpMechsect.lock()->SetActorScale({ 16.0f, 16.0f, 16.0f });
	
	m_wpMechsect = CreateActor<CMechsect>(L"거미4", L"Mechsect", L"Monster");
	m_wpMechsect.lock()->SetActorPosition({ 301.f - 5.0f, 80.0f, -160.0f - 10.0f });
	m_wpMechsect.lock()->SetActorScale({ 16.0f, 16.0f, 16.0f });
	
	////////////////////
	// == 9번 스팟 == //
	////////////////////		- 디콘 4마리 -
	for (int32 i = 0; i < 2; i++)
	{
		// 디콘
		m_wpDeacon = CreateActor<CDeacon>(L"Deacon" + (i), L"Deacon", L"Monster");
		m_wpDeacon.lock()->SetActorPosition({ 310.0f + (5.0f * float(i)), 50.0f, 30.0f + (5.0f * float(i)) });
		m_wpDeacon.lock()->SetActorScale({ 24.0f, 24.0f, 24.0f });
	
		m_wpDeacon = CreateActor<CDeacon>(L"Deacon" + (i + 2), L"Deacon", L"Monster");
		m_wpDeacon.lock()->SetActorPosition({ 310.0f - (5.0f * float(i)), 50.0f, 30.0f - (5.0f * float(i)) });
		m_wpDeacon.lock()->SetActorScale({ 24.0f, 24.0f, 24.0f });
	}
	
	////////////////////
	// == 10번 스팟 == //
	////////////////////
	for (int32 i = 0; i < 2; i++)
	{
		// 소총수
		m_wpCultist = CreateActor<CCultist>(L"sochong" + i, L"sochong", L"Monster");
		m_wpCultist.lock()->SetActorPosition({ 260.0f + (5.0f * float(i)) , 60.0f, 270.0f + (5.0f * float(i)) });
		m_wpCultist.lock()->SetActorScale({ 24.0f, 24.0f, 24.0f });
	
		m_wpCultist = CreateActor<CCultist>(L"sochong" + (i + 2), L"sochong", L"Monster");
		m_wpCultist.lock()->SetActorPosition({ 260.0f - (5.0f * float(i)) , 60.0f, 270.0f - (5.0f * float(i)) });
		m_wpCultist.lock()->SetActorScale({ 24.0f, 24.0f, 24.0f });
	}
	
	////////////////////
	// == 11번 스팟 == //
	////////////////////
	for (int32 i = 0; i < 2; i++)
	{
		// 소총수
		m_wpCultist = CreateActor<CCultist>(L"sochongsu" + i, L"sochong", L"Monster");
		m_wpCultist.lock()->SetActorPosition({ 110.0f + (5.0f * float(i)) , 60.0f, 120.0f + (5.0f * float(i)) });
		m_wpCultist.lock()->SetActorScale({ 24.0f, 24.0f, 24.0f });
	
		m_wpCultist = CreateActor<CCultist>(L"sochongsu" + (i + 2), L"sochong", L"Monster");
		m_wpCultist.lock()->SetActorPosition({ 110.0f - (5.0f * float(i)) , 60.0f, 120.0f - (5.0f * float(i)) });
		m_wpCultist.lock()->SetActorScale({ 24.0f, 24.0f, 24.0f });
	}
	
	////////////////////
	// == 12번 스팟 == //
	////////////////////
	for (int32 i = 0; i < 2; i++)
	{
		// 거미
		m_wpMechsect = CreateActor<CMechsect>(L"spider" + (i), L"Mechsect", L"Monster");
		m_wpMechsect.lock()->SetActorPosition({ 220.0f + 5.0f * float(i), 70.0f, 350.0f + (5.0f * float(i)) });
		m_wpMechsect.lock()->SetActorScale({ 16.0f, 16.0f, 16.0f });
	
		m_wpMechsect = CreateActor<CMechsect>(L"spider" + (i + 2), L"Mechsect", L"Monster");
		m_wpMechsect.lock()->SetActorPosition({ 220.0f - 5.0f * float(i), 70.0f, 350.0f - (5.0f * float(i)) });
		m_wpMechsect.lock()->SetActorScale({ 16.0f, 16.0f, 16.0f });
	}
	
	////////////////////
	// == 13번 스팟 == //
	////////////////////
	for (int32 i = 0; i < 2; i++)
	{
		// 거미
		m_wpMechsect = CreateActor<CMechsect>(L"spiderkun" + (i), L"Mechsect", L"Monster");
		m_wpMechsect.lock()->SetActorPosition({ 185.0f + 5.0f * float(i), 60.0f, -60.0f + (5.0f * float(i)) });
		m_wpMechsect.lock()->SetActorScale({ 16.0f, 16.0f, 16.0f });
	
		m_wpMechsect = CreateActor<CMechsect>(L"spiderkun" + (i + 2), L"Mechsect", L"Monster");
		m_wpMechsect.lock()->SetActorPosition({ 185.0f - 5.0f * float(i), 60.0f, 60.0f - (5.0f * float(i)) });
		m_wpMechsect.lock()->SetActorScale({ 16.0f, 16.0f, 16.0f });
	}
	
	////////////////////
	// == 14번 스팟 == //
	////////////////////
	for (int32 i = 0; i < 2; i++)
	{
		// 디콘
		m_wpDeacon = CreateActor<CDeacon>(L"Deaconkun" + (i), L"Deacon", L"Monster");
		m_wpDeacon.lock()->SetActorPosition({ -75.0f + (5.0f * float(i)), 50.0f, 360.0f + (5.0f * float(i)) });
		m_wpDeacon.lock()->SetActorScale({ 24.0f, 24.0f, 24.0f });
	
		m_wpDeacon = CreateActor<CDeacon>(L"Deaconkun" + (i + 2), L"Deacon", L"Monster");
		m_wpDeacon.lock()->SetActorPosition({ -75.0f - (5.0f * float(i)), 50.0f, 360.0f - (5.0f * float(i)) });
		m_wpDeacon.lock()->SetActorScale({ 24.0f, 24.0f, 24.0f });
	}
	
	////////////////////
	// == 15번 스팟 == //
	///////////////////


	// 랜덤 숫자 생성기 생성
	std::random_device rd;
	std::mt19937 mtRng(rd());


	for (int32 i = 0; i < 10; i++)
	{
	
		std::uniform_real_distribution<float> uPosXDist(470.0f, 735.0f); // x 위치의 랜덤 범위
		std::uniform_real_distribution<float> uPosZDist(-150.0f, 80.0f); // z 위치의 랜덤 범위
	
		// 좀비
		m_wpPustule = CreateActor<CPustule>(L"koreanzombie" + std::to_wstring(i), L"Pustule", L"Monster");
		m_wpPustule.lock()->SetActorPosition({ (float)(uPosXDist(mtRng)), 50.1f, (float)(uPosZDist(mtRng)) });
		m_wpPustule.lock()->SetActorScale({ 24.0f, 24.0f, 24.0f });
	}

	for (int32 i = 0; i < 10; i++)
	{

		std::uniform_real_distribution<float> uPosXDist(470.0f, 735.0f); // x 위치의 랜덤 범위
		std::uniform_real_distribution<float> uPosZDist(-150.0f, 80.0f); // z 위치의 랜덤 범위

		// 좀비
		m_wpPustule = CreateActor<CPustule>(L"koreanzomam" + std::to_wstring(i), L"Pustule", L"Monster");
		m_wpPustule.lock()->SetActorPosition({ (float)(uPosXDist(mtRng)), 200.1f, (float)(uPosZDist(mtRng)) });
		m_wpPustule.lock()->SetActorScale({ 24.0f, 24.0f, 24.0f });
	}

	
#pragma endregion

#pragma region 조명

	m_wpSunActor = CreateActor<CSunActor>(L"Sun", L"Light", L"Actor");

#pragma endregion

#pragma region UI

	m_wpOutGameUI = CreateActor<COutGameUI>(L"OutGameUI", L"UI", L"Actor");
	m_wpOutGameUI.lock()->SetActorPosition({ 0.f,0.f,1.f });
	m_wpOutGameUI.lock()->SetActorScale({ 1.f, 1.f, 0.f });

	//m_wpInGameUI = CreateActor<CInGameUI>(L"InGameUI", L"UI", L"Actor");
	//m_wpInGameUI.lock()->SetActorPosition({ 0.f,0.f,0.f });
	//m_wpInGameUI.lock()->SetActorScale({ 1.f, 1.f, 0.f });


	// 첫번쨰 육교
	//// 문 액터
	m_wpLeverGate = CreateActor<CLeverGate>(L"LeverGate", L"InteractiveBox", L"Actor");
	m_wpLeverGate.lock()->SetActorPosition({ 300.0f, 18.0f, -97.0f });
	m_wpLeverGate.lock()->SetActorRotation({ 0.0f, 154.0f, 0.0f });
	m_wpLeverGate.lock()->SetActorScale({ 50.f, 45.f, 10.f });

	// 카드 키 인식 액터
	m_wpCardKeyBox = CreateActor<CCardKeyBox>(L"CardKeyBox", L"InteractiveBox", L"Actor");
	m_wpCardKeyBox.lock()->SetActorPosition({ 335.f, 16.0f, -107.0f });
	m_wpCardKeyBox.lock()->SetActorRotation({ 0.0f, -25.f, 0.0f });
	m_wpCardKeyBox.lock()->SetActorScale({ 10.f, 5.f, 0.f });
	m_wpCardKeyBox.lock()->SetCardKeyGateActor(m_wpLeverGate.lock());



	//2번쨰 육교
	//// 카드 키 문 액터
	m_wpCardKeyGate = CreateActor<CCardKeyGate>(L"CardKeyGate", L"InteractiveBox", L"Actor");
	m_wpCardKeyGate.lock()->SetActorPosition({ 50.0f, 34.5f, 125.0f });
	m_wpCardKeyGate.lock()->SetActorRotation({ 0.0f, 65.0f, 0.0f });
	m_wpCardKeyGate.lock()->SetActorScale({ 60.f, 75.f, 10.f });
	
	// 손잡이 액터
	m_wpLeverBox = CreateActor<CLeverBox>(L"LeverBox", L"InteractiveBox", L"Actor");
	m_wpLeverBox.lock()->SetActorPosition({ 42.0f, 13.0f, 92.0f });
	m_wpLeverBox.lock()->SetActorRotation({ 0.0f, 70.0f, 0.0f });
	m_wpLeverBox.lock()->SetActorScale({ 5.f, 5.f, 0.f });
	m_wpLeverBox.lock()->SetLeverGateActor(m_wpCardKeyGate.lock());
	
	// 엘레베이터 바닥 문 액터
	m_wpElevatorFloor = CreateActor<CElevatorFloor> (L"ElevatorFloor", L"InteractiveBox", L"Actor");
	m_wpElevatorFloor.lock()->SetActorPosition({ 459.f, 0.f, -122.0f });
	m_wpElevatorFloor.lock()->SetActorRotation({ 0.0f, 152.0f, 0.0f });
	m_wpElevatorFloor.lock()->SetActorScale({ 45.f, 1.5f, 40.f });
	
	// 카드 키 인식 액터
	m_wpElevatorKeyBox = CreateActor<CElevatorKeyBox>(L"ElevatorKeyBox", L"InteractiveBox", L"Actor");
	m_wpElevatorKeyBox.lock()->SetActorPosition({ 489.f, 16.0f, -134.f });
	m_wpElevatorKeyBox.lock()->SetActorRotation({ 0.0f, 65.5f, 0.0f });
	m_wpElevatorKeyBox.lock()->SetActorScale({ 10.f, 5.f, 0.f });
	m_wpElevatorKeyBox.lock()->SetElevatorFloorActor(m_wpElevatorFloor.lock());

	m_wpElevatorKeyBox1 = CreateActor<CElevatorKeyBox1>(L"ElevatorKeyBox1", L"InteractiveBox", L"Actor");
	m_wpElevatorKeyBox1.lock()->SetActorPosition({ 489.f, 175.0f, -134.0f });
	m_wpElevatorKeyBox1.lock()->SetActorRotation({ 0.0f, 65.5f, 0.0f });
	m_wpElevatorKeyBox1.lock()->SetActorScale({ 10.f, 5.f, 0.f });
	m_wpElevatorKeyBox1.lock()->SetElevatorFloorActor(m_wpElevatorFloor.lock());

	// 버튼 액터
	//m_wpFinalGateBox = CreateActor<CFinalGateBox>(L"FinalGateBox", L"InteractiveBox", L"Actor");
	//m_wpFinalGateBox.lock()->SetActorPosition({ 455.5f, 16.0f, -105.0f });
	//m_wpFinalGateBox.lock()->SetActorRotation({ 0.0f, 62.0f, 0.0f });
	//m_wpFinalGateBox.lock()->SetActorScale({ 0.f, 5.f, 5.f });
	//m_wpFinalGateBox.lock()->SetElevatorFloorActor(m_wpElevatorFloor.lock());

	// 엘레베이터 버튼 액터
	//m_wpFinalBox = CreateActor<CFinalGate>(L"FinalGate", L"InteractiveBox", L"Actor");
	//m_wpElevatorBox.lock()->SetActorPosition({ 455.5f, 16.0f, -105.0f });
	//m_wpElevatorBox.lock()->SetActorRotation({ 0.0f, 62.0f, 0.0f });
	//m_wpElevatorBox.lock()->SetActorScale({ 0.f, 5.f, 5.f });
	//m_wpElevatorBox.lock()->SetElevatorFloorActor(m_wpElevatorFloor.lock());

	// 변압기
	m_wpPowerMonitor = CreateActor<CPowerMonitor>(L"PowerMonitor", L"InteractiveBox", L"Actor");
	m_wpPowerMonitor.lock()->SetActorPosition({ 466, 177.5f, -16.5f });
	m_wpPowerMonitor.lock()->SetActorRotation({ 0.0f, 240.0f, 0.0f });
	m_wpPowerMonitor.lock()->SetActorScale({ 15.f, 10.f, 1.f });

	// 변압기 1
	m_wpPowerMonitor1 = CreateActor<CPowerMonitor1>(L"PowerMonitor1", L"InteractiveBox", L"Actor");
	m_wpPowerMonitor1.lock()->SetActorPosition({ 51.f, 17.f, -25.0f });
	m_wpPowerMonitor1.lock()->SetActorRotation({ 0.0f, -203.0f, 0.0f });
	m_wpPowerMonitor1.lock()->SetActorScale({ 15.f, 10.f, 1.f });

#pragma endregion

#pragma region 신 전환 트리거

	 m_wpSceneChanger = CreateActor<CSceneChangerActor>(L"SceneChangerToStage2", L"Trigger", L"Actor");
	 m_wpSceneChanger.lock()->SetActorPosition({ -494.0f, -97.0f, 518.0f });
	 m_wpSceneChanger.lock()->SetActorRotation({ 0.0f, 0.0f, 0.0f });
	 m_wpSceneChanger.lock()->SetActorScale({ 25.f, 25.f, 25.f });

#pragma endregion

	CLevel::Initialize();
}

void CStage1::BeginPlay()
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

int32 CStage1::Update(const float& _fDeltaSeconds)
{
	if (CInputManager::GetInstance()->IsKeyDown(DIK_9))
	{
		GetWorld().lock()->CreateLevel<CStage3>(L"Stage3");
		GetWorld().lock()->ChangeLevelTo(L"Stage3");
		GetWorld().lock()->RemoveLevel(L"Stage1");
		return -2;
	}

	return CLevel::Update(_fDeltaSeconds);
}

int32 CStage1::LateUpdate(const float& _fDeltaSeconds)
{
	return CLevel::LateUpdate(_fDeltaSeconds);
}

void CStage1::Render()
{
	CLevel::Render();
}

void CStage1::EndPlay()
{
	CLevel::EndPlay();
}

void CStage1::Release()
{
	CLevel::Release();
}