#include "pch.h"
#include "ThrowingBox.h"

#include "Level.h"

#include "CubeMeshComponent.h"
#include "CubeColliderComponent.h"

#include "CollisionManager.h"
using namespace std;

/********************
	Framework
********************/
void CThrowingBox::Initialize()
{
	InitializeCubeMeshComponent();
	InitializeCubeColliderComponent();

	SetRenderType(ERenderType::NON_ALPHA);
	SetMobility(EMobilityType::DYNAMIC);
	CCubeColliderActor::Initialize();
}

void CThrowingBox::BeginPlay()
{
	m_wpPlayer = GetLevel().lock()->FindActor(L"Player");

	CCubeColliderActor::BeginPlay();
}

int32 CThrowingBox::Update(const float& _fDeltaSeconds)
{
	switch (m_eCurThrowingBoxState)
	{
	case EThrowingBoxState::IDLE:
		break;

	case EThrowingBoxState::FLOAT:
		FloatThrowingBox(_fDeltaSeconds);
		break;

	case EThrowingBoxState::THROW:
		ThrowThrowingBox(_fDeltaSeconds);
		break;

	case EThrowingBoxState::RETRIEVE:
		RetrieveThrowingBox();
		break;
	}

	// FVector3 vRot = GetActorRotation();


	return CCubeColliderActor::Update(_fDeltaSeconds);
}

int32 CThrowingBox::LateUpdate(const float& _fDeltaSeconds)
{
	return CCubeColliderActor::LateUpdate(_fDeltaSeconds);
}

void CThrowingBox::Render()
{
	CCubeColliderActor::Render();
}

void CThrowingBox::EndPlay()
{
	CCubeColliderActor::EndPlay();
}

void CThrowingBox::Release()
{
	CCubeColliderActor::Release();
}

/********************
	Component
********************/
void CThrowingBox::InitializeCubeMeshComponent()
{
	m_wpCubeMeshComponent = CreateActorComponent<CCubeMeshComponent>(L"CubeMeshComponent");
	m_wpCubeMeshComponent.lock()->SetCubeMeshInfo(m_wstrBoxs[0]);
	SetRootComponent(m_wpCubeMeshComponent);
}

void CThrowingBox::InitializeCubeColliderComponent()
{
	m_wpCubeColliderComponent = CreateActorComponent<CCubeColliderComponent>(L"CubeColliderComponent");
	m_wpCubeColliderComponent.lock()->SetOwnerComponent(m_wpCubeMeshComponent);
	m_wpCubeColliderComponent.lock()->SetCollisionLayerType(ECollisionLayerType::PROJECTILE);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::PLAYER);
	CCollisionManager::GetInstance()->AddColliderComponent(m_wpCubeColliderComponent.lock());
}

/********************
	Callbacks
********************/
int32 CThrowingBox::OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	return 0;
}

void CThrowingBox::OnCollisionStay(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
}

void CThrowingBox::OnCollisionExit(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
}

/********************
	Methods
********************/
void CThrowingBox::RetrieveThrowingBox()
{
	FVector3 vPos = m_wpPlayer.lock()->GetActorPosition();
	FVector3 vUp = FVector3(0.0f, 0.0f, 0.0f);
	FVector3 vDir = vPos - vUp;
	D3DXVec3Normalize(&vDir, &vDir);

	FVector3 vCross;
	D3DXVec3Cross(&vCross, &vDir, &vUp);

	switch (m_iThrowingboxIndex)
	{
	case 0:
		SetActorPosition({ vPos.x, -72.0f, vPos.z });
		break;

	case 1:
		SetActorPosition({ vPos.x, -72.0f, vPos.z });
		break;

	case 2:
		SetActorPosition({ vPos.x, -72.0f, vPos.z });
		break;

	case 3:
		SetActorPosition({ vPos.x, -72.0f, vPos.z });
		break;

	case 4:
		SetActorPosition({ vPos.x, -72.0f, vPos.z });
		break;

	case 5:
		SetActorPosition({ vPos.x, -72.0f, vPos.z });
		break;
	}
}

void CThrowingBox::ThrowThrowingBox(float _fDeltaSeconds)
{

}

void CThrowingBox::FloatThrowingBox(float _fDeltaSeconds)
{
	FVector3 vPos = GetActorPosition();
	FVector3 vDist = m_wpPlayer.lock()->GetActorPosition() - vPos;

	if (D3DXVec3Length(&vDist) <= 2.0f) { return; }

	vPos += FVector3(0.0f, 1.0f, 0.0f) * m_fSpeed * _fDeltaSeconds;
	SetActorPosition(vPos);
}

void CThrowingBox::SetThrowingBoxState(EThrowingBoxState _eCurThrowingBoxState)
{
	if (m_eCurThrowingBoxState == _eCurThrowingBoxState) { return; }

	m_ePrevThrowingBoxState = m_eCurThrowingBoxState;
	m_eCurThrowingBoxState = _eCurThrowingBoxState;
}
