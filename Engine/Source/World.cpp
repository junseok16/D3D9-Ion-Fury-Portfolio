#include "pch.h"
#include "World.h"
#include "Level.h"
#include "RenderManager.h"
#include "CollisionManager.h"
using namespace std;

void CWorld::Initialize()
{
	CHECK(!m_wpLevel.expired());
	m_wpLevel.lock()->Initialize();
}

void CWorld::BeginPlay()
{
	CHECK(!m_wpLevel.expired());
	m_wpLevel.lock()->BeginPlay();
}

int32 CWorld::Update(const float& _fDeltaSeconds)
{
	CHECK(!m_wpLevel.expired());
	return m_wpLevel.lock()->Update(_fDeltaSeconds);
}

int32 CWorld::LateUpdate(const float& _fDeltaSeconds)
{
	CHECK(!m_wpLevel.expired());
	return m_wpLevel.lock()->LateUpdate(_fDeltaSeconds);
}

void CWorld::EndPlay()
{
	CHECK(!m_wpLevel.expired());
	m_wpLevel.lock()->EndPlay();
}

void CWorld::Release()
{
	CHECK(!m_wpLevel.expired());
	m_wpLevel.lock()->Release();
}

void CWorld::Render()
{
	CHECK(!m_wpLevel.expired());
	m_wpLevel.lock()->Render();
}

void CWorld::ChangeLevelTo(const std::wstring& _wstrLevel)
{
	shared_ptr<CLevel> spLevel = FindLevel(_wstrLevel);
	CHECK(spLevel);
	
	m_wpLevel = spLevel;
}

void CWorld::RemoveLevel(const std::wstring& _wstrLevel)
{
	shared_ptr<CLevel> spLevel = FindLevel(_wstrLevel);
	if (spLevel == nullptr) { return; }
	
	CRenderManager::GetInstance()->Clear();
	spLevel->Release();
}

std::shared_ptr<CLevel> CWorld::FindLevel(const std::wstring& _wstrLevel)
{
	if (m_umapLevels.find(_wstrLevel) == m_umapLevels.end()) { return nullptr; }
	return m_umapLevels[_wstrLevel];
}
