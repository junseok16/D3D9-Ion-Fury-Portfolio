#include "pch.h"
#include "DeviceManager.h"
using namespace std;

IMPLEMENT_SINGLETON(CDeviceManager)

HRESULT CDeviceManager::Initialize(HWND _hWnd)
{
	m_hWnd = _hWnd;

	// IDirect3D9 인터페이스
	m_pD3D9 = ::Direct3DCreate9(D3D_SDK_VERSION);

	// 버텍스 프로세스
	D3DCAPS9 caps;
	ZeroMemory(&caps, sizeof(caps));
	ENSURE(m_pD3D9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps));
	
	int iVertexProcess = 0;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) { iVertexProcess |= D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED; }
	else { iVertexProcess |= D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED; }

	// IDirect3DDevice9 인터페이스
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	d3dpp.BackBufferWidth			= 1280;
	d3dpp.BackBufferHeight			= 720;
	d3dpp.BackBufferFormat			= D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount			= 1;

	d3dpp.MultiSampleType			= D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality		= 0;

	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow				= _hWnd;
	d3dpp.Windowed					= TRUE;
	d3dpp.EnableAutoDepthStencil	= TRUE;
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D24S8;

	d3dpp.FullScreen_RefreshRateInHz= D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval		= D3DPRESENT_INTERVAL_IMMEDIATE;

	ENSURE(m_pD3D9->CreateDevice
	(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		_hWnd,
		iVertexProcess,
		&d3dpp,
		&m_pD3DDevice9)
	);

	return S_OK;
}

void CDeviceManager::RenderBegin()
{
	ENSURE(m_pD3DDevice9->Clear(0, nullptr, D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 1.0f, 0));
	ENSURE(m_pD3DDevice9->BeginScene());
}

void CDeviceManager::RenderEnd()
{
	ENSURE(m_pD3DDevice9->EndScene());
	ENSURE(m_pD3DDevice9->Present(nullptr, nullptr, nullptr, nullptr));
}

void CDeviceManager::Release()
{
	if (m_pD3DDevice9->Release())	{ MESSAGE_BOX(TEXT("Failed to release m_pD3DDevice9 at CDeviceManager.")); }
	m_pD3DDevice9 = nullptr;

	if (m_pD3D9->Release())			{ MESSAGE_BOX(TEXT("Failed to release m_pD3D9 at CDeviceManager.")); }
	m_pD3D9 = nullptr;

	m_upInstance.reset();
}
