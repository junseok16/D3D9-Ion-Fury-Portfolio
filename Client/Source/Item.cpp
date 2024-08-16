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