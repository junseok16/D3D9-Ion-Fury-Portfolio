// default
#include "pch.h"
#include "Stage2.h"

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
#include "PowerMonitor.h"
#include "PlayerEffectActor.h"
#include "PlayerParticleActor.h"
#include "SceneChangerActor.h"

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
//#include "ElevatorLeftGate.h"

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

#include "Stage3.h"
#include "BossTrigger.h"

#include "SoundComponent.h"

using namespace std;

void CStage2::Initialize()
{
	LoadLevelFromFile(L"Metro02");

	m_wpSoundComponent.lock()->PlayBGMByDistance("Stage2", 100.f);

	m_wpPlayerActor = CreateActor<CPlayerActor>(L"Player", L"Player", L"Actor");
	m_wpPlayerActor.lock()->SetActorPosition({ 16.f, 60.0f, 3000.0f });
	m_wpPlayerActor.lock()->SetActorScale({ 10.f, 24.f, 10.f });

	m_wpPlayerEffectActor = CreateActor<CPlayerEffectActor>(L"PlayerEffect", L"UI", L"Actor");
	m_wpPlayerEffectActor.lock()->SetActorPosition({ CFWINCX * 0.5f, CFWINCY * 0.5f, 0.f });
	m_wpPlayerEffectActor.lock()->SetActorScale({ CFWINCX, CFWINCY, 1.f });

#pragma region 무기

	m_wpElectrifryerActor = CreateActor<CElectrifryerActor>(L"Electrifryer", L"Weapon", L"Actor");
	m_wpElectrifryerActor.lock()->SetActorScale({ 150.f, 150.f, 0.f });
	m_wpElectrifryerActor.lock()->SetActorPosition({ 50.0f, -150.0f, 5.0f });

	m_wpLoverboyActor = CreateActor<CLoverboyActor>(L"Loverboy", L"Weapon", L"Actor");
	m_wpLoverboyActor.lock()->SetActorScale({ 150.f, 150.f, 0.f });
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

#pragma endregion

#pragma region 아이템
	m_wpSyringeActor = CreateActor<CSyringeActor>(L"Syringe2", L"Item", L"Actor");
	m_wpSyringeActor.lock()->SetActorPosition({ 48.0f, 5.0f, 2800.0f });
	
	m_wpArmorPieceActor = CreateActor<CArmorPieceActor>(L"ArmorPiece", L"Item", L"Actor");
	m_wpArmorPieceActor.lock()->SetActorPosition({ 0.f, 5.0f, 30.0f });

	m_wpArmorActor = CreateActor<CArmorActor>(L"Armor2", L"Item", L"Actor");
	m_wpArmorActor.lock()->SetActorPosition({ 0.f, 5.0f, 35.0f });
	m_wpArmorActor.lock()->SetCapaType(2);

	for (int32 i = 0; i < 20; i++)
	{
		m_wpArmorPieceActor = CreateActor<CArmorPieceActor>(L"ArmorPiece" + std::to_wstring(i), L"Item", L"Actor");
		m_wpArmorPieceActor.lock()->SetActorPosition({ 0.f, 5.0f, 2400.0f - float(i * 64) });
	}

	for (int32 i = 20; i < 30; i++)
	{
		m_wpArmorPieceActor = CreateActor<CArmorPieceActor>(L"ArmorPiece" + std::to_wstring(i), L"Item", L"Actor");
		m_wpArmorPieceActor.lock()->SetActorPosition({ 160.f, 21.0f, 800.0f - float((i - 20) * 64) });
	}

	for (int32 i = 30; i < 50; i++)
	{
		m_wpArmorPieceActor = CreateActor<CArmorPieceActor>(L"ArmorPiece" + std::to_wstring(i), L"Item", L"Actor");
		m_wpArmorPieceActor.lock()->SetActorPosition({ 64.f, 135.0f, 0.0f + float((i- 30) * 64) });
	}

	m_wpCardKeyActor = CreateActor<CCardKeyActor>(L"CardKey", L"Item", L"Actor");
	m_wpCardKeyActor.lock()->SetActorPosition({ 192.f, 140.f, 1530.f });
	m_wpCardKeyActor.lock()->SetCapaType(0);

	m_wpCardKeyActor = CreateActor<CCardKeyActor>(L"CardKey1", L"Item", L"Actor");
	m_wpCardKeyActor.lock()->SetActorPosition({ 192.f, 21.f, 200.f });
	m_wpCardKeyActor.lock()->SetCapaType(0);

#pragma endregion

#pragma region 오브젝트

	// 아이템 임시소환입니다. 11.14 검사용
	for (int32 i = 0; i < 2; i++)
	{
		// 쓰레기봉투
		m_wpGarbage = CreateActor<CGarbageActor>(L"Garbage" + std::to_wstring(i), L"Item", L"Actor");
		m_wpGarbage.lock()->SetActorPosition({ 0.f, 5.0f, 45.0f + float(i * 15) });
		m_wpGarbage.lock()->SetRecoveryType(ERecoveryType::HEALTHPACK);
		m_wpGarbage.lock()->SetCapaType(i);
	}
	// 쓰레기통
	m_wpTrashCan = CreateActor<CTrashCanActor>(L"TrashCan0", L"Item", L"Actor");
	m_wpTrashCan.lock()->SetActorPosition({ 200.0f, 24.0f, 520.0f });
	m_wpTrashCan.lock()->SetWeaponType(EWeaponType::LOVERBOY);
	m_wpTrashCan.lock()->SetCapaType(1);

	m_wpTrashCan = CreateActor<CTrashCanActor>(L"TrashCan1", L"Item", L"Actor");
	m_wpTrashCan.lock()->SetActorPosition({ 192.0f, 132.0f, 1016.0f });
	m_wpTrashCan.lock()->SetWeaponType(EWeaponType::DISPERSER);
	m_wpTrashCan.lock()->SetActorScale({ 0.5f, 0.5f, 0.5f });

	m_wpTrashCan = CreateActor<CTrashCanActor>(L"TrashCan2", L"Item", L"Actor");
	m_wpTrashCan.lock()->SetActorPosition({ 192.0f, 132.0f, 1064.0f });
	m_wpTrashCan.lock()->SetWeaponType(EWeaponType::PENETRATOR);
	m_wpTrashCan.lock()->SetActorScale({ 0.5f, 0.5f, 0.5f });

	m_wpTrashCan = CreateActor<CTrashCanActor>(L"TrashCan3", L"Item", L"Actor");
	m_wpTrashCan.lock()->SetActorPosition({ 192.0f, 132.0f, 1112.0f });
	m_wpTrashCan.lock()->SetWeaponType(EWeaponType::CHAINGUN);
	m_wpTrashCan.lock()->SetActorScale({ 0.5f, 0.5f, 0.5f });

	m_wpChainGunItemActor = CreateActor<CChainGunItemActor>(L"ChainGunItem", L"Item", L"Actor");
	m_wpChainGunItemActor.lock()->SetActorPosition({ 64.0f, 5.0f, 2800.0f });

#pragma endregion 

#pragma region 몬스터
	for (int32 i = 0; i < 6; i++)
	{
		// 거미
		m_wpMechsect = CreateActor<CMechsect>(L"Mechsect" + std::to_wstring(i), L"Mechsect", L"Monster");
		m_wpMechsect.lock()->SetActorPosition({ 128.0f, 190.0f, 400.0f + (24.0f * float(i)) });
		m_wpMechsect.lock()->SetActorScale({ 16.0f, 16.0f, 16.0f });
	}

	for (int32 i = 6; i < 12; i++)
	{
		// 거미
		m_wpMechsect = CreateActor<CMechsect>(L"Mechsect" + std::to_wstring(i), L"Mechsect", L"Monster");
		m_wpMechsect.lock()->SetActorPosition({ 144.0f, 190.0f, 800.0f + (24.0f * float(i - 6)) });
		m_wpMechsect.lock()->SetActorScale({ 16.0f, 16.0f, 16.0f });
	}

	for (int32 i = 12; i < 20; i++)
	{
		// 거미
		m_wpMechsect = CreateActor<CMechsect>(L"Mechsect" + std::to_wstring(i), L"Mechsect", L"Monster");
		m_wpMechsect.lock()->SetActorPosition({ 64.0f, 190.0f, 800.0f + (24.0f * float(i - 12)) });
		m_wpMechsect.lock()->SetActorScale({ 16.0f, 16.0f, 16.0f });
	}

	for (int32 i = 0; i < 4; i++)
	{
		// 좀비
		m_wpPustule = CreateActor<CPustule>(L"Pustule" + std::to_wstring(i), L"Pustule", L"Monster");
		m_wpPustule.lock()->SetActorPosition({ 32.0f, 60.0f, 2400.f + (24.0f * float(i)) });
		m_wpPustule.lock()->SetActorScale({ 24.0f, 24.0f, 24.0f });
	}

	for (int32 i = 4; i < 9; i++)
	{
		// 좀비
		m_wpPustule = CreateActor<CPustule>(L"Pustule" + std::to_wstring(i), L"Pustule", L"Monster");
		m_wpPustule.lock()->SetActorPosition({ 64.0f, 60.0f, 1800.f + (24.0f * float(i - 4)) });
		m_wpPustule.lock()->SetActorScale({ 24.0f, 24.0f, 24.0f });
	}

	for (int32 i = 9; i < 15; i++)
	{
		// 좀비
		m_wpPustule = CreateActor<CPustule>(L"Pustule" + std::to_wstring(i), L"Pustule", L"Monster");
		m_wpPustule.lock()->SetActorPosition({ 64.0f, 60.0f, 1600.f + (24.0f * float(i - 9)) });
		m_wpPustule.lock()->SetActorScale({ 24.0f, 24.0f, 24.0f });
	}

	for (int32 i = 15; i < 20; i++)
	{
		// 좀비
		m_wpPustule = CreateActor<CPustule>(L"Pustule" + std::to_wstring(i), L"Pustule", L"Monster");
		m_wpPustule.lock()->SetActorPosition({ 160.0f, 60.0f, 1200.f + (24.0f * float(i - 15)) });
		m_wpPustule.lock()->SetActorScale({ 24.0f, 24.0f, 24.0f });
	}

	for (int32 i = 20; i < 23; i++)
	{
		// 좀비
		m_wpPustule = CreateActor<CPustule>(L"Pustule" + std::to_wstring(i), L"Pustule", L"Monster");
		m_wpPustule.lock()->SetActorPosition({ 160.0f, 60.0f, 800.f + (24.0f * float(i - 20)) });
		m_wpPustule.lock()->SetActorScale({ 24.0f, 24.0f, 24.0f });
	}

	for (int32 i = 23; i < 28; i++)
	{
		// 좀비
		m_wpPustule = CreateActor<CPustule>(L"Pustule" + std::to_wstring(i), L"Pustule", L"Monster");
		m_wpPustule.lock()->SetActorPosition({ 160.0f, 60.0f, 400.f + (24.0f * float(i - 23)) });
		m_wpPustule.lock()->SetActorScale({ 24.0f, 24.0f, 24.0f });
	}

	for (int32 i = 28; i < 36; i++)
	{
		// 좀비
		m_wpPustule = CreateActor<CPustule>(L"Pustule" + std::to_wstring(i), L"Pustule", L"Monster");
		m_wpPustule.lock()->SetActorPosition({ 64.0f, 60.0f, 400.f + (24.0f * float(i - 28)) });
		m_wpPustule.lock()->SetActorScale({ 24.0f, 24.0f, 24.0f });
	}

	for (int32 i = 36; i < 42; i++)
	{
		// 좀비
		m_wpPustule = CreateActor<CPustule>(L"Pustule" + std::to_wstring(i), L"Pustule", L"Monster");
		m_wpPustule.lock()->SetActorPosition({ 32.0f, 200.0f, 800.0f + (24.0f * float(i - 36)) });
		m_wpPustule.lock()->SetActorScale({ 24.0f, 24.0f, 24.0f });
	}

	for (int32 i = 42; i < 48; i++)
	{
		// 좀비
		m_wpPustule = CreateActor<CPustule>(L"Pustule" + std::to_wstring(i), L"Pustule", L"Monster");
		m_wpPustule.lock()->SetActorPosition({ 48.0f, 200.0f, 1000.0f + (24.0f * float(i - 42)) });
		m_wpPustule.lock()->SetActorScale({ 24.0f, 24.0f, 24.0f });
	}

	for (int32 i = 48; i < 54; i++)
	{
		// 좀비
		m_wpPustule = CreateActor<CPustule>(L"Pustule" + std::to_wstring(i), L"Pustule", L"Monster");
		m_wpPustule.lock()->SetActorPosition({ 64.0f, 200.0f, 1200.0f + (24.0f * float(i - 48)) });
		m_wpPustule.lock()->SetActorScale({ 24.0f, 24.0f, 24.0f });
	}
#pragma endregion

#pragma region UI

	m_wpOutGameUI = CreateActor<COutGameUI>(L"OutGameUI", L"UI", L"Actor");
	m_wpOutGameUI.lock()->SetActorPosition({ 0.f,0.f,1.f });
	m_wpOutGameUI.lock()->SetActorScale({ 1.f, 1.f, 0.f });
#pragma endregion

#pragma region 문 and 변압기 동준 추가

	// 변압기
	m_wpPowerMonitor = CreateActor<CPowerMonitor>(L"PowerMonitor", L"InteractiveBox", L"Actor");
	m_wpPowerMonitor.lock()->SetActorPosition({ 176.f, 144.f, 1550.f });
	m_wpPowerMonitor.lock()->SetActorScale({ 15.f, 10.f, 1.f });
	
	m_wpLeverGate = CreateActor<CLeverGate>(L"LeverGate", L"InteractiveBox", L"Actor");
	m_wpLeverGate.lock()->SetActorPosition({ 40.0f, 160.0f, 728.0f });
	m_wpLeverGate.lock()->SetActorScale({ 112.0f, 96.0f, 16.0f });
	m_wpLeverGate.lock()->SetActorRotation({ 0.f, 0.f, 180.f });
	//
	//////// 카드 키 인식 액터
	m_wpCardKeyBox = CreateActor<CCardKeyBox>(L"CardKeyBox", L"InteractiveBox", L"Actor");
	m_wpCardKeyBox.lock()->SetActorPosition({ 108.0f, 144.0f, 717.0f });
	m_wpCardKeyBox.lock()->SetActorScale({ 10.f, 5.f, 0.f });
	m_wpCardKeyBox.lock()->SetCardKeyGateActor(m_wpLeverGate.lock());

#pragma endregion

#pragma region 씬 전환 트리거

	m_wpSceneChanger = CreateActor<CSceneChangerActor>(L"SceneChangerToStage3", L"Trigger", L"Actor");
	m_wpSceneChanger.lock()->SetActorPosition({ 41.0f, 336.0f, 1875.0f });
	m_wpSceneChanger.lock()->SetActorScale({ 128.f, 128.f, 10.f });

#pragma endregion

	CLevel::Initialize();
}

