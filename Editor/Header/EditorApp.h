#pragma once

class CEditorWorld;

class CEditorApp final
{
public:
	explicit CEditorApp() = default;
	~CEditorApp() = default;

public:
	HRESULT PreInitialize(HINSTANCE _hInst, HWND _hWnd);
	HRESULT Initialize();
	int Update(float _fDeltaSeconds);
	int LateUpdate(float _fDeltaSeconds);
	void Render();
	void Release();

private:
	std::shared_ptr<CEditorWorld> m_spEditorWorld = nullptr;
};

