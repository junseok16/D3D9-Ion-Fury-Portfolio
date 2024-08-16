#include "pch.h"
#include "LandscapeComponent.h"

#include "DeviceManager.h"
using namespace std;

void CLandscapeComponent::Initialize()
{
	m_pD3DDevice9 = CDeviceManager::GetInstance()->GetDirect3DDevice9();
	m_eTextureType = ETextureType::TEXTURE;

	SetVertexInfo((m_iNumCellsInRow + 1) * (m_iNumCellsInColumn + 1), sizeof(TextureVertex), TEXTURE_FVF);
	SetIndexInfo(m_iNumCellsInRow * m_iNumCellsInColumn * 2, sizeof(TextureIndex), D3DFMT_INDEX32);

	CPrimitiveComponent::Initialize();
	CreateVertices();
	CreateIndices();
}

void CLandscapeComponent::BeginPlay()
{
	CPrimitiveComponent::BeginPlay();
}

int32 CLandscapeComponent::Update(const float& _fDeltaSeconds)
{
	

	return CPrimitiveComponent::Update(_fDeltaSeconds);
}

int32 CLandscapeComponent::LateUpdate(const float& _fDeltaSeconds)
{
	return CPrimitiveComponent::LateUpdate(_fDeltaSeconds);
}

void CLandscapeComponent::Render()
{
	CPrimitiveComponent::Render();

	// 월드 행렬(World matrix, W)을 설정합니다.
	m_pD3DDevice9->SetTransform(D3DTS_WORLD, &m_matWorld);

	// 스트림 소스에 버텍스 버퍼를 설정합니다.
	m_pD3DDevice9->SetStreamSource(0, m_pVertexBuffer, 0, m_iVertexSize);

	// 버텍스 포맷을 설정합니다.
	m_pD3DDevice9->SetFVF(m_iVertexFormat);

	// 인덱스 버퍼를 설정합니다.
	m_pD3DDevice9->SetIndices(m_pIndexBuffer);

	// 텍스처를 설정합니다.
	m_pD3DDevice9->SetTexture(0, m_vecD3DTextures[0]);

	// 인덱스 정보를 활용해 기본 도형을 그립니다. 
	m_pD3DDevice9->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_iNumVertices, 0, m_iNumTriangles);
}

void CLandscapeComponent::EndPlay()
{
	CPrimitiveComponent::EndPlay();
}

void CLandscapeComponent::Release()
{
	CPrimitiveComponent::Release();
}

void CLandscapeComponent::CreateVertices()
{
	// 높이맵
	// D3DSURFACE_DESC ddsd;
	// D3DLOCKED_RECT d3drc;
	// 
	// m_pD3DHeightmap->GetLevelDesc(0, &ddsd);
	// int32 iWidth = ddsd.Width;
	// int32 iHeight = ddsd.Height;
	// 
	// m_pD3DHeightmap->LockRect(0, &d3drc, NULL, D3DLOCK_READONLY);

	// 텍스처
	TextureVertex* pVertex = nullptr;
	m_pVertexBuffer->Lock(0, 0, (void**)&pVertex, 0);

	// m_vecHeights.reserve(iNumVerticesInRow * iNumVerticesInColumn);
	// m_vecHeights.resize(iNumVerticesInRow * iNumVerticesInColumn);

	for (uint32 i = 0; i < m_iNumVerticesInColumn; ++i)
	{
		for (uint32 j = 0; j < m_iNumVerticesInRow; ++j)
		{
			uint32 nth = i * m_iNumVerticesInRow + j;

			// float fY = (*((LPDWORD)d3drc.pBits + nth) & 0x000000ff) / 20.0f;
			// m_vecHeights[nth] = fY;

			pVertex[nth].position = { (float)(j * m_iCellLength) - (m_fLandscapeWidth / 2), /* fY */ 0.0f, -(float)(i * m_iCellLength) + (m_fLandscapeDepth / 2) };
			pVertex[nth].uv = { (float)(j) / m_iNumCellsInRow, (float)(i) / m_iNumCellsInColumn };
		}
	}

	m_pVertexBuffer->Unlock();
	// m_pD3DHeightmap->UnlockRect(0);
}

