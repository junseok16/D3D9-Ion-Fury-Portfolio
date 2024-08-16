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
	m_tLightInfo.Type			= D3DLIGHT_SPOT;		// ������ Ÿ��
	m_tLightInfo.Diffuse		= Diffuse;				// ������ �߻��ϴ� ���ݻ籤�� �÷�
	m_tLightInfo.Specular		= Specular;				// ������ �߻��ϴ� ���ݻ籤�� �÷�
	m_tLightInfo.Ambient		= Ambient;				// ������ �߻��ϴ� ȯ�汤�� �÷�
	m_tLightInfo.Position		= Position;				// ������ ��ġ�� �����ϴ� ����
	m_tLightInfo.Direction		= Direction;			// ���� ���ϴ� ������ �����ϴ� ����
	m_tLightInfo.Range			= fRange;				// ���� �Ҹ� �Ÿ�
	m_tLightInfo.Falloff		= fFalloff;				// ����Ʈ����Ʈ�� ���� ���԰� �ٱ��� ������ ���� ���� ����. ���� 1.0f
	m_tLightInfo.Theta			= fTheta;				// ���� ������ ����
	m_tLightInfo.Phi			= fPhi;					// �ٱ��� ������ ����

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

