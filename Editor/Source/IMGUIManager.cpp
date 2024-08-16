#include "pch.h"
#include "IMGUIManager.h"
#include "DeviceManager.h"

IMPLEMENT_SINGLETON(CIMGUIManager)

HRESULT CIMGUIManager::Initialize(HWND _hWnd)
{
	m_hWnd = _hWnd;
	m_pD3DDevice9 = CDeviceManager::GetInstance()->GetDirect3DDevice9();
	m_pD3DDevice9->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	m_pD3DDevice9->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(m_hWnd);
	ImGui_ImplDX9_Init(m_pD3DDevice9);

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	return S_OK;
}

void CIMGUIManager::UpdateBegin()
{
	ImGui::NewFrame();
}

void CIMGUIManager::UpdateEnd()
{
	ImGui::EndFrame();
}

void CIMGUIManager::Render()
{
	m_pD3DDevice9->SetRenderState(D3DRS_ZENABLE, FALSE);

	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	m_pD3DDevice9->SetRenderState(D3DRS_ZENABLE, TRUE);
}

void CIMGUIManager::Release()
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	// IMGUI 매니저를 해제합니다.
	m_upInstance.reset();
}
