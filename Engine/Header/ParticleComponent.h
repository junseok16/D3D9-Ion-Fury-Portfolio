#pragma once
#include "PrimitiveComponent.h"

/**
 * @brief ��ƼŬ ������Ʈ Ŭ�����Դϴ�.
 * @author �ڵ���
 * @date 2023-11-03
 */

class CParticleComponent : public CPrimitiveComponent
{
public:
	explicit CParticleComponent() = default;
	virtual ~CParticleComponent() = default;

public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;

	virtual void PreRender();
	virtual void Render() override;
	virtual void PostRender();

	virtual void EndPlay() override;
	virtual void Release() override;

/********************
	Methods
********************/

public:
	virtual void CreateVertexBuffer();

	// ��� �޾����� ������ �ʴ� �Լ��̱⿡ �������̵��Ͽ� ���Լ��� ó���մϴ�.
	virtual void CreateIndexBuffer() {};

	virtual void CreateVertices() {};

	virtual void CreateIndices() {};

	// ��ƼŬ�� �޽� ������ �����մϴ�.
	void SetParticleMeshInfo(const std::wstring& _wstrTextureFileName, uint32 _iBeginIndex = 0, uint32 _iEndIndex = 0);

	// ��ƼŬ�� ���� ������ �����մϴ�.
	void SetParticleInfo(EParticleType _eParticleType, int32 _iParticleNum);

	// ���ؽ� ���۸� �о���̱� ���� ������ �����մϴ�.
	void SetVertexBufferOffsetInfo(uint32 _lVbSize, uint32 _lVbOffset, uint32 _lVbBatchSize);

	// �� ������ ��ƼŬ ������ ������Ʈ�մϴ�.
	virtual void UpdateParticle(const float& _fDeltaSeconds);

public:
	// ����Ʈ �� ��� ��ƼŬ�� �����մϴ�.
	virtual void Reset();

	// ��ƼŬ�� ����Ʈ�� �߰��մϴ�.
	virtual void AddParticle();

	// ParticleAttribute�� ������� ��ƼŬ�� �����մϴ�.
	virtual void ResetParticles(ParticleAttribute* _tParticleAttribute);

	// ������Ÿ���� ���� ��ƼŬ�� ����Ʈ���� �����մϴ�.
	virtual void RemoveDeadParticles();

/*******************
	Getter/Setter
*******************/
public:
	// ���� ��ƼŬ ����Ʈ
	std::list<ParticleAttribute>& GetParticleList() { return m_lstParticles; }

	// ��ƼŬ Ÿ��
	void SetParticleType(EParticleType _eParticleType) { m_eParticleType = _eParticleType; }
	EParticleType GetParticleType() { return m_eParticleType; }

	// ��ƼŬ ���� ��ġ
	void SetParticleOrigin(const FVector3& _vOrigin) { m_vOrigin = _vOrigin; }
	const FVector3& GetParticleOrigin() { return m_vOrigin; }

	// �� ��ƼŬ ��
	void SetParticleNum(const uint32& _iParticleNum) { m_iParticleNum = _iParticleNum; }
	const uint32& GetParticleNum() { return m_iParticleNum; }

	// �ʴ� ��ƼŬ ��
	void SetEmitRate(const float& _fEmitRate) { m_fEmitRate = _fEmitRate; }
	const float& GetEmitRate() { return m_fEmitRate; }

	// ��ƼŬ ũ��
	void SetParticleSize(const float& _fParticleSize) { m_fParticleSize = _fParticleSize; }
	const float& GetParticleSize() { return m_fParticleSize; }

	// ��ƼŬ ������Ÿ��
	void SetParticleLifeTime(const float& _fParticleLifeTime) { m_fParticleLifeTime = _fParticleLifeTime; }
	const float& GetParticleLifeTime() { return m_fParticleLifeTime; }

	// ��ƼŬ ���� �ӵ�
	void SetParticleSpeed(const float& _fParticleSpeed) { m_fParticleSpeed = _fParticleSpeed; }
	const float& GetParticleSpeed() { return m_fParticleSpeed; }

	// ��ƼŬ ���� ���ӵ�
	void SetParticleAcceleration(const float& _fParticleAccelertaion) { m_fParticleAcceleration = _fParticleAccelertaion; }
	const float& GetParticleAcceleration() { return m_fParticleAcceleration; }

	// ��ƼŬ ���� ����(�ð� �ƴ� ������)
	void SetParticleInterval(const float& _fParticleInterval) { m_fParticleInterval = _fParticleInterval; }
	const float& GetParticleInterval() { return m_fParticleInterval; }

	// ��ƼŬ x, z ���� ����
	void SetParticleSpreadDegreeXZ(const float& _fParticleSpreadDegreeXZ) { m_fParticleSpreadDegreeXZ = _fParticleSpreadDegreeXZ; }
	const float& GetParticleSpreadDegreeXZ() { return m_fParticleSpreadDegreeXZ; }

	// ��ƼŬ y ���� ����
	void SetParticleSpreadDegreeY(const float& _fParticleSpreadDegreeY) { m_fParticleSpreadDegreeY = _fParticleSpreadDegreeY; }
	const float& GetParticleSpreadDegreeY() { return m_fParticleSpreadDegreeY; }

