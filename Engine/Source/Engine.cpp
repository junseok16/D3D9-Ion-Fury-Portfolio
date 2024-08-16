#include "pch.h"
#include "Engine.h"

#include "DeviceManager.h"
#include "World.h"
using namespace std;

HRESULT CEngine::PreInitialize(HWND _hWnd)
{
	CDeviceManager::GetInstance()->Initialize(_hWnd);
	m_spWorld = make_shared<CWorld>();
	return S_OK;
}

HRESULT CEngine::Initialize()
{
	return m_spWorld->Initialize();
}

int CEngine::Update(const float& _fDeltaSeconds)
{
	return m_spWorld->Update(_fDeltaSeconds);
}

int CEngine::LateUpdate(const float& _fDeltaSeconds)
{
	return m_spWorld->LateUpdate(_fDeltaSeconds);
}

void CEngine::Render()
{
	CDeviceManager::GetInstance()->RenderBegin();
	m_spWorld->Render();
	CDeviceManager::GetInstance()->RenderEnd();
}

void CEngine::Release()
{
	m_spWorld->Release();
	CDeviceManager::GetInstance()->Release();
}
