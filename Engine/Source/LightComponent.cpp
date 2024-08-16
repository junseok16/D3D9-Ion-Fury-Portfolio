#include "pch.h"
#include "LightComponent.h"
#include "DeviceManager.h"
using namespace std;

void CLightComponent::Initialize()
{
	ZeroMemory(&m_tLightInfo, sizeof(D3DLIGHT9));
	CSceneComponent::Initialize();
}

void CLightComponent::BeginPlay()
{
	CSceneComponent::BeginPlay();
}

int32 CLightComponent::Update(const float& _fDeltaSeconds)
{
	return CSceneComponent::Update(_fDeltaSeconds);
}

int32 CLightComponent::LateUpdate(const float& _fDeltaSeconds)
{
	return CSceneComponent::LateUpdate(_fDeltaSeconds);
}

void CLightComponent::Render()
{
	CSceneComponent::Render();
}

void CLightComponent::EndPlay()
{
	CSceneComponent::EndPlay();
}

void CLightComponent::Release()
{
	CSceneComponent::Release();
}


void CLightComponent::SetLightOnOff(UINT _iIndex, BOOL bEnable)
{
	m_pD3DDevice9->LightEnable(_iIndex, bEnable);
}