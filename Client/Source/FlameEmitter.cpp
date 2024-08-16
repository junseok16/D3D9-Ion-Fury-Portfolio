#include "pch.h"
#include "FlameEmitter.h"

#include "RectangleMeshComponent.h"
#include "AnimationComponent.h"
#include "CubeColliderComponent.h"

#include "CollisionManager.h"
#include "InputManager.h"
using namespace std;

/********************
	Framework
********************/
void CFlameEmitter::Initialize()
{
	InitializeRectMeshComponent();
	InitializeAnimationComponent();
	InitializeCubeColliderComponent();

	SetRenderType(ERenderType::ALPHA_TEST);
	SetMobility(EMobilityType::DYNAMIC);
	CCubeColliderActor::Initialize();
}

void CFlameEmitter::BeginPlay()
{
	SetActorScale({ 12.0f, 12.0f, 12.0f });

	m_wpAnimationComponent.lock()->AddState(L"Idle", 0, 25);
	m_wpAnimationComponent.lock()->SetCurrentState(L"Idle");
	CCubeColliderActor::BeginPlay();
}

int32 CFlameEmitter::Update(const float& _fDeltaSeconds)
{
	UpdateEmitterPosition();
	UpdateEmitterState();
	UpdateEmitterAnim();
	return CCubeColliderActor::Update(_fDeltaSeconds);
}

int32 CFlameEmitter::LateUpdate(const float& _fDeltaSeconds)
{
	return CCubeColliderActor::LateUpdate(_fDeltaSeconds);
}

void CFlameEmitter::Render()
{
	CCubeColliderActor::Render();
}

void CFlameEmitter::EndPlay()
{
	CCubeColliderActor::EndPlay();
}

void CFlameEmitter::Release()
{
	CCubeColliderActor::Release();
}

/********************
	Component
********************/
void CFlameEmitter::InitializeRectMeshComponent()
{
	m_wpRectMeshComponent = CreateActorComponent<CRectangleMeshComponent>(L"RecteMeshComponent");
	m_wpRectMeshComponent.lock()->SetRectangleMeshInfo(L"LaserEmitter0_0", 0, 0);
	m_wpRectMeshComponent.lock()->SetComponentRotation({ 90.0f, 0.0f, 0.0f });
	SetRootComponent(m_wpRectMeshComponent);
}

void CFlameEmitter::InitializeAnimationComponent()
{
	m_wpAnimationComponent = CreateActorComponent<CAnimationComponent>(L"AnimationComponent");
	m_wpAnimationComponent.lock()->SettingAnimationInfo(L"ThinFlame0_0", 0, 25, L"Idle", EAnimationType::LOOP, 1.0f);
	m_wpAnimationComponent.lock()->SetComponentLocalPosition({ 0.0f, 1.4f, 0.0f });
	m_wpAnimationComponent.lock()->SetComponentScale({ 1.0f, 2.6f, 1.0f });
	SetRootComponent(m_wpAnimationComponent);
}

void CFlameEmitter::InitializeCubeColliderComponent()
{
	m_wpCubeColliderComponent = CreateActorComponent<CCubeColliderComponent>(L"CubeColliderComponent");
	m_wpCubeColliderComponent.lock()->SetComponentLocalPosition({ 0.0f, 0.0f, -0.5f });
	m_wpCubeColliderComponent.lock()->SetComponentScale({ 0.5f, 0.5f, 1.0f });
	m_wpCubeColliderComponent.lock()->SetCollisionLayerType(ECollisionLayerType::PROJECTILE);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::PLAYER);
	m_wpCubeColliderComponent.lock()->SetOwnerComponent(m_wpRectMeshComponent);
	CCollisionManager::GetInstance()->AddColliderComponent(m_wpCubeColliderComponent.lock());
}

/********************
	Methods
********************/
void CFlameEmitter::UpdateEmitterPosition()
{
	FVector3 vPos = m_wpFloatingBox.lock()->GetActorPosition();

	switch (m_iEmitterIndex)
	{
	case 0: SetActorPosition(vPos + FVector3(-9.1f, 36.1f, 9.1f));	break;
	case 1: SetActorPosition(vPos + FVector3(9.1f, 36.1f, 9.1f));	break;
	case 2: SetActorPosition(vPos + FVector3(-9.1f, 36.1f, -9.1f));	break;
	case 3: SetActorPosition(vPos + FVector3(9.1f, 36.1f, -9.1f));	break;
	}
}

void CFlameEmitter::UpdateEmitterState()
{
	switch (m_eFlameEmitterState)
	{
	case EFlameEmitterState::FLAME_ON:
		break;

	case EFlameEmitterState::FLAME_OFF:
		break;
	}
}

void CFlameEmitter::UpdateEmitterAnim()
{
	switch (m_eFlameEmitterState)
	{
	case EFlameEmitterState::FLAME_ON:
		m_wpAnimationComponent.lock()->SetIsRender(true);
		break;

	case EFlameEmitterState::FLAME_OFF:
		m_wpAnimationComponent.lock()->SetIsRender(false);
		break;
	}
}

/********************
	Callbacks
********************/
int32 CFlameEmitter::OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	switch (m_eFlameEmitterState)
	{
	case EFlameEmitterState::FLAME_ON:
		// TODO: 플레이어의 체력을 감소시킵니다.
		break;
	}
	return 0;
}

void CFlameEmitter::OnCollisionStay(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	switch (m_eFlameEmitterState)
	{
	case EFlameEmitterState::FLAME_ON:
		// TODO: 플레이어의 체력을 감소시킵니다.
		break;
	}
}
