#include "pch.h"
#include "SkyboxComponent.h"

#include "DeviceManager.h"
using namespace std;

void CSkyboxComponent::Initialize()
{
	m_pD3DDevice9 = CDeviceManager::GetInstance()->GetDirect3DDevice9();
	m_pD3DDevice9->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_eTextureType = ETextureType::CUBE_TEXTURE;

	SetVertexInfo(8, sizeof(CubeTextureVertex), CUBE_TEXTURE_FVF);
	SetIndexInfo(12, sizeof(CubeTextureIndex), D3DFMT_INDEX32);

	m_vecCubeTextureVertices.reserve(8);
	m_vecCubeTextureVertices.resize(8);

	m_vecCubeTextureVertices[0].position = { -1.0f, 1.0f, -1.0f };
	m_vecCubeTextureVertices[0].uv = m_vecCubeTextureVertices[0].position;
	
	m_vecCubeTextureVertices[1].position = { 1.0f, 1.0f, -1.0f };
	m_vecCubeTextureVertices[1].uv = m_vecCubeTextureVertices[1].position;
	
	m_vecCubeTextureVertices[2].position = { 1.0f, -1.0f, -1.0f };
	m_vecCubeTextureVertices[2].uv = m_vecCubeTextureVertices[2].position;
	
	m_vecCubeTextureVertices[3].position = { -1.0f, -1.0f, -1.0f };
	m_vecCubeTextureVertices[3].uv = m_vecCubeTextureVertices[3].position;
	
	m_vecCubeTextureVertices[4].position = { -1.0f, 1.0f, 1.0f };
	m_vecCubeTextureVertices[4].uv = m_vecCubeTextureVertices[4].position;
	
	m_vecCubeTextureVertices[5].position = { 1.0f, 1.0f, 1.0f };
	m_vecCubeTextureVertices[5].uv = m_vecCubeTextureVertices[5].position;
	
	m_vecCubeTextureVertices[6].position = { 1.0f, -1.0f, 1.0f };
	m_vecCubeTextureVertices[6].uv = m_vecCubeTextureVertices[6].position;
	
	m_vecCubeTextureVertices[7].position = { -1.0f, -1.0f, 1.0f };
	m_vecCubeTextureVertices[7].uv = m_vecCubeTextureVertices[7].position;

	m_vecCubeTextureIndices.reserve(12);
	m_vecCubeTextureIndices.resize(12);

	// X+
	m_vecCubeTextureIndices[0] = { 1, 5, 6 };
	m_vecCubeTextureIndices[1] = { 1, 6, 2 };

	// X-
	m_vecCubeTextureIndices[2] = { 4, 0, 3 };
	m_vecCubeTextureIndices[3] = { 4, 3, 7 };

	// Y+
	m_vecCubeTextureIndices[4] = { 4, 5, 1 };
	m_vecCubeTextureIndices[5] = { 4, 1, 0 };

	// Y-
	m_vecCubeTextureIndices[6] = { 3, 2, 6 };
	m_vecCubeTextureIndices[7] = { 3, 6, 7 };

	// Z+
	m_vecCubeTextureIndices[8] = { 7, 6, 5 };
	m_vecCubeTextureIndices[9] = { 7, 5, 4 };

	// Z-
	m_vecCubeTextureIndices[10] = { 0, 1, 2 };
	m_vecCubeTextureIndices[11] = { 0, 2, 3 };

	m_vecVertexWorldPos.reserve(8);
	m_vecVertexWorldPos.resize(8);

	m_vecVertexIndices.reserve(12);

	CMeshComponent::Initialize();
}

void CSkyboxComponent::BeginPlay()
{
	CMeshComponent::BeginPlay();
}

int32 CSkyboxComponent::Update(const float& _fDeltaSeconds)
{
	return CMeshComponent::Update(_fDeltaSeconds);
}

int32 CSkyboxComponent::LateUpdate(const float& _fDeltaSeconds)
{
	return CMeshComponent::LateUpdate(_fDeltaSeconds);
}

void CSkyboxComponent::Render()
{
	CMeshComponent::Render();

	// 월드 행렬(World matrix, W)을 설정합니다.
	m_pD3DDevice9->SetTransform(D3DTS_WORLD, &m_matWorld);

	m_pD3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// 스트림 소스를 버텍스 버퍼에 연결하여 렌더링 파이프라인에 보냅니다.
	m_pD3DDevice9->SetStreamSource(0, m_pVertexBuffer, 0, m_iVertexSize);

	// 버텍스 포맷을 설정합니다.
	m_pD3DDevice9->SetFVF(m_iVertexFormat);

	// 인덱스 버퍼를 설정합니다.
	m_pD3DDevice9->SetIndices(m_pIndexBuffer);

	// 텍스처를 설정합니다.
	m_pD3DDevice9->SetTexture(0, m_vecD3DTextures[m_iFileIndex]);

	// 인덱스 정보를 활용해 기본 도형을 그립니다.
	m_pD3DDevice9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_iNumVertices, 0, m_iNumTriangles);

	m_pD3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void CSkyboxComponent::EndPlay()
{
	CMeshComponent::EndPlay();
}

void CSkyboxComponent::Release()
{
	CMeshComponent::Release();
}

void CSkyboxComponent::SetSkyboxInfo(const std::wstring& _wstrTextureFileName, uint32 _iBeginIndex, uint32 _iEndIndex)
{
	m_wstrTextureFileName = _wstrTextureFileName;
	m_iFileBeginIndex = _iBeginIndex;
	m_iFileEndIndex = _iEndIndex;
}
