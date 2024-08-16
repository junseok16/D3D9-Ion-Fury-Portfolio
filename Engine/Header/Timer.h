#pragma once

class CTimer final
{
public:
	explicit CTimer() = default;
	virtual ~CTimer() = default;

public:
	HRESULT Initialize();
	void Update();

/********************
	Methods
********************/
	void Reset();
	void Start();
	void Stop();

/********************
	Getter/Setter
********************/
public:
	float GetDeltaSeconds() { return m_fDeltaSeconds; }

/********************
	Data Members
********************/
private:
	LARGE_INTEGER m_FixTime{};
	LARGE_INTEGER m_iCurFrequency{};
	LARGE_INTEGER m_iPrevFrequency{};
	LARGE_INTEGER m_iCpuFrequency{};
	float m_fDeltaSeconds = 0.0f;
};

