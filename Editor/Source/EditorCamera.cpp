#include "pch.h"
#include "EditorCamera.h"
#include "DeviceManager.h"
#include "InputManager.h"
#include "CollisionManager.h"
#include "ColliderComponent.h"
using namespace std;

void CEditorCamera::Initialize()
{
	// �� ��İ� �������� ����� �׵� ��ķ� �ʱ�ȭ�մϴ�.
	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matProjection);
}

int32 CEditorCamera::Update(const float& _fDeltaSeconds)
{
	UpdateViewMatrix();
	UpdateProjectionMatrix();
	FocusOnViewport();
	UpdateKeyInput(_fDeltaSeconds);
	UpdateMouseInput();
	return 0;
}

void CEditorCamera::Release()
{
}

void CEditorCamera::FocusOnViewport()
{
	bool bMouseInCenter = CInputManager::GetInstance()->GetCursorInCenter();

	// Ŀ���� ����� ��װų� �����մϴ�.
	if (CInputManager::GetInstance()->IsKeyDown(DIK_F1))
	{
		bool bMouseInCenter = CInputManager::GetInstance()->GetCursorInCenter();
		CInputManager::GetInstance()->SetCursorInCenter(!bMouseInCenter);
	}
}

void CEditorCamera::UpdateKeyInput(float _fDeltaSeconds)
{
	if (!CInputManager::GetInstance()->GetCursorInCenter()) { return; }

	FMatrix matEditorCamera;
	D3DXMatrixInverse(&matEditorCamera, 0, &m_matView);

	// ������ �̵��մϴ�.
	if (CInputManager::GetInstance()->IsKeyPressed(DIK_W))
	{
		FVector3 vLook;
		memcpy(&vLook, &matEditorCamera.m[2][0], sizeof(FVector3));

		FVector3 vLength = *D3DXVec3Normalize(&vLook, &vLook) * _fDeltaSeconds * m_fSpeed;
		m_vEye += vLength;
		m_vAt += vLength;
	}

	// �ڷ� �̵��մϴ�.
	if (CInputManager::GetInstance()->IsKeyPressed(DIK_S))
	{
		FVector3 vLook;
		memcpy(&vLook, &matEditorCamera.m[2][0], sizeof(FVector3));

		FVector3 vLength = *D3DXVec3Normalize(&vLook, &vLook) * _fDeltaSeconds * m_fSpeed;
		m_vEye -= vLength;
		m_vAt -= vLength;
	}

	// �������� �̵��մϴ�.
	if (CInputManager::GetInstance()->IsKeyPressed(DIK_A))
	{
		FVector3 vRight;
		memcpy(&vRight, &matEditorCamera.m[0][0], sizeof(FVector3));

		FVector3 vLength = *D3DXVec3Normalize(&vRight, &vRight) * _fDeltaSeconds * m_fSpeed;
		m_vEye -= vLength;
		m_vAt -= vLength;
	}

	// ���������� �̵��մϴ�.
	if (CInputManager::GetInstance()->IsKeyPressed(DIK_D))
	{
		FVector3 vRight;
		memcpy(&vRight, &matEditorCamera.m[0][0], sizeof(FVector3));

		FVector3 vLength = *D3DXVec3Normalize(&vRight, &vRight) * _fDeltaSeconds * m_fSpeed;
		m_vEye += vLength;
		m_vAt += vLength;
	}

	// ���� �̵��մϴ�.
	if (CInputManager::GetInstance()->IsKeyPressed(DIK_E))
	{
		FVector3 vUp = *D3DXVec3Normalize(&m_vUp, &m_vUp) * _fDeltaSeconds * m_fSpeed;
		m_vEye += vUp;
		m_vAt += vUp;
	}

	// �Ʒ��� �̵��մϴ�.
	if (CInputManager::GetInstance()->IsKeyPressed(DIK_Q))
	{
		FVector3 vUp = *D3DXVec3Normalize(&m_vUp, &m_vUp) * _fDeltaSeconds * m_fSpeed;
		m_vEye -= vUp;
		m_vAt -= vUp;
	}

	// ���콺 �ӵ��� ������ŵ�ϴ�.
	if (CInputManager::GetInstance()->IsKeyDown(DIK_ADD))
	{
		m_fSpeed += 2.0f;
		if (m_fSpeed >= 100.0f) { m_fSpeed = 100.0f; }
	}

	// ���콺 �ӵ��� ���ҽ�ŵ�ϴ�.
	if (CInputManager::GetInstance()->IsKeyDown(DIK_SUBTRACT))
	{
		m_fSpeed -= 2.0f;
		if (m_fSpeed <= 1.0f) { m_fSpeed = 1.0f; }
	}
}

void CEditorCamera::UpdateMouseInput()
{
	// ī�޶��� ���� ��ǥ�� ���մϴ�.
	FMatrix matEditorCamera;
	D3DXMatrixInverse(&matEditorCamera, 0, &m_matView);

	if (CInputManager::GetInstance()->GetCursorInCenter())
	{ 
		int32 iMouseDeltaY = 0;
		if (iMouseDeltaY = CInputManager::GetInstance()->GetMouseDeltaY())
		{
			FVector3 vRight;
			memcpy(&vRight, &matEditorCamera.m[0][0], sizeof(FVector3));

			FVector3 vLook = m_vAt - m_vEye;
			FMatrix matRotate;

			D3DXMatrixRotationAxis(&matRotate, &vRight, D3DXToRadian(iMouseDeltaY / 10.0f));
			D3DXVec3TransformNormal(&vLook, &vLook, &matRotate);
			m_vAt = m_vEye + vLook;
		}

		int32 iMouseDeltaX = 0;
		if (iMouseDeltaX = CInputManager::GetInstance()->GetMouseDeltaX())
		{
			FVector3 vUp = { 0.f, 1.f, 0.f };
			FVector3 vLook = m_vAt - m_vEye;
			FMatrix matRotate;
			D3DXMatrixRotationAxis(&matRotate, &vUp, D3DXToRadian(iMouseDeltaX / 10.0f));
			D3DXVec3TransformNormal(&vLook, &vLook, &matRotate);
			m_vAt = m_vEye + vLook;
		}
	}
}

void CEditorCamera::UpdateViewMatrix()
{
	// �� ����� ����ϴ�.
	::D3DXMatrixLookAtLH
	(
		&m_matView,
		&m_vEye,
		&m_vAt,
		&m_vUp
	);

	// �� ���(View Projection, V)�� �����մϴ�.
	ENSURE(CDeviceManager::GetInstance()->GetDirect3DDevice9()->SetTransform(D3DTS_VIEW, &m_matView));
}

void CEditorCamera::UpdateProjectionMatrix()
{
	// ���� ���� ����� ����ϴ�.
	::D3DXMatrixPerspectiveFovLH	// Direct3D Matrix Perspective Field of View Left Handed
	(
		&m_matProjection,			// �������� ���
		D3DXToRadian(m_fFoV),		// �þ߰�
		m_fAspectRatio,				// ��Ⱦ��
		m_fNearPlane,				// �����
		m_fFarPlane					// �����
	);

	// ���� ���(Projection Matrix, P)�� �����մϴ�.
	ENSURE(CDeviceManager::GetInstance()->GetDirect3DDevice9()->SetTransform(D3DTS_PROJECTION, &m_matProjection));
}
