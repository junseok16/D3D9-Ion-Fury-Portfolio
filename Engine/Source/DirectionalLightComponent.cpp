#include "pch.h"
#include "DirectionalLightComponent.h"
#include "DeviceManager.h"
using namespace std;

void CDirectionalLightComponent::Initialize()
{
	m_pD3DDevice9 = CDeviceManager::GetInstance()->GetDirect3DDevice9();
	CLightComponent::Initialize();
}

void CDirectionalLightComponent::BeginPlay()
{
	CLightComponent::BeginPlay();
}

int32 CDirectionalLightComponent::Update(const float& _fDeltaSeconds)
{
	return CLightComponent::Update(_fDeltaSeconds);
}

int32 CDirectionalLightComponent::LateUpdate(const float& _fDeltaSeconds)
{
	return CLightComponent::LateUpdate(_fDeltaSeconds);
}

void CDirectionalLightComponent::Render()
{
	CLightComponent::Render();
}

void CDirectionalLightComponent::EndPlay()
{
	CLightComponent::EndPlay();
}

void CDirectionalLightComponent::Release()
{
	m_pD3DDevice9->LightEnable(m_iIndex, FALSE);

	CLightComponent::Release();
}

void CDirectionalLightComponent::SetDirLightInfo(D3DCOLORVALUE Diffuse, D3DCOLORVALUE Specular, D3DCOLORVALUE Ambient, D3DVECTOR Direction, UINT _iIndex)
{
	m_tLightInfo.Type = D3DLIGHT_DIRECTIONAL;
	m_tLightInfo.Diffuse = Diffuse;
	m_tLightInfo.Specular = Specular;
	m_tLightInfo.Ambient = Ambient;
	m_tLightInfo.Direction = Direction;

	m_iIndex = _iIndex;

	m_pD3DDevice9->SetLight(m_iIndex, &m_tLightInfo);
	m_pD3DDevice9->LightEnable(m_iIndex, TRUE);
}