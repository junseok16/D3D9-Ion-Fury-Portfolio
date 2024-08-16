#include "pch.h"
#include "FrameManager.h"

#include "Frame.h"
using namespace std;

IMPLEMENT_SINGLETON(CFrameManager)

HRESULT CFrameManager::Initialize(const std::wstring& _wstrTag, const float& _fFrameRate)
{
	if (m_umapFrames.find(_wstrTag) != m_umapFrames.end()) { return E_FAIL; }
	shared_ptr<CFrame> spFrame = make_shared<CFrame>();
	spFrame->Initialize(_fFrameRate);

	m_umapFrames.insert({ _wstrTag, spFrame });
	return S_OK;
}

void CFrameManager::Release()
{
	for (auto& pair : m_umapFrames) { pair.second = nullptr; }
	m_umapFrames.clear();

	// 매니저 스마트 포인터를 해제합니다.
	m_upInstance.reset();
}

std::shared_ptr<CFrame> CFrameManager::FindFrame(const std::wstring& _wstrTag)
{
	if (m_umapFrames.find(_wstrTag) == m_umapFrames.end()) { return nullptr; }
	return m_umapFrames[_wstrTag];
}

bool CFrameManager::IsFrameRate(const std::wstring& _wstrTag, const float& fDeltaSeconds)
{
	if (m_umapFrames.find(_wstrTag) == m_umapFrames.end()) { return false; }
	return m_umapFrames[_wstrTag]->IsFrameRate(fDeltaSeconds);
}
