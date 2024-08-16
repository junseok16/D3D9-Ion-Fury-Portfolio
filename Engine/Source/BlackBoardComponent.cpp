#include "pch.h"
#include "BlackBoardComponent.h"
using namespace std;

void CBlackBoardComponent::Initialize()
{
	CActorComponent::Initialize();
}

void CBlackBoardComponent::BeginPlay()
{
	CActorComponent::BeginPlay();
}

int32 CBlackBoardComponent::Update(const float& _fDeltaSeconds)
{
	return CActorComponent::Update(_fDeltaSeconds);
}

int32 CBlackBoardComponent::LateUpdate(const float& _fDeltaSeconds)
{
	return CActorComponent::LateUpdate(_fDeltaSeconds);
}

void CBlackBoardComponent::EndPlay()
{
	CActorComponent::EndPlay();
}

void CBlackBoardComponent::Render()
{
	CActorComponent::Render();
}

void CBlackBoardComponent::Release()
{
	CActorComponent::Release();
}

void CBlackBoardComponent::ClearValue(const wstring& _wstrKey)
{
}

void CBlackBoardComponent::RemoveValue(const wstring& _wstrKey)
{
}

bool CBlackBoardComponent::GetValueAsBool(const wstring& _wstrKey)
{
	if (m_umapBoolValues.find(_wstrKey) != m_umapBoolValues.end())
	{
		return m_umapBoolValues[_wstrKey];
	}
	return false;
}

void CBlackBoardComponent::SetValueAsBool(const wstring& _wstrKey, bool _bValue)
{
	if (m_umapBoolValues.find(_wstrKey) == m_umapBoolValues.end())
	{
		m_umapBoolValues.insert({ _wstrKey, _bValue });
	}
	else
	{
		m_umapBoolValues[_wstrKey] = _bValue;
	}
}

float CBlackBoardComponent::GetValueAsFloat(const wstring& _wstrKey)
{
	if (m_umapFloatValues.find(_wstrKey) != m_umapFloatValues.end())
	{
		return m_umapFloatValues[_wstrKey];
	}
	return 0.0f;
}

void CBlackBoardComponent::SetValueAsFloat(const wstring& _wstrKey, float _fValue)
{
	if (m_umapFloatValues.find(_wstrKey) == m_umapFloatValues.end())
	{
		m_umapFloatValues.insert({ _wstrKey, _fValue });
	}
	else
	{
		m_umapFloatValues[_wstrKey] = _fValue;
	}
}

int CBlackBoardComponent::GetValueAsInt(const wstring& _wstrKey)
{
	if (m_umapIntValues.find(_wstrKey) != m_umapIntValues.end())
	{
		return m_umapIntValues[_wstrKey];
	}
	return 0;
}

void CBlackBoardComponent::SetValueAsInt(const wstring& _wstrKey, int _iValue)
{
	if (m_umapIntValues.find(_wstrKey) == m_umapIntValues.end())
	{
		m_umapIntValues.insert({ _wstrKey, _iValue });
	}
	else
	{
		m_umapIntValues[_wstrKey] = _iValue;
	}
}

wstring CBlackBoardComponent::GetValueAsWstring(const wstring& _wstrKey)
{
	if (m_umapWstringValues.find(_wstrKey) != m_umapWstringValues.end())
	{
		return m_umapWstringValues[_wstrKey];
	}
	return wstring(L"");
}

void CBlackBoardComponent::SetValueAsWstring(const wstring& _wstrKey, const wstring& _wstrValue)
{
	if (m_umapWstringValues.find(_wstrKey) == m_umapWstringValues.end())
	{
		m_umapWstringValues.insert({ _wstrKey, _wstrValue });
	}
	else
	{
		m_umapWstringValues[_wstrKey] = _wstrValue;
	}
}

FVector3 CBlackBoardComponent::GetValueAsFVector3(const wstring& _wstrKey)
{
	if (m_umapFVector3Values.find(_wstrKey) != m_umapFVector3Values.end())
	{
		return m_umapFVector3Values[_wstrKey];
	}
	return FVector3(0.0f, 0.0f, 0.0f);
}

void CBlackBoardComponent::SetValueAsFVector3(const wstring& _wstrKey, const FVector3& _vValue)
{
	if (m_umapFVector3Values.find(_wstrKey) == m_umapFVector3Values.end())
	{
		m_umapFVector3Values.insert({ _wstrKey, _vValue });
	}
	else
	{
		m_umapFVector3Values[_wstrKey] = _vValue;
	}
}

std::shared_ptr<CActor> CBlackBoardComponent::GetValueAsActor(const std::wstring& _wstrKey)
{
	if (m_umapActorValues.find(_wstrKey) != m_umapActorValues.end())
	{
		CHECK(!m_umapActorValues[_wstrKey].expired());
		return m_umapActorValues[_wstrKey].lock();
	}
	return nullptr;
}

void CBlackBoardComponent::SetValueAsActor(const std::wstring& _wstrKey, std::weak_ptr<CActor> _wpActor)
{
	if (m_umapActorValues.find(_wstrKey) == m_umapActorValues.end())
	{
		m_umapActorValues.insert({ _wstrKey, _wpActor });
	}
	else
	{
		m_umapActorValues[_wstrKey] = _wpActor;
	}
}
