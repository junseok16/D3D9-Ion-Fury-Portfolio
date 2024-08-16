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
	m_tLightInfo.Type			= D3DLIGHT_POINT;	// ������ Ÿ��
	m_tLightInfo.Diffuse		= Diffuse;			// ������ �߻��ϴ� ���ݻ籤�� �÷�
	m_tLightInfo.Specular		= Specular;			// ������ �߻��ϴ� ���ݻ籤�� �÷�
	m_tLightInfo.Ambient		= Ambient;			// ������ �߻��ϴ� ȯ�汤�� �÷�
	m_tLightInfo.Position		= Position;			// ������ ��ġ�� �����ϴ� ����
	m_tLightInfo.Range			= fRange;			// ���� �Ҹ� �Ÿ�

	m_iIndex = _iIndex;

	m_pD3DDevice9->SetLight(m_iIndex, &m_tLightInfo);
	m_pD3DDevice9->LightEnable(m_iIndex, TRUE);
}