#pragma once

class CWorld;

class CGameApp final
{
public:
	explicit CGameApp() = default;
	~CGameApp();

public:
	HRESULT PreInitialize(HINSTANCE _hInst, HWND _hWnd);
	HRESULT Initialize();
	int32 Update(const float& _fDeltaSeconds);
	int32 LateUpdate(const float& _fDeltaSeconds);
	void Render();
	void Release();

private:
	std::shared_ptr<CWorld> m_spWorld = nullptr;
};

