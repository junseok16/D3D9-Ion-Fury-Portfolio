#pragma once

class CIMGUIManager final
{
	DECLARE_SINGLETON(CIMGUIManager)

public:
	HRESULT Initialize(HWND _hWnd);
	void UpdateBegin();
	void UpdateEnd();
	void Render();
	void Release();

private:
	HWND m_hWnd{};

	LPDIRECT3DDEVICE9 m_pD3DDevice9 = nullptr;
};