void CStage2::BeginPlay()
{
	// 무기
	m_wpPlayerActor.lock()->AddWeapon(m_wpElectrifryerActor);
	m_wpPlayerActor.lock()->AddWeapon(m_wpLoverboyActor);
	m_wpPlayerActor.lock()->AddWeapon(m_wpDisperserActor);
	m_wpPlayerActor.lock()->AddWeapon(m_wpPenetratorActor);
	m_wpPlayerActor.lock()->AddWeapon(m_wpChainGunActor);

	// 이펙트
	m_wpPlayerActor.lock()->AddEffect(m_wpPlayerEffectActor);

	// 파티클
	// m_wpPlayerActor.lock()->AddParticle(m_wpPlayerParticleActor);

	NonDestroyData tNonDestroyData = CGameManager::GetInstance()->GetNonDestroyData();

	m_wpLoverboyActor.lock()->SetSavedBulletLoaded(tNonDestroyData.prLoverboy.first);
	m_wpLoverboyActor.lock()->SetSavedBulletHolding(tNonDestroyData.prLoverboy.second);

	m_wpDisperserActor.lock()->SetSavedBulletLoaded(tNonDestroyData.prDisperser.first);
	m_wpDisperserActor.lock()->SetSavedBulletHolding(tNonDestroyData.prDisperser.second);

	m_wpPenetratorActor.lock()->SetSavedBulletLoaded(tNonDestroyData.prPenetrator.first);
	m_wpPenetratorActor.lock()->SetSavedBulletHolding(tNonDestroyData.prPenetrator.second);

	m_wpChainGunActor.lock()->SetSavedBulletLoaded(tNonDestroyData.prChainGun.first);
	m_wpChainGunActor.lock()->SetSavedBulletHolding(tNonDestroyData.prChainGun.second);

	m_wpPlayerActor.lock()->SetCurHp(tNonDestroyData.fCurHp);
	m_wpPlayerActor.lock()->SetCurArmor(tNonDestroyData.fCurArmor);
	m_wpPlayerActor.lock()->SetMaxArmor(tNonDestroyData.fMaxArmor);

	if (tNonDestroyData.bBlinkEnable) { m_wpPlayerActor.lock()->SetBlinkEnable(); }
	if (tNonDestroyData.bRecallEnable) { m_wpPlayerActor.lock()->SetRecallEnable(); }
	if (tNonDestroyData.bSandevistanEnable) { m_wpPlayerActor.lock()->SetSandevistanEnable(); }

	if (tNonDestroyData.bPenetratorEnable) { m_wpPlayerActor.lock()->SetPenetratorEnable(); }
	if (tNonDestroyData.bDisperserEnable) { m_wpPlayerActor.lock()->SetDisperserEnable(); }
	if (tNonDestroyData.bSandevistanEnable) { m_wpPlayerActor.lock()->SetChainGunEnable(); }
	CLevel::BeginPlay();
}

int32 CStage2::Update(const float& _fDeltaSeconds)
{
	if (CInputManager::GetInstance()->IsKeyDown(DIK_Y))
	{
		GetWorld().lock()->CreateLevel<CStage3>(L"Stage3");
		GetWorld().lock()->ChangeLevelTo(L"Stage3");
		GetWorld().lock()->RemoveLevel(L"Stage2");
		return -2;
	}
	return CLevel::Update(_fDeltaSeconds);
}

int32 CStage2::LateUpdate(const float& _fDeltaSeconds)
{
	return CLevel::LateUpdate(_fDeltaSeconds);
}

void CStage2::Render()
{
	CLevel::Render();
}

void CStage2::EndPlay()
{
	CLevel::EndPlay();
}

void CStage2::Release()
{
	m_wpSoundComponent.lock()->StopSoundEx(ESoundType::BGM);
	CLevel::Release();
}