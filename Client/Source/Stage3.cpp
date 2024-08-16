// Default
#include "pch.h"
#include "Stage1.h"
#include "Stage3.h"
#include "World.h"
#include "HanamuraLevel.h"

// Managers
#include "InputManager.h"
#include "CollisionManager.h"
#include "GameManager.h"

// Player
#include "SunActor.h"
#include "RainParticleActor.h"
#include "PlayerActor.h"
#include "PlayerEffectActor.h"
#include "PlayerParticleActor.h"
#include "SkyBox.h"

// Gimmick
#include "WallLaser.h"
#include "WallBlade.h"
#include "SceneChangerActor.h"

// Item
#include "ArmorPieceActor.h"
#include "LoverboyBulletActor.h"
#include "DisperserBulletActor.h"
#include "PenetratorBulletActor.h"
#include "ChainGunBulletActor.h"
#include "ArmorActor.h"

// 플레이어 무기 액터
#include "ElectrifryerActor.h"
#include "LoverboyActor.h"
#include "DisperserActor.h"
#include "PenetratorActor.h"
#include "ChainGunActor.h"

// Boss
#include "WarmechHead.h"
#include "WarmechLeg.h"
#include "WarmechCharge.h"
#include "WarmechSmash.h"
#include "BossTrigger.h"

// User Interface
#include "OutGameUI.h"
#include "InGameUI.h"

// Component
#include "CubeColliderComponent.h"
#include "RectangleMeshComponent.h"
#include "SoundComponent.h"
using namespace std;

