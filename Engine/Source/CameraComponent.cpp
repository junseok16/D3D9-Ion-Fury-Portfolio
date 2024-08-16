#include "pch.h"
#include "CameraComponent.h"

#include "DeviceManager.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "TimerManager.h"

#include "ActorComponent.h"
#include "Actor.h"
using namespace std;

void CCameraComponent::Initialize()
{
	shared_ptr<CActor> spActor = GetOwnerActor().lock();
	m_tEye = spActor->GetActorPosition();
	m_tAt = spActor->GetActorPosition() + spActor->GetForwardVector();
	m_tUp = { 0.0f, 1.0f, 0.0f };

	m_vCameraMoveDir = { 1.0f, 1.0f, 0.0f };

	CSceneComponent::Initialize();
}

void CCameraComponent::BeginPlay()
{
	CSceneComponent::BeginPlay();
}

int32 CCameraComponent::Update(const float& _fDeltaSeconds)
{
	int32 iResult = CSceneComponent::Update(_fDeltaSeconds);
	switch (iResult)
	{
	case 0:		break;
	default:	return iResult;
	}

	return 0;
}

int32 CCameraComponent::LateUpdate(const float& _fDeltaSeconds)
{
	int32 iResult = CSceneComponent::LateUpdate(_fDeltaSeconds);
	switch (iResult)
	{
	case 0:		break;
	default:	return iResult;
	}

	// 카메라 컴포넌트의 트랜스폼을 업데이트합니다.
	UpdateCameraTransform();
	return 0;
}

void CCameraComponent::Render()
{
	CSceneComponent::Render();
}

void CCameraComponent::EndPlay()
{
	CSceneComponent::EndPlay();
}

void CCameraComponent::Release()
{
	CSceneComponent::Release();
}

void CCameraComponent::SetCurRenderCamera()
{
	CRenderManager::GetInstance()->SetCurRenderCamera(dynamic_pointer_cast<CCameraComponent>(shared_from_this()));
}

void CCameraComponent::UpdateCameraTransform()
{
	CHECK(!GetOwnerActor().expired());

	shared_ptr<CActor> spActor = GetOwnerActor().lock();

	if (m_bIsCameraMove)
		CameraMove(m_vCameraMoveDir,
					m_fCameraMoveRatioX, m_fCameraMoveRatioY,
					m_fCameraMoveDistanceX, m_fCameraMoveDistanceY);
	else
	{
		m_tEye = spActor->GetActorPosition();
		m_tAt = spActor->GetActorPosition() + spActor->GetForwardVector();
		m_tUp = { 0.0f, 1.0f, 0.0f };
	}

	::D3DXMatrixLookAtLH			// Direct3D Matrix Look At Left Handed
	(
		&m_matPersView,
		&m_tEye,
		&m_tAt,
		&m_tUp
	);

	::D3DXMatrixPerspectiveFovLH	// Direct3D Matrix Perspective Field of View Left Handed
	(
		&m_matPersProj,				// 프로젝션 행렬
		D3DXToRadian(m_fFoV),		// 시야각
		m_fAspectRatio,				// 종횡비
		m_fNearPlane,				// 근평면
		m_fFarPlane					// 원평면
	);

	D3DXMatrixIdentity(&m_matOrthoView);

	::D3DXMatrixOrthoLH
	(
		&m_matOrthoProj,			// 프로젝션 행렬
		CFWINCX,					// 윈도우 스크린 가로	
		CFWINCY,					// 윈도우 스크린 세로
		m_fNearPlane,				// 근평면
		m_fFarPlane					// 원평면
	);

	/*
	* 뷰 행렬 공식
	* zaxis = normal(At - Eye)
	* xaxis = normal(cross(Up, zaxis))
	* yaxis = cross(zaxis, xaxis)
	*
	* [ xaxis.x           yaxis.x           zaxis.x          0 ]
	* [ xaxis.y           yaxis.y           zaxis.y          0 ]
	* [ xaxis.z           yaxis.z           zaxis.z          0 ]
	* [ -dot(xaxis, eye)  -dot(yaxis, eye)  -dot(zaxis, eye) 1 ]
	*/

	/*
	* 원근 투영 행렬 공식
	* yScale = cot(fovY / 2)
	* xScale = yScale / aspect ratio
	*
	* [ xScale		0			0						0 ]
	* [ 0			yScale		0						0 ]
	* [ 0			0			zf / (zf - zn)			1 ]
	* [ 0			0			-zn * zf / (zf - zn)	0 ]
	*/
}

void CCameraComponent::CameraMove(const FVector3& _vDir, const float& _fRatioX, const float& _fRatioY,
								  const float& _fDistanceX, const float& _fDistanceY)
{
	shared_ptr<CActor> spActor = GetOwnerActor().lock();
	float fDeltaSeconds = CTimerManager::GetInstance()->GetDeltaSeconds(L"TimerInner");

	// Y축 역방향 전환
	if (_fDistanceY < fabs(m_vCameraMoveDistance.y) && !m_bIsYFliped)
	{
 		m_vCameraMoveDir.y *= -1.0f;
		m_bIsYFliped = !m_bIsYFliped;
	}
	else if (_fDistanceY < fabs(m_vCameraMoveDistance.y) && m_bIsYFliped)
	{
		m_vCameraMoveDir.y *= -1.0f;
		m_bIsYFliped = !m_bIsYFliped;
	}

	// X축 역방향 전환
	if (_fDistanceX < fabs(m_vCameraMoveDistance.x) && !m_bIsXFliped)
	{
		m_vCameraMoveDir.x *= -1.0f;
		m_bIsXFliped = !m_bIsXFliped;
	}
	else if (_fDistanceX < fabs(m_vCameraMoveDistance.x) && m_bIsXFliped)
	{
		m_vCameraMoveDir.x *= -1.0f;
		m_bIsXFliped = !m_bIsXFliped;
	}

	// X, Y방향 이동거리 증가
	if(!m_bIsYFliped)
		m_vCameraMoveDistance.y += _fRatioY * fDeltaSeconds;
	else
		m_vCameraMoveDistance.y -= _fRatioY * fDeltaSeconds;

	if (!m_bIsXFliped)
		m_vCameraMoveDistance.x += _fRatioX * fDeltaSeconds;
	else
		m_vCameraMoveDistance.x -= _fRatioX * fDeltaSeconds;

	m_tEye = spActor->GetActorPosition();
	m_tAt = spActor->GetActorPosition() + spActor->GetForwardVector();

	m_tEye.x = spActor->GetActorPosition().x + m_vCameraMoveDistance.x;
	m_tAt.x = spActor->GetActorPosition().x + spActor->GetForwardVector().x + m_vCameraMoveDistance.x;

	m_tEye.y = spActor->GetActorPosition().y + m_vCameraMoveDistance.y;
	m_tAt.y = spActor->GetActorPosition().y + spActor->GetForwardVector().y + m_vCameraMoveDistance.y;
}
