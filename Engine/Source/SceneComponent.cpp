#include "pch.h"
#include "SceneComponent.h"

#include "Actor.h"
using namespace std;

void CSceneComponent::Initialize()
{
	CActorComponent::Initialize();
}

void CSceneComponent::BeginPlay()
{
	// 스태틱 액터가 갖고 있는 컴포넌트의 트랜스폼을 초기화합니다.
	UpdateSceneComponentTransform();
	CActorComponent::BeginPlay();
}

int32 CSceneComponent::Update(const float& _fDeltaSeconds)
{
	// 다이나믹 액터가 갖고 있는 컴포넌트의 트랜스폼을 업데이트합니다.
	if (GetOwnerActor().lock()->GetMobility() == EMobilityType::DYNAMIC)
	{
		UpdateSceneComponentTransform();
	}

	return CActorComponent::Update(_fDeltaSeconds);
}

int32 CSceneComponent::LateUpdate(const float& _fDeltaSeconds)
{
	return CActorComponent::LateUpdate(_fDeltaSeconds);
}

void CSceneComponent::Render()
{
	CActorComponent::Render();
}

void CSceneComponent::EndPlay()
{
	CActorComponent::EndPlay();
}

void CSceneComponent::Release()
{
	CActorComponent::Release();
}

void CSceneComponent::UpdateSceneComponentTransform()
{
	// 월드 행렬을 단위 행렬로 초기화합니다.
	::D3DXMatrixIdentity(&m_matWorld);

	// 로컬 행렬을 단위 행렬로 초기화합니다.
	::D3DXMatrixIdentity(&m_matLocal);

	// 부모 컴포넌트의 행렬을 단위 행렬로 초기화합니다.
	::D3DXMatrixIdentity(&m_matOwnerWorld);

	// 크기 변환 행렬
	FMatrix matScale;
	::D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);

	// 회전 변환 행렬
	FMatrix matRotate[3];
	::D3DXMatrixRotationX(&matRotate[0], D3DXToRadian(m_vRotate.x));
	::D3DXMatrixRotationY(&matRotate[1], D3DXToRadian(m_vRotate.y));
	::D3DXMatrixRotationZ(&matRotate[2], D3DXToRadian(m_vRotate.z));

	// 이동 변환 행렬
	FMatrix matTranslate;
	::D3DXMatrixTranslation(&matTranslate, m_vTranslate.x, m_vTranslate.y, m_vTranslate.z);

	// 로컬 행렬에 크기 변환 행렬을 곱합니다.
	D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &matScale);

	// 로컬 행렬에 회전 변환 행렬을 곱합니다.
	::D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &matRotate[0]);
	::D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &matRotate[1]);
	::D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &matRotate[2]);

	// 로컬 행렬에 이동 변환 행렬을 곱합니다.
	::D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &matTranslate);

	// 소유한 액터 혹은 컴포넌트의 월드 행렬
	switch (m_bIsRootComponent)
	{
	case true:
		CHECK(!GetOwnerActor().expired());
		m_matOwnerWorld = GetOwnerActor().lock()->GetWorldMatrix();
		break;

	case false:
		CHECK(!GetOwnerComponent().expired());
		m_matOwnerWorld = dynamic_pointer_cast<CSceneComponent>(GetOwnerComponent().lock())->GetWorldMatrix();
		break;
	}
	
	//  액터 크기 * 회전 * 이동 * 부모 크기 * 회전 * 이동
	::D3DXMatrixMultiply(&m_matLocal, &m_matLocal, &m_matOwnerWorld);

	// 컴포넌트의 월드 행렬을 갱신합니다.
	m_matWorld = m_matLocal;

	// 컴포넌트의 월드 좌표를 갱신합니다.
	m_vWorldPosition = { m_matWorld._41, m_matWorld._42, m_matWorld._43 };
}