void CStage3::Initialize()
{
	LoadLevelFromFile(L"Stage03");

	// 태양
	m_wpSun = CreateActor<CSunActor>(L"Sun", L"Light", L"Actor");

	// 스카이 박스
	m_wpSkyBox = CreateActor<CSkyBox>(L"SkyBox", L"Actor", L"Actor");
	m_wpSkyBox.lock()->SetSkybox(L"SkyBox3_0");
	m_wpSkyBox.lock()->SetActorPosition({ 300.0f, 120.0f, -600.0f });
	m_wpSkyBox.lock()->SetActorScale({ 1000.f, 1000.f, 1000.f });

	// 파티클
	m_wpRainParticleActor = CreateActor<CRainParticleActor>(L"Rain", L"Particle", L"Actor");
	m_wpRainParticleActor.lock()->SetActorPosition({ 0.0f, 150.0f, -40.0f });

	// 플레이어 액터
	m_wpPlayer = CreateActor<CPlayerActor>(L"Player", L"Player", L"Actor");
	m_wpPlayer.lock()->SetActorPosition({ 0.0f, 30.0f, -430.0f });
	m_wpPlayer.lock()->SetActorScale({ 10.0f, 24.0f, 10.0f });

	for (int32 iIndex = 0; iIndex < 10; ++iIndex)
	{
		shared_ptr<CLoverboyBulletActor> spLoverboyBullet = CreateActor<CLoverboyBulletActor>(L"LoverboyBullet" + to_wstring(iIndex), L"", L"");
		spLoverboyBullet->SetActorPosition({ -60.0f, 5.0f, -440.0f + 8.0f * iIndex });
		spLoverboyBullet->SetCapaType(1);
	}

	for (int32 iIndex = 0; iIndex < 10; ++iIndex)
	{
		shared_ptr<CDisperserBulletActor> spDisperserBullet = CreateActor<CDisperserBulletActor>(L"DisperserBullet" + to_wstring(iIndex), L"", L"");
		spDisperserBullet->SetActorPosition({ -30.0f, 5.0f, -440.0f + 8.0f * iIndex });
	}

	for (int32 iIndex = 0; iIndex < 10; ++iIndex)
	{
		shared_ptr<CPenetratorBulletActor> spPenetratorBullet = CreateActor<CPenetratorBulletActor>(L"PenetratorBullet" + to_wstring(iIndex), L"", L"");
		spPenetratorBullet->SetActorPosition({ 30.0f, 5.0f, -440.0f + 8.0f * iIndex });
	}

	for (int32 iIndex = 0; iIndex < 10; ++iIndex)
	{
		shared_ptr<CChainGunBulletActor> spChainGunBullet = CreateActor<CChainGunBulletActor>(L"ChainGunBulletActor" + to_wstring(iIndex), L"", L"");
		spChainGunBullet->SetActorPosition({ 60.0f, 5.0f, -440.0f + 8.0f * iIndex });
	}

	shared_ptr<CArmorActor> spArmorActor = CreateActor<CArmorActor>(L"ArmorActor", L"", L"");
	spArmorActor->SetActorPosition({ 0.0f, 5.0f, -410.0f });
	spArmorActor->SetCapaType(2);

	m_wpPlayerEffectActor = CreateActor<CPlayerEffectActor>(L"PlayerEffect", L"UI", L"Actor");
	m_wpPlayerEffectActor.lock()->SetActorPosition({ CFWINCX * 0.5f, CFWINCY * 0.5f, 0.0f });
	m_wpPlayerEffectActor.lock()->SetActorScale({ CFWINCX, CFWINCY, 1.0f });

	// 플레이어 무기 액터
	m_wpElectrifryer = CreateActor<CElectrifryerActor>(L"Electrifryer", L"Weapon", L"Actor");
	m_wpElectrifryer.lock()->SetActorScale({ 150.f, 150.f, 0.f });
	m_wpElectrifryer.lock()->SetActorPosition({ 100.0f, -100.0f, 5.0f });

	m_wpLoverboy = CreateActor<CLoverboyActor>(L"Loverboy", L"Weapon", L"Actor");
	m_wpLoverboy.lock()->SetActorScale({ 150.f, 150.f, 0.f });
	m_wpLoverboy.lock()->SetActorPosition({ 100.0f, -150.0f, 5.0f });
	
	m_wpDisperser = CreateActor<CDisperserActor>(L"Disperser", L"Weapon", L"Actor");
	m_wpDisperser.lock()->SetActorScale({ 150.f, 150.f, 0.f });
	m_wpDisperser.lock()->SetActorPosition({ 100.0f, -100.0f, 5.0f });

	m_wpPenetrator = CreateActor<CPenetratorActor>(L"Penetrator", L"Weapon", L"Actor");
	m_wpPenetrator.lock()->SetActorScale({ 150.f, 150.f, 0.f });
	m_wpPenetrator.lock()->SetActorPosition({ 100.0f, -100.0f, 5.0f });

	m_wpChainGun = CreateActor<CChainGunActor>(L"ChainGun", L"Weapon", L"Actor");
	m_wpChainGun.lock()->SetActorScale({ 150.f, 150.f, 0.f });
	m_wpChainGun.lock()->SetActorPosition({ 100.0f, -100.0f, 5.0f });

	// 보스 액터
	m_wpWarmechLeg = CreateActor<CWarmechLeg>(L"WarmechLeg", L"Boss", L"Actor");
	m_wpWarmechLeg.lock()->SetActorScale({ 80.0f, 80.0f, 80.0f });

	m_wpWarmechHead = CreateActor<CWarmechHead>(L"WarmechHead", L"Boss", L"Actor");
	m_wpWarmechHead.lock()->SetActorScale({ 80.0f, 80.0f, 80.0f });

	m_wpWarmechHead.lock()->SetWarmechLeg(m_wpWarmechLeg.lock());
	m_wpWarmechLeg.lock()->SetWarmechHead(m_wpWarmechHead.lock());
	
	// 돌진 액터를 생성합니다.
	// m_wpCharge = CreateActor<CWarmechCharge>(L"WarmechCharge", L"Skill", L"Actor");
	// m_wpWarmechLeg.lock()->SetCharge(m_wpCharge);  
	
	// 스매시 액터를 생성합니다.
	m_wpSmash = CreateActor<CWarmechSmash>(L"WarmechSmash", L"Skill", L"Actor");
	m_wpWarmechLeg.lock()->SetSmash(m_wpSmash);

	// 사용자 인터페이스
	m_wpOutGameUI = CreateActor<COutGameUI>(L"OutGameUI", L"UI", L"Actor");
	m_wpOutGameUI.lock()->SetActorPosition({ 0.0f, 0.0f, 1.0f });
	m_wpOutGameUI.lock()->SetActorScale({ 1.0f, 1.0f, 0.0f });

	// 안전하지 않은 안전 발판
	for (int32 iY = 0; iY < 4; ++iY)
	{
		for (int32 iX = 0; iX < 4; ++iX)
		{
			int32 iIndex = iX + 4 * iY;
			m_wpSafeFloor[iIndex] = CreateActor<CActor>(L"SafeFloorCenter" + iIndex, L"Env", L"Actor");
			m_wpSafeFloor[iIndex].lock()->SetActorScale({ 24.0f, 24.0f, 1.0f });
			m_wpSafeFloor[iIndex].lock()->SetActorRotation({ 90.0f, 0.0f, 0.0f });
			m_wpSafeFloor[iIndex].lock()->SetActorPosition({ -36.0f + 24.0f * iX, 0.0f, -36.0f + 24.0f * iY });

			shared_ptr<CRectangleMeshComponent> spRectMeshComponent = m_wpSafeFloor[iIndex].lock()->CreateActorComponent<CRectangleMeshComponent>(L"RectangleMeshComponent");
			spRectMeshComponent->SetRectangleMeshInfo(L"SafeFloor0_0", 0, 0);
			m_wpSafeFloor[iIndex].lock()->SetRootComponent(spRectMeshComponent);
		}
	}
	
	// 안전하지 않은 안전 발판 콜라이더
	// m_wpSafeFloorCollider = CreateActor<CActor>(L"SafeFloorCollider0", L"Env", L"Actor");
	// shared_ptr<CCubeColliderComponent> spCubeColliderComponent = m_wpSafeFloorCollider.lock()->CreateActorComponent<CCubeColliderComponent>(L"CubeColliderComponent");
	// m_wpSafeFloorCollider.lock()->SetActorScale({ 96.0f, 4.0f, 96.0f });
	// m_wpSafeFloorCollider.lock()->SetActorPosition({ 0.0f, -2.0f, 0.0f });
	// m_wpSafeFloorCollider.lock()->SetRootComponent(spCubeColliderComponent);
	// spCubeColliderComponent->SetCollisionLayerType(ECollisionLayerType::GROUND);
	// spCubeColliderComponent->AddCollisionLayer(ECollisionLayerType::PLAYER);
	// spCubeColliderComponent->AddCollisionLayer(ECollisionLayerType::MONSTER);
	// spCubeColliderComponent->AddCollisionLayer(ECollisionLayerType::ITEM);
	// CCollisionManager::GetInstance()->AddColliderComponent(spCubeColliderComponent);

	// 보스 트리거
	m_wpBossTrigger = CreateActor<CBossTrigger>(L"WarmechTrigger", L"Trigger", L"Actor");
	m_wpBossTrigger.lock()->SetActorPosition({ 0.0f, 20.0f, -100.0f });
	m_wpBossTrigger.lock()->SetActorScale({ 20.0f, 20.0f, 1.0f });
	m_wpBossTrigger.lock()->SetWarmechLeg(m_wpWarmechLeg);
	m_wpBossTrigger.lock()->SetWarmechHead(m_wpWarmechHead);

	// 신 전환 트리거
	// m_wpLevelChangeTrigger = CreateActor<CSceneChangerActor>(L"SceneChangerToStage4", L"Trigger", L"Actor");
	// m_wpLevelChangeTrigger.lock()->SetActorPosition({ 0.0f, 20.0f, -100.0f });
	// m_wpLevelChangeTrigger.lock()->SetActorScale({ 20.0f, 20.0f, 1.0f });

	// 레이저
	for (int32 iIndex = 0; iIndex < 12; ++iIndex)
	{
		m_wpWallLasers[iIndex] = CreateActor<CWallLaser>(L"WallLaser" + to_wstring(iIndex), L"Env", L"Actor");
		m_wpWallLasers[iIndex].lock()->SetActorScale({ 96.0f, 12.0f, 12.0f });
		m_wpWallLasers[iIndex].lock()->SetActorRotation({ 90.0f, 30.0f * iIndex, 0.0f });
		m_wpWallLasers[iIndex].lock()->SetActorPosition({ 0.0f, -96.0f - 12.0f * iIndex, 0.0f });
	}

	// 레이저
	for (int32 iIndex = 12; iIndex < 14; ++iIndex)
	{
		m_wpWallLasers[iIndex] = CreateActor<CWallLaser>(L"WallLaser" + to_wstring(iIndex), L"Env", L"Actor");
		m_wpWallLasers[iIndex].lock()->SetActorScale({ 96.0f, 12.0f, 12.0f });
		m_wpWallLasers[iIndex].lock()->SetActorRotation({ 90.0f, 0.0f, 0.0f });
		m_wpWallLasers[iIndex].lock()->SetActorPosition({ 0.0f, (-96.0f - 24.0f * 12), -24.0f * (iIndex - 12) });
		m_wpWallLasers[iIndex].lock()->SetMovementType(ELaserMovementType::VERTICAL);
		m_wpWallLasers[iIndex].lock()->SetMovementTime(5.0f);
		m_wpWallLasers[iIndex].lock()->SetSpeed(30.0f);
	}

	
	// 레이저
	for (int32 iIndex = 14; iIndex < 16; ++iIndex)
	{
		m_wpWallLasers[iIndex] = CreateActor<CWallLaser>(L"WallLaser" + to_wstring(iIndex), L"Env", L"Actor");
		m_wpWallLasers[iIndex].lock()->SetActorScale({ 96.0f, 12.0f, 12.0f });
		m_wpWallLasers[iIndex].lock()->SetActorRotation({ 90.0f, 90.0f, 0.0f });
		m_wpWallLasers[iIndex].lock()->SetActorPosition({ -24.0f * (iIndex - 14), (-96.0f - 24.0f * 14), 0.0f });
		m_wpWallLasers[iIndex].lock()->SetMovementType(ELaserMovementType::HORIZONTAL);
		m_wpWallLasers[iIndex].lock()->SetMovementTime(3.0f);
		m_wpWallLasers[iIndex].lock()->SetSpeed(20.0f);
	}

	// 레이저
	for (int32 iIndex = 16; iIndex < 18; ++iIndex)
	{
		m_wpWallLasers[iIndex] = CreateActor<CWallLaser>(L"WallLaser" + to_wstring(iIndex), L"Env", L"Actor");
		m_wpWallLasers[iIndex].lock()->SetActorScale({ 96.0f, 12.0f, 12.0f });
		m_wpWallLasers[iIndex].lock()->SetActorRotation({ 90.0f, 0.0f, 0.0f });
		m_wpWallLasers[iIndex].lock()->SetActorPosition({ 0.0f, (-96.0f - 24.0f * 16), 24.0f * (iIndex - 16) });
		m_wpWallLasers[iIndex].lock()->SetMovementType(ELaserMovementType::VERTICAL);
		m_wpWallLasers[iIndex].lock()->SetMovementTime(10.0f);
		m_wpWallLasers[iIndex].lock()->SetSpeed(20.0f);
	}
			
	// 레이저
	for (int32 iIndex = 18; iIndex < 20; ++iIndex)
	{
		m_wpWallLasers[iIndex] = CreateActor<CWallLaser>(L"WallLaser" + to_wstring(iIndex), L"Env", L"Actor");
		m_wpWallLasers[iIndex].lock()->SetActorScale({ 96.0f, 12.0f, 12.0f });
		m_wpWallLasers[iIndex].lock()->SetActorRotation({ 90.0f, 90.0f, 0.0f });
		m_wpWallLasers[iIndex].lock()->SetActorPosition({ 24.0f * (iIndex - 18), (-96.0f - 24.0f * 18), 0.0f });
		m_wpWallLasers[iIndex].lock()->SetMovementType(ELaserMovementType::HORIZONTAL);
		m_wpWallLasers[iIndex].lock()->SetMovementTime(2.0f);
	}
	
	// 칼날
	for (int32 iIndex = 0; iIndex < 2; ++iIndex)
	{
		m_wpWallBlade[iIndex] = CreateActor<CWallBlade>(L"WallBlade" + to_wstring(iIndex), L"Env", L"Actor");
		m_wpWallBlade[iIndex].lock()->SetActorScale({ 36.0f, 36.0f, 36.0f });
		m_wpWallBlade[iIndex].lock()->SetActorRotation({ 90.0f, 0.0f, 0.0f });
		m_wpWallBlade[iIndex].lock()->SetActorPosition({ -48.0f, (-96.0f - 24.0f * 20), -24.0f + 48.0f * iIndex });
		m_wpWallBlade[iIndex].lock()->SetMovementType(EBladeMovementType::VERTICAL);
		m_wpWallBlade[iIndex].lock()->SetMovementTime(3.0f);
		m_wpWallBlade[iIndex].lock()->SetSpeed(50.0f);
	}

	// 칼날
	for (int32 iIndex = 2; iIndex < 4; ++iIndex)
	{
		m_wpWallBlade[iIndex] = CreateActor<CWallBlade>(L"WallBlade" + to_wstring(iIndex), L"Env", L"Actor");
		m_wpWallBlade[iIndex].lock()->SetActorScale({ 36.0f, 36.0f, 36.0f });
		m_wpWallBlade[iIndex].lock()->SetActorRotation({ 90.0f, 0.0f, 0.0f });
		m_wpWallBlade[iIndex].lock()->SetActorPosition({ +48.0f, (-96.0f - 24.0f * 20), -24.0f + 48.0f * (iIndex - 2) });
		m_wpWallBlade[iIndex].lock()->SetMovementType(EBladeMovementType::VERTICAL);
		m_wpWallBlade[iIndex].lock()->SetMovementTime(3.0f);
		m_wpWallBlade[iIndex].lock()->SetSpeed(50.0f);
	}

	// 아머 피스
	for (int32 iIndex = 0; iIndex < 14; ++iIndex)
	{
		shared_ptr<CArmorPieceActor> spArmorPieceActor = CreateActor<CArmorPieceActor>(L"ArmorPiece" + to_wstring(iIndex), L"Item", L"Actor");
		spArmorPieceActor->SetActorPosition({ 0.0f, 4.0f, -380.0f + 20.0f * iIndex });
	}

	CLevel::Initialize();
}

