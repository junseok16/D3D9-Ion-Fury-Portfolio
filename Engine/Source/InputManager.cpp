#include "pch.h"
#include "InputManager.h"
using namespace std;

IMPLEMENT_SINGLETON(CInputManager)

HRESULT CInputManager::Initialize(HINSTANCE _hInst, HWND _hWnd)
{
	m_hWnd = _hWnd;

	// DirectInput COM 객체를 생성합니다.
	ENSURE(::DirectInput8Create(_hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDeviceInput, NULL));

	// 키보드 객체를 생성합니다.
	ENSURE(m_pDeviceInput->CreateDevice(GUID_SysKeyboard, &m_pDIKeyDevice, nullptr));
	ENSURE(m_pDIKeyDevice->SetDataFormat(&c_dfDIKeyboard));
	ENSURE(m_pDIKeyDevice->SetCooperativeLevel(_hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE));
	while (m_pDIKeyDevice->Acquire() == DIERR_INPUTLOST);

	// 마우스 객체를 생성합니다.
	ENSURE(m_pDeviceInput->CreateDevice(GUID_SysMouse, &m_pDIMouseDevice, nullptr));
	ENSURE(m_pDIMouseDevice->SetDataFormat(&c_dfDIMouse));
	ENSURE(m_pDIMouseDevice->SetCooperativeLevel(_hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE));
	while (m_pDIMouseDevice->Acquire() == DIERR_INPUTLOST);
	return S_OK;
}

void CInputManager::Update()
{
	// 키보드 입력을 업데이트 합니다.
	int8 asciiKeys[256];
	ENSURE(m_pDIKeyDevice->GetDeviceState(256, asciiKeys));

	for (uint32 iKey = 0; iKey < 256; iKey++)
	{
		// 키를 누른 경우
		if (asciiKeys[iKey] & 0x80)
		{
			switch (m_arrKeyStates[iKey])
			{
			// 이전에 눌렀거나 누르는 중인 경우
			case EKeyState::DOWN:
			case EKeyState::PRESSED:
				m_arrKeyStates[iKey] = EKeyState::PRESSED;
				break;

			// 이전에 뗐거나 떼는 중인 경우
			case EKeyState::UP:
			case EKeyState::RELEASED:
				m_arrKeyStates[iKey] = EKeyState::DOWN;
				break;
			}
		}

		// 키를 누르지 않은 경우
		else
		{
			switch (m_arrKeyStates[iKey])
			{
			// 이전에 눌렀거나 누르는 중인 경우
			case EKeyState::DOWN:
			case EKeyState::PRESSED:
				m_arrKeyStates[iKey] = EKeyState::UP;
				break;

			// 이전에 뗐거나 떼는 중인 경우
			case EKeyState::UP:
			case EKeyState::RELEASED:
				m_arrKeyStates[iKey] = EKeyState::RELEASED;
				break;
			}
		}
	}

	// 마우스 입력을 업데이트 합니다.
	DIMOUSESTATE m_tMouseState;
	ENSURE(m_pDIMouseDevice->GetDeviceState(sizeof(m_tMouseState), &m_tMouseState));

	for (uint32 iMouse = 0; iMouse < 3; iMouse++)
	{
		// 키를 누른 경우
		if (m_tMouseState.rgbButtons[iMouse])
		{
			switch (m_arrMouseStates[iMouse])
			{
			// 이전에 눌렀거나 누르는 중인 경우
			case EMouseState::DOWN:
			case EMouseState::PRESSED:
				m_arrMouseStates[iMouse] = EMouseState::PRESSED;
				break;

			// 이전에 뗐거나 떼는 중인 경우
			case EMouseState::UP:
			case EMouseState::RELEASED:
				m_arrMouseStates[iMouse] = EMouseState::DOWN;
				break;
			}
		}

		// 키를 누르지 않은 경우
		else
		{
			switch (m_arrMouseStates[iMouse])
			{
			// 이전에 눌렀거나 누르는 중인 경우
			case EMouseState::DOWN:
			case EMouseState::PRESSED:
				m_arrMouseStates[iMouse] = EMouseState::UP;
				break;

			// 이전에 뗐거나 떼는 중인 경우
			case EMouseState::UP:
			case EMouseState::RELEASED:
				m_arrMouseStates[iMouse] = EMouseState::RELEASED;
				break;
			}
		}
	}

	// 마우스의 움직임을 업데이트합니다.
	m_arrMouseDelta[0] = m_tMouseState.lX;
	m_arrMouseDelta[1] = m_tMouseState.lY;
	m_arrMouseDelta[2] = m_tMouseState.lZ;

	// 마우스를 스크린 가운데로 이동합니다.
	if (m_bCursorInCenter)
	{
		POINT ptCursor = { CIWINCX >> 1, CIWINCY >> 1 };
		ClientToScreen(m_hWnd, &ptCursor);
		SetCursorPos(ptCursor.x, ptCursor.y);
	}
}

void CInputManager::Release()
{
	ENSURE(m_pDIKeyDevice->Unacquire());
	if (m_pDIKeyDevice->Release()) { MESSAGE_BOX(TEXT("Failed to release m_pDIKeyBoard at CInputManager.")); }
	m_pDIKeyDevice = nullptr;

	ENSURE(m_pDIMouseDevice->Unacquire());
	if (m_pDIMouseDevice->Release()) { MESSAGE_BOX(TEXT("Failed to release m_pDIMouse at CInputManager.")); }
	m_pDIMouseDevice = nullptr;

	if (m_pDeviceInput->Release()) { MESSAGE_BOX(TEXT("Failed to release m_pDI at CInputManager.")); }
	m_pDeviceInput = nullptr;

	m_upInstance.reset();
}

