#include "pch.h"
#include "GameApp.h"

#include "DeviceManager.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "TimerManager.h"
#include "FrameManager.h"
#include "FontManager.h"
#include "CollisionManager.h"
#include "SoundManager.h"
#include "ResourceManager.h"
#include "PrefabManager.h"
#include "SpawnManager.h"
#include "GameManager.h"

#include "World.h"
#include "HanamuraLevel.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"
#include "Stage4.h"
using namespace std;

CGameApp::~CGameApp() { }

HRESULT CGameApp::PreInitialize(HINSTANCE _hInst, HWND _hWnd)
{	
	ENSURE(CDeviceManager::GetInstance()->Initialize(_hWnd));
	ENSURE(CRenderManager::GetInstance()->Initialize(false));
	ENSURE(CInputManager::GetInstance()->Initialize(_hInst, _hWnd));
	ENSURE(CCollisionManager::GetInstance()->Initialize());
	ENSURE(CResourceManager::GetInstance()->Initialize());
	ENSURE(CPrefabManager::GetInstance()->Initialize());
	ENSURE(CSpawnManager::GetInstance()->Initialize());
	ENSURE(CSoundManager::GetInstance()->Initialize());
	ENSURE(CGameManager::GetInstance()->Initialize());

	// 초기화 중에 시간이 계속 흐르는 것을 막아야 합니다.
	// ENSURE(CTimerManager::GetInstance()->Initialize(L"TimerOuter"));
	// ENSURE(CTimerManager::GetInstance()->Initialize(L"TimerInner"));
	// ENSURE(CFrameManager::GetInstance()->Initialize(L"Frame144", 144.0f));
	return S_OK;
}

HRESULT CGameApp::Initialize()
{
	// 이곳에서 처음으로 로드될 신을 설정합니다.
	if (!m_spWorld)
	{
		m_spWorld = make_shared<CWorld>();
		m_spWorld->CreateLevel<CStage3>(L"Stage3");
		m_spWorld->ChangeLevelTo(L"Stage3");
	}
	
	m_spWorld->Initialize();
	m_spWorld->BeginPlay();
	return S_OK;
}

int32 CGameApp::Update(const float& _fDeltaSeconds)
{
	CInputManager::GetInstance()->Update();

	switch (CCollisionManager::GetInstance()->Update())
	{
	case -2:	return -2;
	default:	break;
	}

	return m_spWorld->Update(_fDeltaSeconds);
}

int32 CGameApp::LateUpdate(const float& _fDeltaSeconds)
{
	return m_spWorld->LateUpdate(_fDeltaSeconds);
}

void CGameApp::Render()
{
	CDeviceManager::GetInstance()->RenderBegin();
	CRenderManager::GetInstance()->Render();
	CDeviceManager::GetInstance()->RenderEnd();
}

void CGameApp::Release()
{
	m_spWorld->EndPlay();
	m_spWorld->Release();
	m_spWorld.reset();

	CGameManager::GetInstance()->Release();
	CSoundManager::GetInstance()->Release();
	CSpawnManager::GetInstance()->Release();
	CPrefabManager::GetInstance()->Release();
	CResourceManager::GetInstance()->Release();
	CTimerManager::GetInstance()->Release();
	CFrameManager::GetInstance()->Release();
	CCollisionManager::GetInstance()->Release();
	CInputManager::GetInstance()->Release();
	CRenderManager::GetInstance()->Release();
	CDeviceManager::GetInstance()->Release();
}
