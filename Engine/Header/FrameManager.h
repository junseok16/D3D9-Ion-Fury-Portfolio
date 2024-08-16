#pragma once

class CFrame;

class CFrameManager final
{
	DECLARE_SINGLETON(CFrameManager)

/********************
	Framework
********************/
public:
	HRESULT Initialize(const std::wstring& _wstrTag, const float& _fFrameRate);
	void Release();

/********************
	Methods
********************/
public:
	std::shared_ptr<CFrame> FindFrame(const std::wstring& _wstrTag);

	bool IsFrameRate(const std::wstring& _wstrTag, const float& fDeltaSeconds);

/********************
	Data Members
********************/
private:
	std::unordered_map<std::wstring, std::shared_ptr<CFrame>> m_umapFrames;
};

