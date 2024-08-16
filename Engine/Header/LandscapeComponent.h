#pragma once
#include "PrimitiveComponent.h"

class CLandscapeComponent : public CPrimitiveComponent
{
public:
	explicit CLandscapeComponent() = default;
	virtual ~CLandscapeComponent() = default;

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
	//void CreateHeightmap();

	virtual void CreateVertices() override;

	virtual void CreateIndices() override;

/*******************
	Getter/Setter
*******************/
public:
	void SetLandscapeInfo
	(
		uint32 _iNumCellsInRow,
		uint32 _iNumCellsInColumn,
		uint32 _iCellLength,
		const std::wstring _wstrTextureFileName,
		int32 _iFileIndex,
		const std::wstring _wstrTextureFileExt,
		const std::wstring _wstrHeightmapFileName
	);

public:
	void SetHeightmapFileName(const std::wstring& _wstrHightmapFileName) { m_wstrHeightmapFileName = _wstrHightmapFileName; }
	const std::wstring& GetHeightmapFileName() const { return m_wstrHeightmapFileName; }

	void SetNumCellsInRow(uint32 _iNumCellsInRow) { m_iNumCellsInRow = _iNumCellsInRow; }
	uint32 GetNumCellsInRow() const { return m_iNumCellsInRow; }

	void SetNumCellsInColumn(uint32 _iNumCellsInColumn) { m_iNumCellsInColumn = _iNumCellsInColumn; }
	uint32 GetNumCellsInColumn() const { return m_iNumCellsInColumn; }

	void SetCellLength(int32 _iCellLength) { m_iCellLength = _iCellLength; }
	int32 GetCellLength() const { return m_iCellLength; }

	void SetHeightScale(float _fHeightScale) { m_fHeightScale = _fHeightScale; }
	float GetHeightScale() const { return m_fHeightScale; }

	//float GetHeight(float _fX, float _fZ);
	//float GetHeightmapEntry(int32 _iRow, int32 _iColumn);

protected:
	// IDirect3DTexture9* m_pD3DHeightmap = nullptr;

private:
	std::vector<float> m_vecHeights;

	// ���̸� ���� �̸�
	std::wstring m_wstrHeightmapFileName = L"";

	// ��� ���� ����
	uint32 m_iNumCellsInRow = 0;

	// ���� ���� ����
	uint32 m_iNumCellsInColumn = 0;

	// ��� ���ؽ��� ����
	uint32 m_iNumVerticesInRow = 0;

	// ���� ���ؽ��� ����
	uint32 m_iNumVerticesInColumn = 0;

	// ���� ���������� ���� ����
	float m_fLandscapeWidth = 0.0f;

	// ���� ���������� ���� ����
	float m_fLandscapeDepth = 0.0f;

	// �� ũ��
	int32 m_iCellLength = 0;

	// ����
	float m_fHeightScale = 1.0f;
};

