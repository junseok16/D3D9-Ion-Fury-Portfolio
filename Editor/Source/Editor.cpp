// Editor.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "Editor.h"
#include "EditorApp.h"

#include "DeviceManager.h"
#include "TimerManager.h"
#include "FrameManager.h"
using namespace std;

#define MAX_LOADSTRING 100

// 전역 변수:
HWND g_hWnd;
HINSTANCE g_hInstance;

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	g_hInstance = hInstance;

/********************
	Register Class
********************/
	WNDCLASSEXW wcex;
	wcex.cbSize			= sizeof(WNDCLASSEX);
	wcex.style			= CS_CLASSDC;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0L;
	wcex.cbWndExtra		= 0L;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= nullptr;
	wcex.hCursor		= nullptr;
	wcex.hbrBackground	= nullptr;
	wcex.lpszMenuName	= nullptr;
	wcex.lpszClassName	= L"Editor";
	wcex.hIconSm		= nullptr;
	RegisterClassExW(&wcex);

/********************
	Initialize
********************/
	RECT rc{ 0, 0, CIWINCX, CIWINCY };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	g_hWnd = CreateWindowW
	(
		L"Editor",
		L"Editor",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		0,
		rc.right - rc.left,
		rc.bottom - rc.top,
		nullptr,
		nullptr,
		wcex.hInstance,
		nullptr
	);

	if (!g_hWnd) { return FALSE; }

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

/********************
	Main Loop
********************/
	shared_ptr<CEditorApp> spEditorApp(make_shared<CEditorApp>());
	spEditorApp->PreInitialize(g_hInstance, g_hWnd);
	spEditorApp->Initialize();

	bool done = false;
	while (!done)
	{
		MSG msg;
		while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);

			if (msg.message == WM_QUIT) { done = true; }
		}
		if (done) { break; }

		CTimerManager::GetInstance()->Update(L"TimerOuter");
		float fOuterDeltaSeconds = CTimerManager::GetInstance()->GetDeltaSeconds(L"TimerOuter");

		if (CFrameManager::GetInstance()->IsFrameRate(L"Frame60", fOuterDeltaSeconds))
		{
			CTimerManager::GetInstance()->Update(L"TimerInner");
			float fInnerDeltaSeconds = CTimerManager::GetInstance()->GetDeltaSeconds(L"TimerInner");

			spEditorApp->Update(fInnerDeltaSeconds);
			spEditorApp->LateUpdate(fInnerDeltaSeconds);
			spEditorApp->Render();
		}
	}

	spEditorApp->Release();
	spEditorApp.reset();

	::DestroyWindow(g_hWnd);
	::UnregisterClassW(wcex.lpszClassName, wcex.hInstance);
	_CrtDumpMemoryLeaks();
	return 0;

#pragma endregion
}

/*
* 함수: WndProc(HWND, UINT, WPARAM, LPARAM)
* 
* 용도: 주 창의 메시지를 처리합니다.
* 
* WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
* WM_PAINT    - 주 창을 그립니다.
* WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
*/
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam)) { return true; }

	switch (msg)
	{
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU) { return 0; }
		break;

	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;
	}
	return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}