void CLandscapeComponent::CreateIndices()
{
	TextureIndex* pTextureIndex = nullptr;
	m_pIndexBuffer->Lock(0, 0, (void**)&pTextureIndex, 0);

	int32 iIndexCnt = 0;
	for (uint32 i = 0; i < m_iNumCellsInColumn; ++i)
	{
		for (uint32 j = 0; j < m_iNumCellsInRow; ++j)
		{
			uint32 iBase = i * m_iNumCellsInRow + j;

			// 오른쪽 위 삼각형
			// pTextureIndex[iIndexCnt]._0 = iBase + iNumVerticesPerRow;
			// pTextureIndex[iIndexCnt]._1 = iBase + iNumVerticesPerRow + 1;
			// pTextureIndex[iIndexCnt]._2 = iBase + 1;

			pTextureIndex[iIndexCnt]._0 = iBase;
			pTextureIndex[iIndexCnt]._1 = iBase + 1;
			pTextureIndex[iIndexCnt]._2 = iBase + m_iNumVerticesInRow + 1;
			iIndexCnt++;

			// 왼쪽 아래 삼각형
			// pTextureIndex[iIndexCnt]._0 = iBase + iNumVerticesPerRow;
			// pTextureIndex[iIndexCnt]._1 = iBase + 1;
			// pTextureIndex[iIndexCnt]._2 = iBase;

			pTextureIndex[iIndexCnt]._0 = iBase;
			pTextureIndex[iIndexCnt]._1 = iBase + m_iNumVerticesInRow + 1;
			pTextureIndex[iIndexCnt]._2 = iBase + m_iNumVerticesInRow;

			iIndexCnt++;
		}
	}

	m_pIndexBuffer->Unlock();
}
/*
float CLandscapeComponent::GetHeight(float _fX, float _fZ)
{
	int32 fColumn = static_cast<int32>(::floorf(_fX));
	int32 fRow = static_cast<int32>(::floorf(_fZ));

	float fA = GetHeightmapEntry(fRow + 1, fColumn);
	float fB = GetHeightmapEntry(fRow + 1, fColumn + 1);
	float fC = GetHeightmapEntry(fRow, fColumn);
	float fD = GetHeightmapEntry(fRow, fColumn + 1);

	float fDX = _fX - fColumn;
	float fDZ = _fZ - fRow;

	float fHeight = 0.0f;
	if (fDZ > fDX)  // upper triangle ABC
	{
		float uy = fB - fA; // A->B
		float vy = fC - fA; // A->C
		
		fHeight = fA + lerp(0.0f, uy, fDX) + lerp(0.0f, vy, fDZ);	}
	else
	{
		float uy = fC - fD; // D->C
		float vy = fB - fD; // D->B
		fHeight = fD + lerp(0.0f, uy, 1.0f - fDX) + lerp(0.0f, vy, 1.0f - fDZ);
	}
	return fHeight;
}

float CLandscapeComponent::GetHeightmapEntry(int32 iRow, int32 iColumn)
{
	int32 iNumVerticesPerRow = m_iNumCellsPerRow + 1;
	return m_vecHeights[iRow * iNumVerticesPerRow + iColumn];
}
*/

/*
void CLandscapeComponent::CreateHeightmap()
{
	if (!m_wstrHeightmapFileName.empty())
	{
		ENSURE(D3DXCreateTextureFromFileEx
		(
			m_pD3DDevice9,
			m_wstrHeightmapFileName.c_str(),
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			0,
			D3DFMT_X8B8G8R8,
			D3DPOOL_MANAGED,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			0,
			NULL,
			NULL,
			(LPDIRECT3DTEXTURE9*)&m_pD3DHeightmap)
		);
	}
}
*/


void CLandscapeComponent::SetLandscapeInfo(
	uint32 _iNumCellsInRow,
	uint32 _iNumCellsInColumn,
	uint32 _iCellLength,
	const std::wstring _wstrTextureFileName,
	int32 _iFileIndex,
	const std::wstring _wstrTextureFileExt,
	const std::wstring _wstrHeightmapFileName)
{
	m_iNumCellsInRow = _iNumCellsInRow;
	m_iNumCellsInColumn = _iNumCellsInColumn;
	m_iCellLength = _iCellLength;

	m_wstrTextureFileName = _wstrTextureFileName;
	m_iFileIndex = _iFileIndex;
	m_wstrTextureFileExt = _wstrTextureFileExt;
	m_wstrHeightmapFileName = _wstrHeightmapFileName;

	m_iNumVerticesInRow = _iNumCellsInRow + 1;
	m_iNumVerticesInColumn = _iNumCellsInColumn + 1;
	m_fLandscapeWidth = (float)_iCellLength * _iNumCellsInRow;
	m_fLandscapeDepth = (float)_iCellLength * _iNumCellsInColumn;
}