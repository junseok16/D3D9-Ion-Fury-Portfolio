#pragma once

class CFrame final
{
public:
	explicit CFrame() = default;
	~CFrame() = default;

/********************
	Framework
********************/
public:
	HRESULT Initialize(const float& _fFrameRate);

public:
	bool IsFrameRate(const float& _fDeltaSeconds);

private:
	float m_fFrameRate = 0.0f;
	float m_fSumDeltaSeconds = 0.0f;
};

