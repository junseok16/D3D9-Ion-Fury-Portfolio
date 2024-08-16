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
	// �� ���, �������� ���
	FMatrix m_matView, m_matProjection;

	// ī�޶� �ִ� ��ġ
	FVector3 m_vEye{ 0.0f, 0.0f, -10.0f };

	// ī�޶� �ٶ󺸴� ��ġ
	FVector3 m_vAt{ 0.0f, 0.0f, 1.0f };

	// ī�޶��� �� ����
	FVector3 m_vUp{ 0.0f, 1.0f, 0.0f };

	// �þ߰�
	float m_fFoV = 60.0f;

	// ��Ⱦ��
	float m_fAspectRatio = CFWINCX / CFWINCY;

	// �������� �Ÿ�
	float m_fNearPlane = 1.0f;

	// �� ������ �Ÿ�
	float m_fFarPlane = 1000.0f;

	// ī�޶� �̵� �ӵ�
	float m_fSpeed = 30.0f;
};

