#pragma once
#include "PrimitiveComponent.h"

/**
 * @brief 파티클 컴포넌트 클래스입니다.
 * @author 박동연
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

	// 상속 받았지만 쓰이지 않는 함수이기에 오버라이딩하여 빈함수로 처리합니다.
	virtual void CreateIndexBuffer() {};

	virtual void CreateVertices() {};

	virtual void CreateIndices() {};

	// 파티클의 메쉬 정보를 설정합니다.
	void SetParticleMeshInfo(const std::wstring& _wstrTextureFileName, uint32 _iBeginIndex = 0, uint32 _iEndIndex = 0);

	// 파티클의 생성 정보를 설정합니다.
	void SetParticleInfo(EParticleType _eParticleType, int32 _iParticleNum);

	// 버텍스 버퍼를 읽어들이기 위한 단위를 설정합니다.
	void SetVertexBufferOffsetInfo(uint32 _lVbSize, uint32 _lVbOffset, uint32 _lVbBatchSize);

	// 매 프레임 파티클 정보를 업데이트합니다.
	virtual void UpdateParticle(const float& _fDeltaSeconds);

public:
	// 리스트 내 모든 파티클을 리셋합니다.
	virtual void Reset();

	// 파티클을 리스트에 추가합니다.
	virtual void AddParticle();

	// ParticleAttribute의 정보대로 파티클을 리셋합니다.
	virtual void ResetParticles(ParticleAttribute* _tParticleAttribute);

	// 라이프타임이 끝난 파티클을 리스트에서 삭제합니다.
	virtual void RemoveDeadParticles();

/*******************
	Getter/Setter
*******************/
public:
	// 현재 파티클 리스트
	std::list<ParticleAttribute>& GetParticleList() { return m_lstParticles; }

	// 파티클 타입
	void SetParticleType(EParticleType _eParticleType) { m_eParticleType = _eParticleType; }
	EParticleType GetParticleType() { return m_eParticleType; }

	// 파티클 생성 위치
	void SetParticleOrigin(const FVector3& _vOrigin) { m_vOrigin = _vOrigin; }
	const FVector3& GetParticleOrigin() { return m_vOrigin; }

	// 총 파티클 수
	void SetParticleNum(const uint32& _iParticleNum) { m_iParticleNum = _iParticleNum; }
	const uint32& GetParticleNum() { return m_iParticleNum; }

	// 초당 파티클 수
	void SetEmitRate(const float& _fEmitRate) { m_fEmitRate = _fEmitRate; }
	const float& GetEmitRate() { return m_fEmitRate; }

	// 파티클 크기
	void SetParticleSize(const float& _fParticleSize) { m_fParticleSize = _fParticleSize; }
	const float& GetParticleSize() { return m_fParticleSize; }

	// 파티클 라이프타임
	void SetParticleLifeTime(const float& _fParticleLifeTime) { m_fParticleLifeTime = _fParticleLifeTime; }
	const float& GetParticleLifeTime() { return m_fParticleLifeTime; }

	// 파티클 진행 속도
	void SetParticleSpeed(const float& _fParticleSpeed) { m_fParticleSpeed = _fParticleSpeed; }
	const float& GetParticleSpeed() { return m_fParticleSpeed; }

	// 파티클 진행 가속도
	void SetParticleAcceleration(const float& _fParticleAccelertaion) { m_fParticleAcceleration = _fParticleAccelertaion; }
	const float& GetParticleAcceleration() { return m_fParticleAcceleration; }

	// 파티클 생성 간격(시간 아님 공간임)
	void SetParticleInterval(const float& _fParticleInterval) { m_fParticleInterval = _fParticleInterval; }
	const float& GetParticleInterval() { return m_fParticleInterval; }

	// 파티클 x, z 퍼짐 정도
	void SetParticleSpreadDegreeXZ(const float& _fParticleSpreadDegreeXZ) { m_fParticleSpreadDegreeXZ = _fParticleSpreadDegreeXZ; }
	const float& GetParticleSpreadDegreeXZ() { return m_fParticleSpreadDegreeXZ; }

	// 파티클 y 퍼짐 정도
	void SetParticleSpreadDegreeY(const float& _fParticleSpreadDegreeY) { m_fParticleSpreadDegreeY = _fParticleSpreadDegreeY; }
	const float& GetParticleSpreadDegreeY() { return m_fParticleSpreadDegreeY; }

	// 파티클 색상
	void SetParticleColor(D3DXCOLOR _vColor) { m_tColor = _vColor; }
	const D3DXCOLOR GetParticleColor() { return m_tColor; }

	// 직선형 파티클의 방향 벡터
	void SetStraightParticleDir(const FVector3& _vStraightDir) { m_vStraightDir = _vStraightDir; }
	const FVector3& GetStraightParticleDir() { return m_vStraightDir; }

	// 파티클 생성 시간(0 ~ 매개변수 까지의 랜덤한 시간에서 생성됩니다.)
	void SetParticleCreateTime(const float& _fParticleCreateTime) { m_fParticleCreateTime = _fParticleCreateTime; }
	const float& GetParticleCreateTime() { return m_fParticleCreateTime; }

	// 파티클 삭제 여부
	void SetIsRemove(bool _bIsRemove) { m_bIsRemove = _bIsRemove; }
	bool GetIsRemove() { return m_bIsRemove; }

	// 파티클 랜덤 생성 여부
	void SetIsRandom(bool _bIsRandom) { m_bIsRandom = _bIsRandom; }
	bool GetIsRandom() { return m_bIsRandom; }

	// 최대 파티클 수
	void SetMaxParticles(const int32& _iMaxParticles) { m_iMaxParticles = _iMaxParticles; }
	const int32& GetMaxParticles() { return m_iMaxParticles; }

	// 파티클 활성화
	void SetIsActive(bool _bIsActive) { m_bIsActive = _bIsActive; }
	bool GetIsActive() { return m_bIsActive; }

