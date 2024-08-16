#include "pch.h"
#include "SpotLightComponent.h"
#include "DeviceManager.h"
using namespace std;

void CSpotLightComponent::Initialize()
{
	m_pD3DDevice9 = CDeviceManager::GetInstance()->GetDirect3DDevice9();
	CLightComponent::Initialize();
}

void CSpotLightComponent::BeginPlay()
{
	CLightComponent::BeginPlay();
}

int32 CSpotLightComponent::Update(const float& _fDeltaSeconds)
{
	return CLightComponent::Update(_fDeltaSeconds);
}

int32 CSpotLightComponent::LateUpdate(const float& _fDeltaSeconds)
{
	return CLightComponent::LateUpdate(_fDeltaSeconds);
}

void CSpotLightComponent::Render()
{
	CLightComponent::Render();
}

void CSpotLightComponent::EndPlay()
{
	CLightComponent::EndPlay();
}

void CSpotLightComponent::Release()
{
	m_pD3DDevice9->LightEnable(m_iIndex, FALSE);

	CLightComponent::Release();
}

void CSpotLightComponent::SetSpotLightInfo(D3DCOLORVALUE Diffuse,
	D3DCOLORVALUE Specular,
	D3DCOLORVALUE Ambient,
	D3DVECTOR Position,
	D3DVECTOR Direction,
	float fRange,
	float fFalloff,
	float fTheta,
	float fPhi,
	UINT _iIndex)
{
	m_tLightInfo.Type			= D3DLIGHT_SPOT;		// 광원의 타입
	m_tLightInfo.Diffuse		= Diffuse;				// 광원이 발산하는 난반사광의 컬러
	m_tLightInfo.Specular		= Specular;				// 광원이 발산하는 정반사광의 컬러
	m_tLightInfo.Ambient		= Ambient;				// 광원이 발산하는 환경광의 컬러
	m_tLightInfo.Position		= Position;				// 광원의 위치를 정의하는 벡터
	m_tLightInfo.Direction		= Direction;			// 빛이 향하는 방향을 정의하는 벡터
	m_tLightInfo.Range			= fRange;				// 빛의 소멸 거리
	m_tLightInfo.Falloff		= fFalloff;				// 스포트라이트의 안쪽 원뿔과 바깥쪽 원뿔의 빛의 세기 차이. 보통 1.0f
	m_tLightInfo.Theta			= fTheta;				// 안쪽 원뿔의 각도
	m_tLightInfo.Phi			= fPhi;					// 바깥쪽 원뿔의 각도

	m_iIndex = _iIndex;

	m_pD3DDevice9->SetLight(m_iIndex, &m_tLightInfo);
	m_pD3DDevice9->LightEnable(m_iIndex, TRUE);
}

void CSpotLightComponent::SetLightPosition(D3DVECTOR Position, D3DVECTOR Direction, UINT _iIndex)
{
	m_tLightInfo.Position = Position;
	m_tLightInfo.Direction = Direction;
	m_iIndex = _iIndex;
	m_pD3DDevice9->SetLight(m_iIndex, &m_tLightInfo);
}

