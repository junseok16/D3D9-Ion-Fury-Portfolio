#pragma once
#include "SceneComponent.h"

class CCameraComponent : public CSceneComponent
{
public:
	explicit CCameraComponent() = default;
	virtual ~CCameraComponent() = default;

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
	Getter/Setter
********************/
public:
	void SetProjectionType(EProjectionType _eProjectionType) { m_eProjectionType = _eProjectionType; }
	EProjectionType GetProjectionType() const { return m_eProjectionType; }

	void SetActive(bool bActive) { m_bActive = m_bActive; }
	bool GetActive() const { return m_bActive; }

	void SetFieldOfView(float _fFoV) { m_fFoV = _fFoV; }
	float GetFieldOfView() const { return m_fFoV; }
	
	void SetAspectRatio(float _fAspectRatio) { m_fAspectRatio = _fAspectRatio; }
	float GetAspectRatio() const { return m_fAspectRatio; }

	void SetNearPlane(float _fNearPlane) { m_fNearPlane = _fNearPlane; }
	float GetNearPlane() const { return m_fNearPlane; }

	void SetFarPlane(float _fFarPlane) { m_fFarPlane = _fFarPlane; }
	float GetFarPlane() const { return m_fFarPlane; }

	// 원근 뷰 행렬
	const FMatrix& GetPersViewMatrix() const { return m_matPersView; }
	void SetPersViewMatrix(const FMatrix& _matPersView) { m_matPersView = _matPersView; }

	// 원근 투영 행렬
	const FMatrix& GetPersProjMatrix() const { return m_matPersProj; }
	void SetPersProjMatrix(const FMatrix& _matPersProj) { m_matPersProj = _matPersProj; }

	// 직교 뷰 행렬
	const FMatrix& GetOrthoViewMatrix() const { return m_matOrthoView; }
	void SetOrthoViewMatrix(const FMatrix& _matOrthoView) { m_matOrthoView = _matOrthoView; }

	// 직교 투영 행렬
	const FMatrix& GetOrthoProjMatrix() const { return m_matOrthoProj; }
	void SetOrthoProjMatrix(const FMatrix& _matOrthoProj) { m_matOrthoProj = _matOrthoProj; }

	const FVector3& GetCameraEye() { return m_tEye; }

	const FVector3& GetCameraAt() { return m_tAt; }

	const FVector3& GetCameraUp() { return m_tUp; }

	// 현재 렌더할 카메라를 설정합니다.
	void SetCurRenderCamera();

	// 카메라 무브 활성화
	void SetCameraMove(bool _bIsMove) { m_bIsCameraMove = _bIsMove; }

	void SetCameraMoveRatioX(const float& _fRatioX) { m_fCameraMoveRatioX = _fRatioX; }
	const float& GetCameraMoveRatioX() { return m_fCameraMoveDistanceX; }

	void SetCameraMoveRatioY(const float& _fRatioY) { m_fCameraMoveRatioY = _fRatioY; }
	const float& GetCameraMoveRatioY() { return m_fCameraMoveDistanceY; }

	void SetCameraMoveDistanceX(const float& _fDistanceX) { m_fCameraMoveDistanceX = _fDistanceX; }
	const float& GetCameraMoveDistanceX() { return m_fCameraMoveDistanceX; }

	void SetCameraMoveDistanceY(const float& _fDistanceY) { m_fCameraMoveDistanceY = _fDistanceY; }
	const float& GetCameraMoveDistanceY() { return m_fCameraMoveDistanceY; }

/********************
	Methods
********************/
private:
	void UpdateCameraTransform();

	// 카메라 무브
private:
	void CameraMove(const FVector3& _vDir, const float& _fRatioX, const float& _fRatioY,
					const float& _fDistanceX, const float& _fDistanceY);

/********************
	Data Members
********************/
private:
	// 카메라 시점 타입
	ECameraViewType m_eCameraViewType = ECameraViewType::ENUM_END;

	// 카메라 투영 타입
	EProjectionType m_eProjectionType = EProjectionType::PERSPECTIVE;

	// 카메라 활성화
	bool m_bActive = true;

	// 카메라 무브 활성화
	bool m_bIsCameraMove = false;

	// X축 카메라 무브 빠르기
	float m_fCameraMoveRatioX = 5.0f;

	// Y축 카메라 무브 빠르기
	float m_fCameraMoveRatioY = 5.0f;

	// X축 카메라 무브 범위
	float m_fCameraMoveDistanceX = 1.0f;

	// Y축 카메라 무브 범위
	float m_fCameraMoveDistanceY = 1.0f;

	// (임시) 카메라 이동 방향 전환
	bool m_bIsYFliped = false;
	bool m_bIsXFliped = false;

	// (임시) 카메라 이동 방향
	FVector3 m_vCameraMoveDir = { 0.0f, 0.0f, 0.0f };

	// (임시) 카메라 이동 거리
	FVector3 m_vCameraMoveDistance = { 0.0f, 0.0f, 0.0f };

	// 뷰 행렬, 프로젝션 행렬
	// FMatrix m_matView, m_matProjection;

	// 카메라가 있는 위치
	FVector3 m_tEye{ 0.0f, 0.0f, 0.0f };

	// 카메라가 바라보는 위치
	FVector3 m_tAt{ 0.0f, 0.0f, 1.0f };

	// 카메라의 업 벡터
	FVector3 m_tUp{ 0.0f, 1.0f, 0.0f };

	// 시야각
	float m_fFoV = 60.0f;

	// 종횡비
	float m_fAspectRatio = CFWINCX / CFWINCY;

	// 근평면까지 거리
	float m_fNearPlane = 1.0f;

	// 원 평면까지 거리
	float m_fFarPlane = 2000.0f;

	// 원근 뷰 행렬
	FMatrix m_matPersView;

	// 원근 투영 행렬
	FMatrix m_matPersProj;

	// 직교 뷰 행렬
	FMatrix m_matOrthoView;

	// 직교 투영 행렬
	FMatrix m_matOrthoProj;
};
