#pragma once

class CInputManager final
{
	DECLARE_SINGLETON(CInputManager)

public:
	HRESULT Initialize(HINSTANCE _hInst, HWND _hWnd);
	void Update();
	void Release();

public:
	bool IsKeyDown		(int32 _iKey) { return GetKeyState(_iKey) == EKeyState::DOWN; }
	bool IsKeyPressed	(int32 _iKey) { return GetKeyState(_iKey) == EKeyState::PRESSED; }
	bool IsKeyUp		(int32 _iKey) { return GetKeyState(_iKey) == EKeyState::UP; }
	bool IsKeyReleased	(int32 _iKey) { return GetKeyState(_iKey) == EKeyState::RELEASED; }

	bool IsMouseDown	(EMouseButtonType _eMouseButtonType) { return GetMouseState(_eMouseButtonType) == EMouseState::DOWN; }
	bool IsMousePressed	(EMouseButtonType _eMouseButtonType) { return GetMouseState(_eMouseButtonType) == EMouseState::PRESSED; }
	bool IsMouseUp		(EMouseButtonType _eMouseButtonType) { return GetMouseState(_eMouseButtonType) == EMouseState::UP; }
	bool IsMouseReleased(EMouseButtonType _eMouseButtonType) { return GetMouseState(_eMouseButtonType) == EMouseState::RELEASED; }

	int32 GetMouseDeltaX() { return m_arrMouseDelta[(int32)EAxisType::X_AXIS]; }
	int32 GetMouseDeltaY() { return m_arrMouseDelta[(int32)EAxisType::Y_AXIS]; }
	int32 GetMouseDeltaZ() { return m_arrMouseDelta[(int32)EAxisType::Z_AXIS]; }
	std::tuple<int32, int32, int32> GetMouseDeltaAll(EAxisType _eAxisType) { return { m_arrMouseDelta[(int32)EAxisType::X_AXIS], m_arrMouseDelta[(int32)EAxisType::Y_AXIS],m_arrMouseDelta[(int32)EAxisType::Z_AXIS] }; }
	
	void SetCursorInCenter(bool _bCursorInCenter) { m_bCursorInCenter = _bCursorInCenter; }
	bool GetCursorInCenter() { return m_bCursorInCenter; }

private:
	EKeyState GetKeyState(uint8 _iKey) { return m_arrKeyStates[_iKey]; }
	EMouseState GetMouseState(EMouseButtonType _eMouseButtonType) { return m_arrMouseStates[(int8)_eMouseButtonType]; }

private:
	HWND m_hWnd{};
	bool m_bCursorInCenter = false;

	LPDIRECTINPUT8 m_pDeviceInput = nullptr;
	LPDIRECTINPUTDEVICE8 m_pDIKeyDevice = nullptr;
	LPDIRECTINPUTDEVICE8 m_pDIMouseDevice = nullptr;

	std::array<EKeyState, 256> m_arrKeyStates{ EKeyState::RELEASED };
	std::array<EMouseState, 3> m_arrMouseStates{ EMouseState::RELEASED };
	std::array<int32, 3> m_arrMouseDelta{ 0 };
};

