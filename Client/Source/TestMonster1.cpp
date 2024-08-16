#include "pch.h"
#include "TestMonster1.h"

#include "RenderManager.h"
#include "CollisionManager.h"

#include "AnimationComponent.h"
#include "CubeColliderComponent.h"

void CTestMonster1::Initialize()
{
	m_wpAnimationComponent = CreateActorComponent<CAnimationComponent>(L"AnimationComponent");
	SetRootComponent(m_wpAnimationComponent);
	m_wpAnimationComponent.lock()->SettingAnimationInfo(L"TestMonster1_Walk_", 0, 4, L"Idle", EAnimationType::LOOP, 1.f);
	CCollisionManager::GetInstance()->AddPrimitiveComponent(m_wpAnimationComponent.lock());

	m_wpCubeColliderComponent = CreateActorComponent<CCubeColliderComponent>(L"CubeColliderComponent");
	m_wpCubeColliderComponent.lock()->SetOwnerComponent(m_wpAnimationComponent);
	m_wpCubeColliderComponent.lock()->SetCollisionLayerType(ECollisionLayerType::MONSTER);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::PLAYER);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::ENVIRONMENT);
	CCollisionManager::GetInstance()->AddColliderComponent(m_wpCubeColliderComponent.lock());

	SetRenderType(ERenderType::ALPHA_TEST);
	SetMobility(EMobilityType::STATIC);

	CCreature::Initialize();
}

void CTestMonster1::BeginPlay()
{
	m_wpAnimationComponent.lock()->AddState(L"Idle", 0, 4);

	CCreature::BeginPlay();
}

int32 CTestMonster1::Update(const float& _fDeltaSeconds)
{
	return CCreature::Update(_fDeltaSeconds);
	CActor::SetBillBoard(m_wpAnimationComponent);
}

int32 CTestMonster1::LateUpdate(const float& _fDeltaSeconds)
{
	return CCreature::LateUpdate(_fDeltaSeconds);
}

void CTestMonster1::Render()
{
	CCreature::Render();
}

void CTestMonster1::EndPlay()
{
	CCreature::EndPlay();
}

void CTestMonster1::Release()
{
	CCreature::Release();
}