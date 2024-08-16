#include "pch.h"
#include "InputComponent.h"

#include "InputManager.h"
using namespace std;

void CInputComponent::Initialize()
{
	CActorComponent::Initialize();
}

void CInputComponent::BeginPlay()
{
	CActorComponent::BeginPlay();
}

int32 CInputComponent::Update(const float& _fDeltaSeconds)
{
	// 엑시스 매핑을 업데이트합니다.
	for (const auto& lstAxisMaps : m_ummapAxisMaps)
	{
		int32 iKey = lstAxisMaps.second.first;
		if (CInputManager::GetInstance()->IsKeyPressed(iKey))
		{
			m_umapAxisCallbacks[lstAxisMaps.first](lstAxisMaps.second.second);
		}
	}

	// 액션 매핑을 업데이트합니다.
	for (const auto& lstActionMaps : m_ummapActionMaps)
	{
		int32 iKey = lstActionMaps.second;
		if (CInputManager::GetInstance()->IsKeyDown(iKey))
		{
			m_umapActionCallbacks[lstActionMaps.first]();
		}
	}

	return CActorComponent::Update(_fDeltaSeconds);
}

int32 CInputComponent::LateUpdate(const float& _fDeltaSeconds)
{
	return CActorComponent::LateUpdate(_fDeltaSeconds);
}

void CInputComponent::Render()
{
	CActorComponent::Render();
}

void CInputComponent::EndPlay()
{
	CActorComponent::EndPlay();
}

void CInputComponent::Release()
{
	CActorComponent::Release();
}

void CInputComponent::AxisMapping(const std::wstring& _wstrAxis, int32 _iKey, int32 _iScale)
{
	m_ummapAxisMaps.insert({ _wstrAxis, { _iKey, _iScale } });
}

void CInputComponent::ActionMapping(const std::wstring& _wstrAction, int32 _iKey)
{
	m_ummapActionMaps.insert({ _wstrAction, _iKey });
}
