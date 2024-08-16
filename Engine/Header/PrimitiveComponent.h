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
	// 11.03 ��ƼŬ�� �������۵� ����, �޸� Ǯ�� �޶� �������̵��� ���ֱ� ���� virtual�� �����Ͽ���. - ������ -
	virtual void CreateVertexBuffer();

	virtual void CreateIndexBuffer();

	void CreateTexture();

	virtual void CreateVertices() abstract;

	virtual void CreateIndices() abstract;

protected:
	// 10.24 �� ������ �������� ���� ��ǥ�� �����ϱ� ���� �߰� - �ڵ��� -
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

	// 10.24 - �ڵ��� - ���� ���� �浹�� ���� �߰�
	std::vector<FVector3>& GetVecVertexWorldPos() { return m_vecVertexWorldPos; }

	FVector3& GetVertexWorldPos(const int32& _iIndex) { return m_vecVertexWorldPos[_iIndex]; }
	FVector3& GetVertexIndices(const int32& _iIndex) { return m_vecVertexIndices[_iIndex]; }

	// �ӽ��ڵ�
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
	// ������Ƽ�� Ÿ��
	EPrimitiveType m_ePrimitiveType = EPrimitiveType::ENUM_END;

	// �ؽ�ó ���� ��� -> ����� �����Դϴ�.
	std::wstring m_wstrTextureFilePath = L"";

	// �ؽ�ó ���� �̸�
	std::wstring m_wstrTextureFileName = L"";

	// �ؽ�ó ���� Ȯ���� -> ����� �����Դϴ�.
	std::wstring m_wstrTextureFileExt = L"";

	// �ؽ�ó ���� �ε��� -> ����� �����Դϴ�.
	int32 m_iFileIndex = 0;
	
	// �ؽ�ó Ÿ��
	ETextureType m_eTextureType = ETextureType::ENUM_END;

/*******************
	��Ƽ �ؽ�ó
*******************/
	// �ؽ�ó ���� ���� �ε���
	uint32 m_iFileBeginIndex = 0;

	// �ؽ�ó ���� �� �ε���
	uint32 m_iFileEndIndex = 0;

protected:
	// �޸� Ǯ
	D3DPOOL m_tD3DPool = D3DPOOL_MANAGED;

	// ���ؽ��� �� ����
	int32 m_iNumVertices = 0;

	// ���ؽ� ����ü�� ũ��
	int32 m_iVertexSize = 0;

	// ���ؽ� ����
	int32 m_iVertexFormat = 0;

	// �ε��� ����ü�� ũ��
	int32 m_iIndexSize = 0;

	// �ﰢ���� �� ����
	int32 m_iNumTriangles = 0;

	// �ε��� ����
	D3DFORMAT m_tIndexFormat{};

protected:
	std::vector<FVector3> m_vecVertexPos;// �ݶ��̴��� ���� ��ǥ

	// 10.24 - �ڵ��� - ���� �浹�� ���� �߰�
	std::vector<FVector3> m_vecVertexWorldPos;// �� ������ ������ ���� ��ǥ ����

	std::vector<FVector3> m_vecVertexIndices;// �������� �ε��� ������ ������ ����(���۴� �ֹߵǱ� ������ �ϳ� �� ����)

protected:
	float m_fScaleU = 1.0f;

	float m_fScaleV = 1.0f;
};

