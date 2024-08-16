#include "pch.h"
#include "EditorApp.h"
#include "EditorWorld.h"

// Engine headers
#include "DeviceManager.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "TimerManager.h"
#include "FrameManager.h"
#include "CollisionManager.h"
#include "ResourceManager.h"

// Editor headers
#include "IMGUIManager.h"
#include "SpawnManager.h"
#include "PrefabManager.h"
using namespace std;

HRESULT CEditorApp::PreInitialize(HINSTANCE _hInst, HWND _hWnd)
{
	ENSURE(CDeviceManager::GetInstance()->Initialize(_hWnd));
	ENSURE(CRenderManager::GetInstance()->Initialize(true));
	ENSURE(CInputManager::GetInstance()->Initialize(_hInst, _hWnd));
	ENSURE(CCollisionManager::GetInstance()->Initialize());
	ENSURE(CTimerManager::GetInstance()->Initialize(L"TimerOuter"));
	ENSURE(CTimerManager::GetInstance()->Initialize(L"TimerInner"));
	ENSURE(CFrameManager::GetInstance()->Initialize(L"Frame60", 60.0f));
	ENSURE(CResourceManager::GetInstance()->Initialize());
	ENSURE(CIMGUIManager::GetInstance()->Initialize(_hWnd));
	ENSURE(CPrefabManager::GetInstance()->Initialize());
	ENSURE(CSpawnManager::GetInstance()->Initialize());
	return S_OK;
}

HRESULT CEditorApp::Initialize()
{
	m_spEditorWorld = make_shared<CEditorWorld>();
	m_spEditorWorld->Initialize();
	m_spEditorWorld->BeginPlay();
	return S_OK;
}

int CEditorApp::Update(float _fDeltaSeconds)
{
	CInputManager::GetInstance()->Update();
	return m_spEditorWorld->Update(_fDeltaSeconds);
}

int CEditorApp::LateUpdate(float _fDeltaSeconds)
{
	return m_spEditorWorld->LateUpdate(_fDeltaSeconds);
}

void CEditorApp::Render()
{
	CDeviceManager::GetInstance()->RenderBegin();
	CRenderManager::GetInstance()->Render();
	CIMGUIManager::GetInstance()->Render();
	CDeviceManager::GetInstance()->RenderEnd();
}

void CEditorApp::Release()
{
	m_spEditorWorld->EndPlay();
	m_spEditorWorld->Release();
	m_spEditorWorld.reset();

	CSpawnManager::GetInstance()->Release();
	CPrefabManager::GetInstance()->Release();
	CIMGUIManager::GetInstance()->Release();
	CResourceManager::GetInstance()->Release();
	CTimerManager::GetInstance()->Release();
	CFrameManager::GetInstance()->Release();
	CCollisionManager::GetInstance()->Release();
	CInputManager::GetInstance()->Release();
	CRenderManager::GetInstance()->Release();
	CDeviceManager::GetInstance()->Release();
}