void CStage3::BeginPlay()
{
	m_wpPlayer.lock()->AddEffect(m_wpPlayerEffectActor);

	m_wpPlayer.lock()->AddWeapon(m_wpElectrifryer);
	m_wpPlayer.lock()->AddWeapon(m_wpLoverboy);
	m_wpPlayer.lock()->AddWeapon(m_wpDisperser);
	m_wpPlayer.lock()->AddWeapon(m_wpPenetrator);
	m_wpPlayer.lock()->AddWeapon(m_wpChainGun);

	NonDestroyData tNonDestroyData = CGameManager::GetInstance()->GetNonDestroyData();

	m_wpLoverboy.lock()->SetSavedBulletLoaded(tNonDestroyData.prLoverboy.first);
	m_wpLoverboy.lock()->SetSavedBulletHolding(tNonDestroyData.prLoverboy.second);

	m_wpDisperser.lock()->SetSavedBulletLoaded(tNonDestroyData.prDisperser.first);
	m_wpDisperser.lock()->SetSavedBulletHolding(tNonDestroyData.prDisperser.second);

	m_wpPenetrator.lock()->SetSavedBulletLoaded(tNonDestroyData.prPenetrator.first);
	m_wpPenetrator.lock()->SetSavedBulletHolding(tNonDestroyData.prPenetrator.second);

	m_wpChainGun.lock()->SetSavedBulletLoaded(tNonDestroyData.prChainGun.first);
	m_wpChainGun.lock()->SetSavedBulletHolding(tNonDestroyData.prChainGun.second);

	m_wpPlayer.lock()->SetCurHp(tNonDestroyData.fCurHp);
	m_wpPlayer.lock()->SetCurArmor(tNonDestroyData.fCurArmor);
	m_wpPlayer.lock()->SetMaxArmor(tNonDestroyData.fMaxArmor);

	if (tNonDestroyData.bBlinkEnable) { m_wpPlayer.lock()->SetBlinkEnable(); }
	if (tNonDestroyData.bRecallEnable) { m_wpPlayer.lock()->SetRecallEnable(); }
	if (tNonDestroyData.bSandevistanEnable) { m_wpPlayer.lock()->SetSandevistanEnable(); }

	if (tNonDestroyData.bPenetratorEnable) { m_wpPlayer.lock()->SetPenetratorEnable(); }
	if (tNonDestroyData.bDisperserEnable) { m_wpPlayer.lock()->SetDisperserEnable(); }
	if (tNonDestroyData.bSandevistanEnable) { m_wpPlayer.lock()->SetChainGunEnable(); }

	CLevel::BeginPlay();
}

int32 CStage3::Update(const float& _fDeltaSeconds)
{
	return CLevel::Update(_fDeltaSeconds);
}

int32 CStage3::LateUpdate(const float& _fDeltaSeconds)
{
	return CLevel::LateUpdate(_fDeltaSeconds);
}

void CStage3::Render()
{
	CLevel::Render();
}

void CStage3::EndPlay()
{
	CLevel::EndPlay();
}

void CStage3::Release()
{
	CLevel::Release();
}
