#include "pch.h"
#include "Item.h"

#include "Level.h"
#include "PlayerActor.h"

#include "CameraComponent.h"
#include "AnimationComponent.h"
#include "RectangleMeshComponent.h"
#include "SoundComponent.h"

using namespace std;

void CItem::Initialize()
{
	m_eRenderType = ERenderType::ALPHA_TEST;
	CCubeColliderActor::Initialize();
}

void CItem::BeginPlay()
{
	CCubeColliderActor::BeginPlay();
}

int32 CItem::Update(const float& _fDeltaSeconds)
{
	return CCubeColliderActor::Update(_fDeltaSeconds);
}

int32 CItem::LateUpdate(const float& _fDeltaSeconds)
{
	return CCubeColliderActor::LateUpdate(_fDeltaSeconds);
}

void CItem::Render()
{
	CCubeColliderActor::Render();
}

void CItem::EndPlay()
{
	CCubeColliderActor::EndPlay();
}

void CItem::Release()
{
	CCubeColliderActor::Release();
}

void CItem::SetBillboard(std::weak_ptr<CPrimitiveComponent> _wpPrimitiveComponent)
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