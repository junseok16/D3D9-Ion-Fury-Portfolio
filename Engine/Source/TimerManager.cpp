#include "pch.h"
#include "TimerManager.h"

#include "Timer.h"
using namespace std;

IMPLEMENT_SINGLETON(CTimerManager)

HRESULT CTimerManager::Initialize(const std::wstring& _wstrTag)
{
	if (m_umapTimers.find(_wstrTag) != m_umapTimers.end()) { return E_FAIL; }
	shared_ptr<CTimer> spTimer = make_shared<CTimer>();
	spTimer->Initialize();

	m_umapTimers.insert({ _wstrTag, spTimer });
	return S_OK;
}

void CTimerManager::Update(const std::wstring& _wstrTag)
{
	std::shared_ptr<CTimer> spTimer = FindTimer(_wstrTag);
	if (spTimer != nullptr) { spTimer->Update(); }
}

void CTimerManager::Release()
{
	for (auto& pair : m_umapTimers) { pair.second = nullptr; }
	m_umapTimers.clear();

	// 매니저 스마트 포인터를 해제합니다.
	m_upInstance.reset();
}

std::shared_ptr<CTimer> CTimerManager::FindTimer(const std::wstring& _wstrTag)
{
	if (m_umapTimers.find(_wstrTag) == m_umapTimers.end()) { return nullptr; }
	return m_umapTimers[_wstrTag];
}

float CTimerManager::GetDeltaSeconds(const std::wstring& _wstrTag)
{
	if (m_umapTimers.find(_wstrTag) == m_umapTimers.end()) { return 0.0f; }
	return m_umapTimers[_wstrTag]->GetDeltaSeconds();
}
