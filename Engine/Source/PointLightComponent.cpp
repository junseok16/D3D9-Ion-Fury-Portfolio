#include "pch.h"
#include "PointLightComponent.h"
#include "DeviceManager.h"
using namespace std;

void CPointLightComponent::Initialize()
{
	m_pD3DDevice9 = CDeviceManager::GetInstance()->GetDirect3DDevice9();
	CLightComponent::Initialize();
}

void CPointLightComponent::BeginPlay()
{
	/*m_pD3DDevice9->SetLight(m_iIndex, &m_tLightInfo);
	m_pD3DDevice9->LightEnable(m_iIndex, TRUE);*/

	CLightComponent::BeginPlay();
}

int32 CPointLightComponent::Update(const float& _fDeltaSeconds)
{
	return CLightComponent::Update(_fDeltaSeconds);
}

int32 CPointLightComponent::LateUpdate(const float& _fDeltaSeconds)
{
	return CLightComponent::LateUpdate(_fDeltaSeconds);
}

void CPointLightComponent::Render()
{
	CLightComponent::Render();
}

void CPointLightComponent::EndPlay()
{
	CLightComponent::EndPlay();
}

void CPointLightComponent::Release()
{
	m_pD3DDevice9->LightEnable(m_iIndex, FALSE);

	CLightComponent::Release();
}

void CPointLightComponent::SetPointLightInfo(D3DCOLORVALUE Diffuse,
	D3DCOLORVALUE Specular,
	D3DCOLORVALUE Ambient,
	D3DVECTOR Position,
	float fRange,
	UINT _iIndex)
{
	m_tLightInfo.Type			= D3DLIGHT_POINT;	// 광원의 타입
	m_tLightInfo.Diffuse		= Diffuse;			// 광원이 발산하는 난반사광의 컬러
	m_tLightInfo.Specular		= Specular;			// 광원이 발산하는 정반사광의 컬러
	m_tLightInfo.Ambient		= Ambient;			// 광원이 발산하는 환경광의 컬러
	m_tLightInfo.Position		= Position;			// 광원의 위치를 정의하는 벡터
	m_tLightInfo.Range			= fRange;			// 빛의 소멸 거리

	m_iIndex = _iIndex;

	m_pD3DDevice9->SetLight(m_iIndex, &m_tLightInfo);
	m_pD3DDevice9->LightEnable(m_iIndex, TRUE);
}