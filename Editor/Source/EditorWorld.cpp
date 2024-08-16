#include "pch.h"
#include "EditorWorld.h"
#include "EditorLevel.h"
#include "EditorCamera.h"

#include "ModeWindow.h"
#include "OutlinerWindow.h"
#include "IMGUIManager.h"
using namespace std;

void CEditorWorld::Initialize()
{
	// ������ ������ �����մϴ�.
	CreateLevel<CEditorLevel>(L"EditorLevel");
	ChangeLevelTo(L"EditorLevel");

	// ��� â�� �����մϴ�.
	m_spModeWindow = make_shared<CModeWindow>();
	m_spModeWindow->Initialize(m_wpLevel);

	// �ƿ����̳� â�� �����մϴ�.
	m_spOutlinerWindow = make_shared<COutlinerWindow>();
	m_spOutlinerWindow->Initialize(m_wpLevel);
	
	// ������ ī�޶� �����մϴ�.
	m_spEditorCamera = make_shared<CEditorCamera>();
	m_spEditorCamera->Initialize();

	CWorld::Initialize();
}

void CEditorWorld::BeginPlay()
{
	m_spModeWindow->BeginPlay();
	m_spOutlinerWindow->BeginPlay();
	CWorld::BeginPlay();
}

int32 CEditorWorld::Update(const float& _fDeltaSeconds)
{
	CIMGUIManager::GetInstance()->UpdateBegin();
	m_spModeWindow->Update(_fDeltaSeconds);
	m_spOutlinerWindow->Update(_fDeltaSeconds);
	CIMGUIManager::GetInstance()->UpdateEnd();

	m_spEditorCamera->Update(_fDeltaSeconds);
	return CWorld::Update(_fDeltaSeconds);
}

int32 CEditorWorld::LateUpdate(const float& _fDeltaSeconds)
{
	m_spModeWindow->LateUpdate(_fDeltaSeconds);
	m_spOutlinerWindow->LateUpdate(_fDeltaSeconds);
	return CWorld::LateUpdate(_fDeltaSeconds);
}

void CEditorWorld::Render()
{
	m_spModeWindow->Render();
	m_spOutlinerWindow->Render();
	CWorld::Render();
}

void CEditorWorld::EndPlay()
{
	m_spModeWindow->EndPlay();
	m_spOutlinerWindow->EndPlay();
	CWorld::EndPlay();
}

void CEditorWorld::Release()
{
	m_spModeWindow->Release();
	m_spOutlinerWindow->Release();
	m_spEditorCamera->Release();
	CWorld::Release();
}