#pragma region 계산 함수

// 랜덤 float을 생성해주는 함수
	float GetRandomFloat(float _fLowBound, float _fHighBound);

	// 랜덤 float을 가진 FVector3를 생성해주는 함수
	void GetRandomVector(FVector3* _vOut, FVector3* _vMin, FVector3* _vMax);

	// float 자료형을 DWORD 자료형으로 바꿔주는 함수
	DWORD FtoDW(const float& _fValue) { return *((DWORD*)&_fValue); }

	// D3DXCOLOR -> D3DCOLOR
	D3DCOLOR ConvertD3DXColorToD3DColor(const D3DXCOLOR& d3dxColor);

#pragma endregion 계산 함수

/********************
	Data Members
********************/
protected:
#pragma region Default

	// 파티클 발생 원천의 위치 -> 액터를 따라가도록 되어있습니다.
	FVector3 m_vOrigin = { 0.0f, 0.0f, 0.0f };

	// 파티클들의 리스트
	std::list<ParticleAttribute> m_lstParticles;

	// 파티클 타입, 임의로 나눠보앗읍니다.
	EParticleType m_eParticleType = EParticleType::ENUM_END;

	// 바운딩 박스 크기의 범위 밖으로 벗어난 파티클은 리셋되거나 삭제됩니다.
	FVector3 m_vBoundingBox = { 1.0f, 1.0f, 1.0f };

	// 총 파티클 수
	int32 m_iParticleNum = 100;

	// 초당 파티클 수
	float m_fEmitRate = 30.0f;

#pragma endregion Default

#pragma region Attribute

	// 파티클 크기
	float m_fParticleSize = 1.0f;

	// 파티클 라이프타임
	float m_fParticleLifeTime = 2.0f;

	// 파티클 진행 속도
	float m_fParticleSpeed = 5.0;

	// 파티클 진행 가속도
	float m_fParticleAcceleration = 1.0f;

	// 파티클 간격(시간 아님 공간임)
	float m_fParticleInterval = 1.0f;

	// 파티클 x,z 퍼짐 정도
	float m_fParticleSpreadDegreeXZ = 1.0f;

	// 파티클 y 퍼짐 정도
	float m_fParticleSpreadDegreeY = 1.0f;

	// 파티클 색상(기본값 = 흰색)
	D3DXCOLOR m_tColor = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );

	// 직선형 파티클의 방향 벡터
	FVector3 m_vStraightDir = { 0.0f, 0.0f, 0.0f };

	// 파티클 생성 시간
	float m_fParticleCreateTime = 0.0f;

	// 파티클 랜덤 생성 여부
	bool m_bIsRandom = true;

	// 파티클 삭제 여부
	bool m_bIsRemove = false;

	// 파티클 활성화
	bool m_bIsActive = false;

#pragma endregion Attribute

#pragma region BufferSetting

	// 최대 파티클 수
	int32 m_iMaxParticles = 4092;

	// 버텍스 버퍼가 보관할 수 있는 파티클의 수
	DWORD m_lVbSize = 4092;

	// 버텍스 버퍼를 읽어들일 때 사용할 오프셋
	DWORD m_lVbOffset = 0;

	// 한 단계에 읽어들일 버퍼의 크기
	DWORD m_lVbBatchSize = 128;

#pragma endregion BufferSetting
};
