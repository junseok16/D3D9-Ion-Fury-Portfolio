#pragma once

class CEditorCamera final
{
public:
	explicit CEditorCamera() = default;
	virtual ~CEditorCamera() = default;

/********************
	Framework
********************/
public:
	void Initialize();
	int32 Update(const float& _fDeltaSeconds);
	void Release();

/********************
	Getter/Setter
********************/
public:
	void SetFieldOfView(float _fFoV) { m_fFoV = _fFoV; }
	float GetFieldOfView() const { return m_fFoV; }

	void SetAspectRatio(float _fAspectRatio) { m_fAspectRatio = _fAspectRatio; }
	float GetAspectRatio() const { return m_fAspectRatio; }

	void SetNearPlane(float _fNearPlane) { m_fNearPlane = _fNearPlane; }
	float GetNearPlane() const { return m_fNearPlane; }

	void SetFarPlane(float _fFarPlane) { m_fFarPlane = _fFarPlane; }
	float GetFarPlane() const { return m_fFarPlane; }

/********************
	Methods
********************/
public:
	void FocusOnViewport();
	void UpdateKeyInput(float _fDeltaSeconds);
	void UpdateMouseInput();
	void UpdateViewMatrix();
	void UpdateProjectionMatrix();

/********************
	Data Members
********************/
private:
	// 뷰 행렬, 프로젝션 행렬
	FMatrix m_matView, m_matProjection;

	// 카메라가 있는 위치
	FVector3 m_vEye{ 0.0f, 0.0f, -10.0f };

	// 카메라가 바라보는 위치
	FVector3 m_vAt{ 0.0f, 0.0f, 1.0f };

	// 카메라의 업 벡터
	FVector3 m_vUp{ 0.0f, 1.0f, 0.0f };

	// 시야각
	float m_fFoV = 60.0f;

	// 종횡비
	float m_fAspectRatio = CFWINCX / CFWINCY;

	// 근평면까지 거리
	float m_fNearPlane = 1.0f;

	// 원 평면까지 거리
	float m_fFarPlane = 1000.0f;

	// 카메라 이동 속도
	float m_fSpeed = 30.0f;
};

