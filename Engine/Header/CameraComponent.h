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

	// ���� �� ���
	const FMatrix& GetPersViewMatrix() const { return m_matPersView; }
	void SetPersViewMatrix(const FMatrix& _matPersView) { m_matPersView = _matPersView; }

	// ���� ���� ���
	const FMatrix& GetPersProjMatrix() const { return m_matPersProj; }
	void SetPersProjMatrix(const FMatrix& _matPersProj) { m_matPersProj = _matPersProj; }

	// ���� �� ���
	const FMatrix& GetOrthoViewMatrix() const { return m_matOrthoView; }
	void SetOrthoViewMatrix(const FMatrix& _matOrthoView) { m_matOrthoView = _matOrthoView; }

	// ���� ���� ���
	const FMatrix& GetOrthoProjMatrix() const { return m_matOrthoProj; }
	void SetOrthoProjMatrix(const FMatrix& _matOrthoProj) { m_matOrthoProj = _matOrthoProj; }

	const FVector3& GetCameraEye() { return m_tEye; }

	const FVector3& GetCameraAt() { return m_tAt; }

	const FVector3& GetCameraUp() { return m_tUp; }

	// ���� ������ ī�޶� �����մϴ�.
	void SetCurRenderCamera();

	// ī�޶� ���� Ȱ��ȭ
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

	// ī�޶� ����
private:
	void CameraMove(const FVector3& _vDir, const float& _fRatioX, const float& _fRatioY,
					const float& _fDistanceX, const float& _fDistanceY);

/********************
	Data Members
********************/
private:
	// ī�޶� ���� Ÿ��
	ECameraViewType m_eCameraViewType = ECameraViewType::ENUM_END;

	// ī�޶� ���� Ÿ��
	EProjectionType m_eProjectionType = EProjectionType::PERSPECTIVE;

	// ī�޶� Ȱ��ȭ
	bool m_bActive = true;

	// ī�޶� ���� Ȱ��ȭ
	bool m_bIsCameraMove = false;

	// X�� ī�޶� ���� ������
	float m_fCameraMoveRatioX = 5.0f;

	// Y�� ī�޶� ���� ������
	float m_fCameraMoveRatioY = 5.0f;

	// X�� ī�޶� ���� ����
	float m_fCameraMoveDistanceX = 1.0f;

	// Y�� ī�޶� ���� ����
	float m_fCameraMoveDistanceY = 1.0f;

	// (�ӽ�) ī�޶� �̵� ���� ��ȯ
	bool m_bIsYFliped = false;
	bool m_bIsXFliped = false;

	// (�ӽ�) ī�޶� �̵� ����
	FVector3 m_vCameraMoveDir = { 0.0f, 0.0f, 0.0f };

	// (�ӽ�) ī�޶� �̵� �Ÿ�
	FVector3 m_vCameraMoveDistance = { 0.0f, 0.0f, 0.0f };

	// �� ���, �������� ���
	// FMatrix m_matView, m_matProjection;

	// ī�޶� �ִ� ��ġ
	FVector3 m_tEye{ 0.0f, 0.0f, 0.0f };

	// ī�޶� �ٶ󺸴� ��ġ
	FVector3 m_tAt{ 0.0f, 0.0f, 1.0f };

	// ī�޶��� �� ����
	FVector3 m_tUp{ 0.0f, 1.0f, 0.0f };

	// �þ߰�
	float m_fFoV = 60.0f;

	// ��Ⱦ��
	float m_fAspectRatio = CFWINCX / CFWINCY;

	// �������� �Ÿ�
	float m_fNearPlane = 1.0f;

	// �� ������ �Ÿ�
	float m_fFarPlane = 2000.0f;

	// ���� �� ���
	FMatrix m_matPersView;

	// ���� ���� ���
	FMatrix m_matPersProj;

	// ���� �� ���
	FMatrix m_matOrthoView;

	// ���� ���� ���
	FMatrix m_matOrthoProj;
};
