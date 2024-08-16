#include "pch.h"
#include "EditorCamera.h"
#include "DeviceManager.h"
#include "InputManager.h"
#include "CollisionManager.h"
#include "ColliderComponent.h"
using namespace std;

void CEditorCamera::Initialize()
{
	// 뷰 행렬과 프로젝션 행렬을 항등 행렬로 초기화합니다.
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

	// 커서를 가운데로 잠그거나 해제합니다.
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

	// 앞으로 이동합니다.
	if (CInputManager::GetInstance()->IsKeyPressed(DIK_W))
	{
		FVector3 vLook;
		memcpy(&vLook, &matEditorCamera.m[2][0], sizeof(FVector3));

		FVector3 vLength = *D3DXVec3Normalize(&vLook, &vLook) * _fDeltaSeconds * m_fSpeed;
		m_vEye += vLength;
		m_vAt += vLength;
	}

	// 뒤로 이동합니다.
	if (CInputManager::GetInstance()->IsKeyPressed(DIK_S))
	{
		FVector3 vLook;
		memcpy(&vLook, &matEditorCamera.m[2][0], sizeof(FVector3));

		FVector3 vLength = *D3DXVec3Normalize(&vLook, &vLook) * _fDeltaSeconds * m_fSpeed;
		m_vEye -= vLength;
		m_vAt -= vLength;
	}

	// 왼쪽으로 이동합니다.
	if (CInputManager::GetInstance()->IsKeyPressed(DIK_A))
	{
		FVector3 vRight;
		memcpy(&vRight, &matEditorCamera.m[0][0], sizeof(FVector3));

		FVector3 vLength = *D3DXVec3Normalize(&vRight, &vRight) * _fDeltaSeconds * m_fSpeed;
		m_vEye -= vLength;
		m_vAt -= vLength;
	}

	// 오른쪽으로 이동합니다.
	if (CInputManager::GetInstance()->IsKeyPressed(DIK_D))
	{
		FVector3 vRight;
		memcpy(&vRight, &matEditorCamera.m[0][0], sizeof(FVector3));

		FVector3 vLength = *D3DXVec3Normalize(&vRight, &vRight) * _fDeltaSeconds * m_fSpeed;
		m_vEye += vLength;
		m_vAt += vLength;
	}

	// 위로 이동합니다.
	if (CInputManager::GetInstance()->IsKeyPressed(DIK_E))
	{
		FVector3 vUp = *D3DXVec3Normalize(&m_vUp, &m_vUp) * _fDeltaSeconds * m_fSpeed;
		m_vEye += vUp;
		m_vAt += vUp;
	}

	// 아래로 이동합니다.
	if (CInputManager::GetInstance()->IsKeyPressed(DIK_Q))
	{
		FVector3 vUp = *D3DXVec3Normalize(&m_vUp, &m_vUp) * _fDeltaSeconds * m_fSpeed;
		m_vEye -= vUp;
		m_vAt -= vUp;
	}

	// 마우스 속도를 증가시킵니다.
	if (CInputManager::GetInstance()->IsKeyDown(DIK_ADD))
	{
		m_fSpeed += 2.0f;
		if (m_fSpeed >= 100.0f) { m_fSpeed = 100.0f; }
	}

	// 마우스 속도를 감소시킵니다.
	if (CInputManager::GetInstance()->IsKeyDown(DIK_SUBTRACT))
	{
		m_fSpeed -= 2.0f;
		if (m_fSpeed <= 1.0f) { m_fSpeed = 1.0f; }
	}
}

void CEditorCamera::UpdateMouseInput()
{
	// 카메라의 월드 좌표를 구합니다.
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
	// 뷰 행렬을 만듭니다.
	::D3DXMatrixLookAtLH
	(
		&m_matView,
		&m_vEye,
		&m_vAt,
		&m_vUp
	);

	// 뷰 행렬(View Projection, V)을 설정합니다.
	ENSURE(CDeviceManager::GetInstance()->GetDirect3DDevice9()->SetTransform(D3DTS_VIEW, &m_matView));
}

void CEditorCamera::UpdateProjectionMatrix()
{
	// 원근 투영 행렬을 만듭니다.
	::D3DXMatrixPerspectiveFovLH	// Direct3D Matrix Perspective Field of View Left Handed
	(
		&m_matProjection,			// 프로젝션 행렬
		D3DXToRadian(m_fFoV),		// 시야각
		m_fAspectRatio,				// 종횡비
		m_fNearPlane,				// 근평면
		m_fFarPlane					// 원평면
	);

	// 투영 행렬(Projection Matrix, P)를 설정합니다.
	ENSURE(CDeviceManager::GetInstance()->GetDirect3DDevice9()->SetTransform(D3DTS_PROJECTION, &m_matProjection));
}
