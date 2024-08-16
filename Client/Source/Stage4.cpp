// Default
#include "pch.h"
#include "Stage4.h"

// Client
#include "SunActor.h"
#include "PlayerActor.h"
#include "Skinjob.h"

#include "FloatingBox.h"
#include "ThrowingBox.h"
#include "AcidWater.h"

#include "PlayerEffectActor.h"

#include "ElectrifryerActor.h"
#include "LoverboyActor.h"
#include "DisperserActor.h"
#include "PenetratorActor.h"
#include "ChainGunActor.h"

#include "OutGameUI.h"
#include "InGameUI.h"
using namespace std;

void CStage4::Initialize()
{
	// LoadLevelFromFile(L"Stage04");

	// 태양
	m_wpSun = CreateActor<CSunActor>(L"Sun", L"Light", L"Actor");

	// 플레이어 액터
	m_wpPlayer = CreateActor<CPlayerActor>(L"Player", L"Player", L"Actor");
	m_wpPlayer.lock()->SetActorPosition({ 0.0f, 50.0f, 0.0f });
	m_wpPlayer.lock()->SetActorScale({ 10.0f, 24.0f, 10.0f });

	// 플레이어 이펙트 액터
	m_wpPlayerEffectActor = CreateActor<CPlayerEffectActor>(L"PlayerEffect", L"UI", L"Actor");
	m_wpPlayerEffectActor.lock()->SetActorPosition({ CFWINCX * 0.5f, CFWINCY * 0.5f, 0.f });
	m_wpPlayerEffectActor.lock()->SetActorScale({ CFWINCX, CFWINCY, 1.f });

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
	m_wpSkinjob = CreateActor<CSkinjob>(L"Skinjob", L"Boss", L"Actor");
	m_wpSkinjob.lock()->SetActorPosition({ 0.0f, 112.0f, 112.0f });
	m_wpSkinjob.lock()->SetActorScale({ 16.0f, 32.0f, 16.0f });

	// 산성 물
	for (int32 iIndex = 0; iIndex < 9; ++iIndex)
	{
		for (int32 jIndex = 0; jIndex < 9; ++jIndex)
		{
			m_wpAcidWater[iIndex][jIndex] = CreateActor<CAcidWater>(L"AcidWater" + to_wstring(iIndex) + to_wstring(jIndex), L"Gimmick", L"Actor");
			m_wpAcidWater[iIndex][jIndex].lock()->SetActorPosition({ -144.0f + 36.0f * iIndex, 27.0f, -144.0f + 36.0f * jIndex });
		}
	}

	// 3 x 3 발판
	for (int32 jIndex = 0; jIndex < 3; ++jIndex)
	{
		for (int32 iIndex = 0; iIndex < 3; ++iIndex)
		{
			m_wpFloatingBox[jIndex][iIndex] = CreateActor<CFloatingBox>(L"FloatingBox" + to_wstring(jIndex) + to_wstring(iIndex), L"Gimmick", L"Actor");
			m_wpFloatingBox[jIndex][iIndex].lock()->SetActorPosition({ -36.0f + 36.0f * iIndex, 0.0f, 36.0f - 36.0f * jIndex });
			m_wpFloatingBox[jIndex][iIndex].lock()->SetFloatingBoxIndex(3 * jIndex + iIndex);
		}
	}

	// 던지는 박스
	for (int32 iIndex = 0; iIndex < 6; ++iIndex)
	{
		m_wpThrowingBox[iIndex] = CreateActor<CThrowingBox>(L"ThrowingBox" + to_wstring(iIndex), L"Gimmick", L"Actor");
		m_wpThrowingBox[iIndex].lock()->SetThrowingBoxIndex(iIndex);
	}

	CLevel::Initialize();
}

void CStage4::BeginPlay()
{
	m_wpPlayer.lock()->AddEffect(m_wpPlayerEffectActor);

	m_wpPlayer.lock()->AddWeapon(m_wpElectrifryer);
	m_wpPlayer.lock()->AddWeapon(m_wpLoverboy);
	m_wpPlayer.lock()->AddWeapon(m_wpDisperser);
	m_wpPlayer.lock()->AddWeapon(m_wpPenetrator);
	m_wpPlayer.lock()->AddWeapon(m_wpChainGun);

	CLevel::BeginPlay();
}

int32 CStage4::Update(const float& _fDeltaSeconds)
{
	return CLevel::Update(_fDeltaSeconds);
}

int32 CStage4::LateUpdate(const float& _fDeltaSeconds)
{
	return CLevel::LateUpdate(_fDeltaSeconds);
}

void CStage4::Render()
{
	CLevel::Render();
}

void CStage4::EndPlay()
{
	CLevel::EndPlay();
}

void CStage4::Release()
{
	CLevel::Release();
}
