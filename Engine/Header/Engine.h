#pragma once

class CWorld;

class CEngine final
{
public:
	explicit CEngine() = default;
	~CEngine() = default;

public:
	HRESULT PreInitialize(HWND _hWnd);
	HRESULT Initialize();
	int Update(const float& _fDeltaSeconds);
	int LateUpdate(const float& _fDeltaSeconds);
	void Render();
	void Release();

private:
	std::shared_ptr<CWorld> m_spWorld = nullptr;
};

