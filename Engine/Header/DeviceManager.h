#pragma once

class CDeviceManager final
{
	DECLARE_SINGLETON(CDeviceManager)

public:
	HRESULT Initialize(HWND _hWnd);
	void RenderBegin();
	void RenderEnd();
	void Release();

public:
	LPDIRECT3DDEVICE9 GetDirect3DDevice9() { return m_pD3DDevice9; }

	HWND GethWnd() const { return m_hWnd; }

private:
	LPDIRECT3D9 m_pD3D9 = nullptr;
	LPDIRECT3DDEVICE9 m_pD3DDevice9 = nullptr;
	HWND m_hWnd{};
};

