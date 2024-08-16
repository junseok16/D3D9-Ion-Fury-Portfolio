#include "pch.h"
#include "Frame.h"

HRESULT CFrame::Initialize(const float& _fFrameRate)
{
	m_fFrameRate = 1.0f / _fFrameRate;
	return S_OK;
}

bool CFrame::IsFrameRate(const float& _fDeltaSeconds)
{
	m_fSumDeltaSeconds += _fDeltaSeconds;
	if (m_fSumDeltaSeconds >= m_fFrameRate)
	{
		m_fSumDeltaSeconds = 0.0f;
		return true;
	}
	return false;
}
