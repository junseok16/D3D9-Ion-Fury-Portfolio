// Default
#include "pch.h"
#include "Projectile.h"

// Manager
#include "RenderManager.h"

// Component
#include "AnimationComponent.h"
#include "CameraComponent.h"

// Framework
#include "Level.h"
#include "PlayerActor.h"
using namespace std;

void CProjectile::Initialize()
{
	CCubeColliderActor::Initialize();
}

void CProjectile::BeginPlay()
{
	CCubeColliderActor::BeginPlay();
}

int32 CProjectile::Update(const float& _fDeltaSeconds)
{
	return CCubeColliderActor::Update(_fDeltaSeconds);
}

int32 CProjectile::LateUpdate(const float& _fDeltaSeconds)
{
	if (IsDead(_fDeltaSeconds)) { return -1; }

	// 빌보드를 설정합니다.

	SetBillBoard(m_wpAnimationComponent);
	return CCubeColliderActor::LateUpdate(_fDeltaSeconds);
}

void CProjectile::Render()
{
	CCubeColliderActor::Render();
}

void CProjectile::EndPlay()
{
	CCubeColliderActor::EndPlay();
}

void CProjectile::Release()
{
	CCubeColliderActor::Release();
}

bool CProjectile::IsDead(const float& _fDeltaSeconds)
{
	// 사망 애니메이션인 경우
	if (m_bIsDead)
	{
		m_fSumDeadDelay += _fDeltaSeconds;

		if (m_fSumDeadDelay >= 0.5f)
		{
			CRenderManager::GetInstance()->RemoveActor(m_eRenderType, dynamic_pointer_cast<CActor>(shared_from_this()));
			GetLevel().lock()->RemoveActor(GetActorName());
			return true;
		}
	}
	return false;
}

void CProjectile::SetBillBoard(std::weak_ptr<CPrimitiveComponent> _wpPrimitiveComponent)
{
	// 뷰 행렬
	FMatrix matView;
	matView = dynamic_pointer_cast<CPlayerActor>(GetLevel().lock()->FindActor(L"Player"))->GetCurCamera().lock()->GetPersViewMatrix();

	// 뷰 행렬에서 빌보드 행렬 만들기(x, y, z축에 따라 다르게 / 지금은 y축만 / 비행기 게임에서는 z, x축도 사용)
	FMatrix matBill;
	D3DXMatrixIdentity(&matBill);
	matBill._11 = matView._11;
	matBill._13 = matView._13;
	matBill._31 = matView._31;
	matBill._33 = matView._33;

	D3DXMatrixInverse(&matBill, 0, &matBill);

	// 월드 행렬
	FMatrix matWorld;
	matWorld = _wpPrimitiveComponent.lock()->GetWorldMatrix();

	// 크기 변환 벡터
	FVector3 vScale = _wpPrimitiveComponent.lock()->GetComponentScale();

	// 크기 변환의 역행렬
	FMatrix matScaleInverse;
	D3DXMatrixScaling(&matScaleInverse, vScale.x, vScale.y, vScale.z);
	D3DXMatrixInverse(&matScaleInverse, 0, &matScaleInverse);

	// 월드행렬에 크기 변환의 역행렬 곱하기
	::D3DXMatrixMultiply(&matWorld, &matScaleInverse, &matWorld);

	// 빌보드 행렬 곱하기
	::D3DXMatrixMultiply(&matWorld, &matBill, &matWorld);

	// 다시 크기 변환 곱하기
	FMatrix matScale;
	D3DXMatrixScaling(&matScale, vScale.x, vScale.y, vScale.z);
	::D3DXMatrixMultiply(&matWorld, &matScale, &matWorld);

	_wpPrimitiveComponent.lock()->SetWorldMatrix(matWorld);
}
