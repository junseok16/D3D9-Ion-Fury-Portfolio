#include "pch.h"
#include "TestLevel.h"
#include "TerrainActor.h"
#include "PlayerActor.h"
#include "GenjiActor.h"
#include "ElectrifryerActor.h"

using namespace std;

void CTestLevel::Initialize()
{
	m_wpPlayerActor = CreateActor<CPlayerActor>(L"Player", L"Player", L"Actor");
	m_wpPlayerActor.lock()->SetActorPosition({ -100.0f, 60.0f, -100.0f });
	m_wpPlayerActor.lock()->SetActorScale({ 6.f, 10.f, 6.f });

	m_wpElectrifryerActor = CreateActor<CElectrifryerActor>(L"Electrifryer", L"Weapon", L"Actor");
	m_wpElectrifryerActor.lock()->SetActorScale({ 150.f, 150.f, 0.f });
	m_wpElectrifryerActor.lock()->SetActorPosition({ 0.0f, 0.0f, 5.0f });

	m_wpGenjiActor = CreateActor<CGenjiActor>(L"Genji", L"Genji", L"Actor");
	m_wpGenjiActor.lock()->SetActorPosition({ 1000.0f, -2.0f, 1000.0f });
	m_wpGenjiActor.lock()->SetActorRotation({ 0.0f, 0.0f, 0.0f });
	m_wpGenjiActor.lock()->SetActorScale({ 30.0f, 30.0f, 30.0f });

	m_wpTerrainActor = CreateActor<CTerrainActor>(L"Terrain", L"Terrain", L"Actor");
	m_wpGenjiActor.lock()->SetActorPosition({ 0.0f, 0.0f, 0.0f });
	m_wpGenjiActor.lock()->SetActorScale({ 30.0f, 30.0f, 30.0f });

	CLevel::Initialize();
}

void CTestLevel::BeginPlay()
{
	(m_wpPlayerActor.lock())->AddWeapon(m_wpElectrifryerActor);

	return CLevel::BeginPlay();
}

int32 CTestLevel::Update(const float& _fDeltaSeconds)
{
	return CLevel::Update(_fDeltaSeconds);
}

int32 CTestLevel::LateUpdate(const float& _fDeltaSeconds)
{
	return CLevel::LateUpdate(_fDeltaSeconds);
}

void CTestLevel::Render()
{
	CLevel::Render();
}

void CTestLevel::EndPlay()
{
	CLevel::EndPlay();
}

void CTestLevel::Release()
{
	CLevel::Release();
}