	// ��ƼŬ ����
	void SetParticleColor(D3DXCOLOR _vColor) { m_tColor = _vColor; }
	const D3DXCOLOR GetParticleColor() { return m_tColor; }

	// ������ ��ƼŬ�� ���� ����
	void SetStraightParticleDir(const FVector3& _vStraightDir) { m_vStraightDir = _vStraightDir; }
	const FVector3& GetStraightParticleDir() { return m_vStraightDir; }

	// ��ƼŬ ���� �ð�(0 ~ �Ű����� ������ ������ �ð����� �����˴ϴ�.)
	void SetParticleCreateTime(const float& _fParticleCreateTime) { m_fParticleCreateTime = _fParticleCreateTime; }
	const float& GetParticleCreateTime() { return m_fParticleCreateTime; }

	// ��ƼŬ ���� ����
	void SetIsRemove(bool _bIsRemove) { m_bIsRemove = _bIsRemove; }
	bool GetIsRemove() { return m_bIsRemove; }

	// ��ƼŬ ���� ���� ����
	void SetIsRandom(bool _bIsRandom) { m_bIsRandom = _bIsRandom; }
	bool GetIsRandom() { return m_bIsRandom; }

	// �ִ� ��ƼŬ ��
	void SetMaxParticles(const int32& _iMaxParticles) { m_iMaxParticles = _iMaxParticles; }
	const int32& GetMaxParticles() { return m_iMaxParticles; }

	// ��ƼŬ Ȱ��ȭ
	void SetIsActive(bool _bIsActive) { m_bIsActive = _bIsActive; }
	bool GetIsActive() { return m_bIsActive; }

#pragma region ��� �Լ�

// ���� float�� �������ִ� �Լ�
	float GetRandomFloat(float _fLowBound, float _fHighBound);

	// ���� float�� ���� FVector3�� �������ִ� �Լ�
	void GetRandomVector(FVector3* _vOut, FVector3* _vMin, FVector3* _vMax);

	// float �ڷ����� DWORD �ڷ������� �ٲ��ִ� �Լ�
	DWORD FtoDW(const float& _fValue) { return *((DWORD*)&_fValue); }

	// D3DXCOLOR -> D3DCOLOR
	D3DCOLOR ConvertD3DXColorToD3DColor(const D3DXCOLOR& d3dxColor);

#pragma endregion ��� �Լ�

/********************
	Data Members
********************/
protected:
#pragma region Default

	// ��ƼŬ �߻� ��õ�� ��ġ -> ���͸� ���󰡵��� �Ǿ��ֽ��ϴ�.
	FVector3 m_vOrigin = { 0.0f, 0.0f, 0.0f };

	// ��ƼŬ���� ����Ʈ
	std::list<ParticleAttribute> m_lstParticles;

	// ��ƼŬ Ÿ��, ���Ƿ� �����������ϴ�.
	EParticleType m_eParticleType = EParticleType::ENUM_END;

	// �ٿ�� �ڽ� ũ���� ���� ������ ��� ��ƼŬ�� ���µǰų� �����˴ϴ�.
	FVector3 m_vBoundingBox = { 1.0f, 1.0f, 1.0f };

	// �� ��ƼŬ ��
	int32 m_iParticleNum = 100;

	// �ʴ� ��ƼŬ ��
	float m_fEmitRate = 30.0f;

#pragma endregion Default

#pragma region Attribute

	// ��ƼŬ ũ��
	float m_fParticleSize = 1.0f;

	// ��ƼŬ ������Ÿ��
	float m_fParticleLifeTime = 2.0f;

	// ��ƼŬ ���� �ӵ�
	float m_fParticleSpeed = 5.0;

	// ��ƼŬ ���� ���ӵ�
	float m_fParticleAcceleration = 1.0f;

	// ��ƼŬ ����(�ð� �ƴ� ������)
	float m_fParticleInterval = 1.0f;

	// ��ƼŬ x,z ���� ����
	float m_fParticleSpreadDegreeXZ = 1.0f;

	// ��ƼŬ y ���� ����
	float m_fParticleSpreadDegreeY = 1.0f;

	// ��ƼŬ ����(�⺻�� = ���)
	D3DXCOLOR m_tColor = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );

	// ������ ��ƼŬ�� ���� ����
	FVector3 m_vStraightDir = { 0.0f, 0.0f, 0.0f };

	// ��ƼŬ ���� �ð�
	float m_fParticleCreateTime = 0.0f;

	// ��ƼŬ ���� ���� ����
	bool m_bIsRandom = true;

	// ��ƼŬ ���� ����
	bool m_bIsRemove = false;

	// ��ƼŬ Ȱ��ȭ
	bool m_bIsActive = false;

#pragma endregion Attribute

#pragma region BufferSetting

	// �ִ� ��ƼŬ ��
	int32 m_iMaxParticles = 4092;

	// ���ؽ� ���۰� ������ �� �ִ� ��ƼŬ�� ��
	DWORD m_lVbSize = 4092;

	// ���ؽ� ���۸� �о���� �� ����� ������
	DWORD m_lVbOffset = 0;

	// �� �ܰ迡 �о���� ������ ũ��
	DWORD m_lVbBatchSize = 128;

#pragma endregion BufferSetting
};
