#pragma once
#include "SceneComponent.h"

class CPrimitiveComponent abstract : public CSceneComponent
{
public:
	explicit CPrimitiveComponent() = default;
	virtual ~CPrimitiveComponent() = default;

/********************
	Framework
********************/
public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void Render() override;
	virtual void EndPlay() override;
	virtual void Release() override;

/********************
	Methods
********************/
public:
	// 11.03 파티클은 동적버퍼도 쓰고, 메모리 풀도 달라서 오버라이딩을 해주기 위해 virtual로 변경하였음. - 동연팍 -
	virtual void CreateVertexBuffer();

	virtual void CreateIndexBuffer();

	void CreateTexture();

	virtual void CreateVertices() abstract;

	virtual void CreateIndices() abstract;

protected:
	// 10.24 매 프레임 정점들의 월드 좌표를 갱신하기 위해 추가 - 박동연 -
	void UpdateVerticesTransform();

/*******************
	Getter/Setter
*******************/
public:
	IDirect3DVertexBuffer9* GetVectexBuffer() const { return m_pVertexBuffer; }

	IDirect3DIndexBuffer9* GetIndexBuffer() const { return m_pIndexBuffer; }

public:
	void SetVertexInfo(int32 _iNumVertices, int32 _iVertexSize, int32 _iVertexFormat);

	void SetIndexInfo(int32 _iNumTriangles, int32 _iIndexSize, D3DFORMAT _tIndexFormat);

	void SetUVInfo(float _fScaleU, float _fScaleV);

	void SetD3DTextures(const std::vector<IDirect3DBaseTexture9*>& _vecD3DTextures) { m_vecD3DTextures = _vecD3DTextures; }

	void SetMaterialInfo(D3DXCOLOR _tDiffuse, D3DXCOLOR _tAmbient, D3DXCOLOR _tSpecular, D3DXCOLOR _tEmissive, float _fPower);

public:
	void SetTextureFileName(const std::wstring& _wstrFileName) { m_wstrTextureFileName = _wstrFileName; }
	const std::wstring& GetTextureFileName() const { return m_wstrTextureFileName; }

	void SetNumVertices(int32 _iNumVertices) { m_iNumVertices = _iNumVertices; }
	int32 GetNumVertices() const { return m_iNumVertices; }

	void SetNumTriangles(int32 _iNumTriangles) { m_iNumTriangles = _iNumTriangles; }
	int32 GetNumTriangles() const { return m_iNumTriangles; }

	void SetVertexSize(int32 _iVertexSize) { m_iVertexSize = _iVertexSize; }
	int32 GetVertexSize() const { return m_iVertexSize; }

	void SetVertexFormat(int32 _iVertexFormat) { m_iVertexFormat = _iVertexFormat; }
	int32 GetVertexFormat() const { return m_iVertexFormat; }

	void SetIndexSize(int32 _iIndexSize) { m_iIndexSize = _iIndexSize; }
	int32 GetIndexSize() const { return m_iIndexSize; }

	void SetIndexFormat(D3DFORMAT _tIndexFormat) { m_tIndexFormat = _tIndexFormat; }
	D3DFORMAT GetIndexFormat() const { return m_tIndexFormat; }

	void SetFileBeginIndex(uint32 _iFileBeginIndex) { m_iFileBeginIndex = _iFileBeginIndex; }
	uint32 GetFileBeginIndex() const { return m_iFileBeginIndex; }

	void SetFileEndIndex(uint32 _iFileEndIndex) { m_iFileEndIndex = _iFileEndIndex; }
	uint32 GetFileEndIndex() const { return m_iFileEndIndex; }

	// 10.24 - 박동연 - 몬스터 광선 충돌을 위해 추가
	std::vector<FVector3>& GetVecVertexWorldPos() { return m_vecVertexWorldPos; }

	FVector3& GetVertexWorldPos(const int32& _iIndex) { return m_vecVertexWorldPos[_iIndex]; }
	FVector3& GetVertexIndices(const int32& _iIndex) { return m_vecVertexIndices[_iIndex]; }

	// 임시코드
	std::vector<IDirect3DBaseTexture9*>& GetVecD3DTextures() { return m_vecD3DTextures; }

/*******************
	Data Members
*******************/
protected:
	IDirect3DDevice9* m_pD3DDevice9 = nullptr;
	
	std::vector<IDirect3DBaseTexture9*> m_vecD3DTextures;
	
	IDirect3DVertexBuffer9* m_pVertexBuffer = nullptr;
	
	IDirect3DIndexBuffer9* m_pIndexBuffer = nullptr;

protected:
	// 프리미티브 타입
	EPrimitiveType m_ePrimitiveType = EPrimitiveType::ENUM_END;

	// 텍스처 파일 경로 -> 폐기할 예정입니다.
	std::wstring m_wstrTextureFilePath = L"";

	// 텍스처 파일 이름
	std::wstring m_wstrTextureFileName = L"";

	// 텍스처 파일 확장자 -> 폐기할 예정입니다.
	std::wstring m_wstrTextureFileExt = L"";

	// 텍스처 파일 인덱스 -> 폐기할 예정입니다.
	int32 m_iFileIndex = 0;
	
	// 텍스처 타입
	ETextureType m_eTextureType = ETextureType::ENUM_END;

/*******************
	멀티 텍스처
*******************/
	// 텍스처 파일 시작 인덱스
	uint32 m_iFileBeginIndex = 0;

	// 텍스처 파일 끝 인덱스
	uint32 m_iFileEndIndex = 0;

protected:
	// 메모리 풀
	D3DPOOL m_tD3DPool = D3DPOOL_MANAGED;

	// 버텍스의 총 개수
	int32 m_iNumVertices = 0;

	// 버텍스 구조체의 크기
	int32 m_iVertexSize = 0;

	// 버텍스 포맷
	int32 m_iVertexFormat = 0;

	// 인덱스 구조체의 크기
	int32 m_iIndexSize = 0;

	// 삼각형의 총 개수
	int32 m_iNumTriangles = 0;

	// 인덱스 포맷
	D3DFORMAT m_tIndexFormat{};

protected:
	std::vector<FVector3> m_vecVertexPos;// 콜라이더의 정점 좌표

	// 10.24 - 박동연 - 광선 충돌을 위해 추가
	std::vector<FVector3> m_vecVertexWorldPos;// 매 프레임 정점들 월드 좌표 갱신

	std::vector<FVector3> m_vecVertexIndices;// 정점들의 인덱스 순서를 영구히 보관(버퍼는 휘발되기 때문에 하나 더 만듦)

protected:
	float m_fScaleU = 1.0f;

	float m_fScaleV = 1.0f;
};

