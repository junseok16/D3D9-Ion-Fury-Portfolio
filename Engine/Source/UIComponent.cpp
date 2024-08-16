#include "pch.h"
#include "UIComponent.h"

#include "DeviceManager.h"
#include "TimerManager.h"
#include "UI.h"
#include "RenderManager.h"
#include "CameraComponent.h"
#include "AnimationComponent.h"
using namespace std;

void CUIComponent::Initialize()
{
	m_pD3DDevice9 = CDeviceManager::GetInstance()->GetDirect3DDevice9();
	m_eTextureType = ETextureType::TEXTURE;
	m_pD3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice9->SetRenderState(D3DRS_LIGHTING, FALSE);

	SetVertexInfo(4, sizeof(TextureVertex), TEXTURE_FVF);
	SetIndexInfo(2, sizeof(TextureIndex), D3DFMT_INDEX32);

	m_vecTextureVertices.reserve(4);
	m_vecTextureVertices.resize(4);
	m_vecTextureVertices[0] = { { -0.5f, +0.5f, 0.0f }, { 0.f, 0.f, 0.f }, { 0.0f, 0.0f } };
	m_vecTextureVertices[1] = { { +0.5f, +0.5f, 0.0f }, { 0.f, 0.f, 0.f }, { 1.0f, 0.0f } };
	m_vecTextureVertices[2] = { { +0.5f, -0.5f, 0.0f }, { 0.f, 0.f, 0.f }, { 1.0f, 1.0f } };
	m_vecTextureVertices[3] = { { -0.5f, -0.5f, 0.0f }, { 0.f, 0.f, 0.f }, { 0.0f, 1.0f } };

	m_vecTextureIndices.reserve(2);
	m_vecTextureIndices.resize(2);
	m_vecTextureIndices[0] = { 0, 1, 2 };
	m_vecTextureIndices[1] = { 0, 2, 3 };

	m_vecVertexWorldPos.reserve(4);
	m_vecVertexWorldPos.resize(4);
	m_vecVertexIndices.reserve(2);

	/*for (auto& pair : m_umapElements)
	{
		pair.second->Initialize();
	}*/

	CMeshComponent::Initialize();
}

void CUIComponent::BeginPlay()
{
	/*FVector3 vDst = { 0.f, 0.f, 0.f }, vSrc = { 0.f, 0.f, 0.f }, vNormal = { 0.f, 0.f, 0.f };

	vDst = m_vecTextureVertices[m_vecTextureIndices[0]._1].position - m_vecTextureVertices[m_vecTextureIndices[0]._0].position;
	vSrc = m_vecTextureVertices[m_vecTextureIndices[0]._2].position - m_vecTextureVertices[m_vecTextureIndices[0]._0].position;
	D3DXVec3Cross(&vNormal, &vDst, &vSrc);
	m_vecTextureVertices[m_vecTextureIndices[0]._0].normal += vNormal;
	m_vecTextureVertices[m_vecTextureIndices[0]._1].normal += vNormal;
	m_vecTextureVertices[m_vecTextureIndices[0]._2].normal += vNormal;

	vDst = m_vecTextureVertices[m_vecTextureIndices[1]._1].position - m_vecTextureVertices[m_vecTextureIndices[1]._0].position;
	vSrc = m_vecTextureVertices[m_vecTextureIndices[1]._2].position - m_vecTextureVertices[m_vecTextureIndices[1]._0].position;
	D3DXVec3Cross(&vNormal, &vDst, &vSrc);
	m_vecTextureVertices[m_vecTextureIndices[1]._0].normal += vNormal;
	m_vecTextureVertices[m_vecTextureIndices[1]._1].normal += vNormal;
	m_vecTextureVertices[m_vecTextureIndices[1]._2].normal += vNormal;

	D3DXVec3Normalize(&m_vecTextureVertices[0].normal, &m_vecTextureVertices[0].normal);
	D3DXVec3Normalize(&m_vecTextureVertices[1].normal, &m_vecTextureVertices[1].normal);
	D3DXVec3Normalize(&m_vecTextureVertices[2].normal, &m_vecTextureVertices[2].normal);
	D3DXVec3Normalize(&m_vecTextureVertices[3].normal, &m_vecTextureVertices[3].normal);*/

	//CAnimationComponent::BeginPlay();

	//CAnimationComponent::BeginPlay();
	/*for (auto& pair : m_umapElements)
	{
		pair.second->BeginPlay();
	}*/

	CMeshComponent::BeginPlay();
}

