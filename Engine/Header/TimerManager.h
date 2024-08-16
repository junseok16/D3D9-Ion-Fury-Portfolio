#pragma once

class CTimer;

class CTimerManager final
{
	DECLARE_SINGLETON(CTimerManager)

/********************
	Methods
********************/
public:
	HRESULT Initialize(const std::wstring& _wstrTag);
	void Update(const std::wstring& _wstrTag);
	void Release();

public:
	std::shared_ptr<CTimer> FindTimer(const std::wstring& _wstrTag);

	float GetDeltaSeconds(const std::wstring& _wstrTag);

/********************
	Data Members
********************/
private:
	std::unordered_map<std::wstring, std::shared_ptr<CTimer>> m_umapTimers;
};

