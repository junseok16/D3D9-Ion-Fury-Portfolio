// Client.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include "pch.h"
#include "framework.h"
#include "Client.h"
#include "GameApp.h"

#include "TimerManager.h"
#include "FrameManager.h"
using namespace std;

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
HWND hWnd;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	// TODO: 여기에 코드를 입력합니다.
	MyRegisterClass(hInstance);

	// 애플리케이션 초기화를 수행합니다:
	if (!InitInstance (hInstance, nCmdShow)) { return FALSE; }
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));
	
	shared_ptr<CGameApp> spGameApp(make_shared<CGameApp>());
	spGameApp->PreInitialize(hInst, hWnd);
	spGameApp->Initialize();

	// 초기화 중에 시간이 계속 흐르는 것을 막아야 합니다.
	ENSURE(CTimerManager::GetInstance()->Initialize(L"TimerOuter"));
	ENSURE(CTimerManager::GetInstance()->Initialize(L"TimerInner"));
	ENSURE(CFrameManager::GetInstance()->Initialize(L"Frame144", 144.0f));

	// 기본 메시지 루프입니다:
	MSG msg{};
	while (true)
	{
		if (msg.message == WM_QUIT) { break; }

		if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		else
		{
			CTimerManager::GetInstance()->Update(L"TimerOuter");
			float fOuterDeltaSeconds = CTimerManager::GetInstance()->GetDeltaSeconds(L"TimerOuter");

			if (CFrameManager::GetInstance()->IsFrameRate(L"Frame144", fOuterDeltaSeconds))
			{
				CTimerManager::GetInstance()->Update(L"TimerInner");
				float fInnerDeltaSeconds = CTimerManager::GetInstance()->GetDeltaSeconds(L"TimerInner");

				switch (spGameApp->Update(fInnerDeltaSeconds))
				{
				case -2: spGameApp->Initialize(); continue;
				default: break;
				}

				switch (spGameApp->LateUpdate(fInnerDeltaSeconds))
				{
				case -2: spGameApp->Initialize(); continue;
				default: break;
				}

				spGameApp->Render();
			}
		}
	}
	spGameApp->Release();
	spGameApp.reset();

	_CrtDumpMemoryLeaks();
	return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style          = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc    = WndProc;
	wcex.cbClsExtra     = 0;
	wcex.cbWndExtra     = 0;
	wcex.hInstance      = hInstance;
	wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
	wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName   = NULL;
	wcex.lpszClassName  = L"Client";
	wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.
   RECT rc{ 0, 0, CFWINCX, CFWINCY };
   AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

   hWnd = CreateWindowW(L"Client", L"Client", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance, nullptr);
   if (!hWnd) { return FALSE; }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	/*
	case WM_CREATE:
		{
			::AllocConsole();
			FILE* pFile = freopen("CONOUT$", "wt", stdout);
		}
		break;
	*/

	case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			// 메뉴 선택을 구문 분석합니다:
			switch (wmId)
			{
			case IDM_EXIT:
				DestroyWindow(hWnd);
				break;

			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
		break;

	case WM_KEYDOWN:
		{
			int wmId = LOWORD(wParam);
			switch (wmId)
			{
			case VK_ESCAPE:
				DestroyWindow(hWnd);
				break;
			}
		}
	break;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
			EndPaint(hWnd, &ps);
		}
		break;

		
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	/*
	case WM_CLOSE:
		// ::FreeConsole();
		break;
	*/

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