int32 CUIComponent::Update(const float& _fDeltaSeconds)
{
	/*for (auto& pair : m_umapElements)
	{
		int32 iResult = pair.second->Update(_fDeltaSeconds);
		if (iResult != 0) { return -1; }
	}*/

	return CMeshComponent::Update(_fDeltaSeconds);
}

int32 CUIComponent::LateUpdate(const float& _fDeltaSeconds)
{
	/*for (auto& pair : m_umapElements)
	{
		int32 iResult = pair.second->LateUpdate(_fDeltaSeconds);
		if (iResult != 0) { return -1; }
	}*/

	return CMeshComponent::LateUpdate(_fDeltaSeconds);
}

void CUIComponent::Render()
{
	CMeshComponent::Render();

	m_pD3DDevice9->SetRenderState(D3DRS_ZENABLE, FALSE);

	m_pD3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	// 월드 행렬(World matrix, W)을 설정합니다.
	m_pD3DDevice9->SetTransform(D3DTS_WORLD, &m_matWorld);

	// 스트림 소스를 버텍스 버퍼에 연결하여 렌더링 파이프라인에 보냅니다.
	m_pD3DDevice9->SetStreamSource(0, m_pVertexBuffer, 0, m_iVertexSize);

	// 버텍스 포맷을 설정합니다.
	m_pD3DDevice9->SetFVF(m_iVertexFormat);

	// 인덱스 버퍼를 설정합니다.
	m_pD3DDevice9->SetIndices(m_pIndexBuffer);

	// 텍스처 지정
	// m_pD3DDevice9->SetTexture(0, m_umapTextures[m_wstrCurrentState][m_iCurFrame]);

	m_pD3DDevice9->SetTexture(0, m_vecD3DTextures[m_iCurFrame]);

	// 인덱스 정보를 활용해 기본 도형을 그립니다.
	m_pD3DDevice9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_iNumVertices, 0, m_iNumTriangles);
	m_pD3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice9->SetRenderState(D3DRS_ZENABLE, TRUE);

	/*for (auto& pair : m_umapElements)
	{
		pair.second->Render();
	}*/
}

void CUIComponent::EndPlay()
{
	/*for (auto& pair : m_umapElements)
	{
		pair.second->EndPlay();
	}*/

	CMeshComponent::EndPlay();
}

void CUIComponent::Release()
{
	/*for (auto& pair : m_umapElements)
	{
		pair.second->Release();
	}*/

	CMeshComponent::Release();
}

//std::shared_ptr<CElement> CUIComponent::FindElement(const std::wstring& _wstrElement)
//{
//	if (m_umapElements.find(_wstrElement) == m_umapElements.end()) { return nullptr; }
//	return m_umapElements[_wstrElement];
//}

void CUIComponent::SettingUserInterfaceInfo(const std::wstring& _wstrTextureFileName,
	const uint32& _iFileBeginIndex, const uint32& _iFileEndIndex,
	const std::wstring& _wstrState, EUserInterfaceType _eUserInterfaceType)
{
	m_wstrTextureFileName = _wstrTextureFileName;
	m_iFileBeginIndex = _iFileBeginIndex;
	m_iFileEndIndex = _iFileEndIndex;

	m_eUserInterfaceType = _eUserInterfaceType;
	m_wstrCurrentState = _wstrState;

	// 추후 추가 할지 말지 고민중
	//m_iCurFrame = _iCurFrame;
}

void CUIComponent::AddUIState(const std::wstring& _wstrState, const uint32& _iBeginIndex, const uint32& _iEndIndex)
{
	m_umapUIStateFrame.insert({ _wstrState, std::make_pair(_iBeginIndex, _iEndIndex) });
}
