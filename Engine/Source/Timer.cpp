#include "pch.h"
#include "Timer.h"

HRESULT CTimer::Initialize()
{
	QueryPerformanceFrequency(&m_iCpuFrequency);
	QueryPerformanceCounter(&m_iCurFrequency);
	QueryPerformanceCounter(&m_FixTime);
	QueryPerformanceCounter(&m_iPrevFrequency);
	return S_OK;
}

void CTimer::Update()
{
	QueryPerformanceCounter(&m_iCurFrequency);

	if (m_iCurFrequency.QuadPart - m_FixTime.QuadPart >= m_iCpuFrequency.QuadPart)
	{
		QueryPerformanceFrequency(&m_iCpuFrequency);
		m_FixTime = m_iCurFrequency;
	}

	// 델타 타임을 구합니다.
	m_fDeltaSeconds = static_cast<float>(m_iCurFrequency.QuadPart - m_iPrevFrequency.QuadPart) / static_cast<float>(m_iCpuFrequency.QuadPart);
	m_fDeltaSeconds > 0.0f ? m_fDeltaSeconds : 0.0f;

	m_iPrevFrequency = m_iCurFrequency;
}

void CTimer::Reset()
{
}

void CTimer::Start()
{
}

void CTimer::Stop()
{
}
