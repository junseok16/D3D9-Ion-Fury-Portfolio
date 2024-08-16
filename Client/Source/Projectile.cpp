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

	// �����带 �����մϴ�.

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
	// ��� �ִϸ��̼��� ���
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
	// �� ���
	FMatrix matView;
	matView = dynamic_pointer_cast<CPlayerActor>(GetLevel().lock()->FindActor(L"Player"))->GetCurCamera().lock()->GetPersViewMatrix();

	// �� ��Ŀ��� ������ ��� �����(x, y, z�࿡ ���� �ٸ��� / ������ y�ุ / ����� ���ӿ����� z, x�൵ ���)
	FMatrix matBill;
	D3DXMatrixIdentity(&matBill);
	matBill._11 = matView._11;
	matBill._13 = matView._13;
	matBill._31 = matView._31;
	matBill._33 = matView._33;

	D3DXMatrixInverse(&matBill, 0, &matBill);

	// ���� ���
	FMatrix matWorld;
	matWorld = _wpPrimitiveComponent.lock()->GetWorldMatrix();

	// ũ�� ��ȯ ����
	FVector3 vScale = _wpPrimitiveComponent.lock()->GetComponentScale();

	// ũ�� ��ȯ�� �����
	FMatrix matScaleInverse;
	D3DXMatrixScaling(&matScaleInverse, vScale.x, vScale.y, vScale.z);
	D3DXMatrixInverse(&matScaleInverse, 0, &matScaleInverse);

	// ������Ŀ� ũ�� ��ȯ�� ����� ���ϱ�
	::D3DXMatrixMultiply(&matWorld, &matScaleInverse, &matWorld);

	// ������ ��� ���ϱ�
	::D3DXMatrixMultiply(&matWorld, &matBill, &matWorld);

	// �ٽ� ũ�� ��ȯ ���ϱ�
	FMatrix matScale;
	D3DXMatrixScaling(&matScale, vScale.x, vScale.y, vScale.z);
	::D3DXMatrixMultiply(&matWorld, &matScale, &matWorld);

	_wpPrimitiveComponent.lock()->SetWorldMatrix(matWorld);
}
