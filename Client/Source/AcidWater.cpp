#include "pch.h"
#include "AcidWater.h"

#include "AnimationComponent.h"
#include "CubeColliderComponent.h"

#include "CollisionManager.h"
using namespace std;

/********************
	Framework
********************/
void CAcidWater::Initialize()
{
	InitializeAnimationComponent();

	SetRenderType(ERenderType::NON_ALPHA);
	SetMobility(EMobilityType::DYNAMIC);
	CCubeColliderActor::Initialize();
}

void CAcidWater::BeginPlay()
{
	SetActorRotation({ 90.0f, 0.0f, 0.0f });
	SetActorScale({ 36.0f, 36.0f, 4.0f });

	m_wpAnimationComponent.lock()->AddState(L"Idle", 0, 15);
	m_wpAnimationComponent.lock()->SetCurrentState(L"Idle");
	CCubeColliderActor::BeginPlay();
}

int32 CAcidWater::Update(const float& _fDeltaSeconds)
{

	return CCubeColliderActor::Update(_fDeltaSeconds);
}

int32 CAcidWater::LateUpdate(const float& _fDeltaSeconds)
{
	return CCubeColliderActor::LateUpdate(_fDeltaSeconds);
}

void CAcidWater::Render()
{
	CCubeColliderActor::Render();
}

void CAcidWater::EndPlay()
{
	CCubeColliderActor::EndPlay();
}

void CAcidWater::Release()
{
	CCubeColliderActor::Release();
}

/********************
	Component
********************/
void CAcidWater::InitializeAnimationComponent()
{
	m_wpAnimationComponent = CreateActorComponent<CAnimationComponent>(L"AnimationComponent");
	m_wpAnimationComponent.lock()->SettingAnimationInfo(L"AcidWater0_0", 0, 15, L"Idle", EAnimationType::LOOP, 1.0f);
	SetRootComponent(m_wpAnimationComponent);
}

/********************
	Callbacks
********************/
int32 CAcidWater::OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	return 0;
}
