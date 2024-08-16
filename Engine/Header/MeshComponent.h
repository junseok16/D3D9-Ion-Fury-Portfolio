#pragma once
#include "PrimitiveComponent.h"

class CMeshComponent : public CPrimitiveComponent
{
public:
	explicit CMeshComponent() = default;
	virtual ~CMeshComponent() = default;

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
private:
	virtual void CreateVertices() override;

	virtual void CreateIndices() override;

public:
	void ReverseTextureUV();

	void SetTextureUV(const float& _fU, const float& _fV);

/*******************
	Getter/Setter
*******************/
public:
	void SetVertices(const std::vector<TextureVertex>& _vecTextureVertices) { m_vecTextureVertices = _vecTextureVertices; }
	
	void SetIndices(const std::vector<TextureIndex>& _vecTextureIndices) { m_vecTextureIndices = _vecTextureIndices; }

/********************
	Data Members
********************/
protected:
	// �Ϲ� �ؽ�ó�� ���ؽ� ��ǥ
	std::vector<TextureVertex> m_vecTextureVertices;

	// �Ϲ� �ؽ�ó�� �ε��� ����
	std::vector<TextureIndex> m_vecTextureIndices;

	// ť�� �ؽ�ó�� ���ؽ� ��ǥ
	std::vector<CubeTextureVertex> m_vecCubeTextureVertices;

	// ť�� �ؽ�ó�� �ε��� ����
	std::vector<CubeTextureIndex> m_vecCubeTextureIndices;

protected:
	bool m_bAlphaBlend = false;

	bool m_bAlphaTest = false;

	bool m_bAlphaSort = false;
};

