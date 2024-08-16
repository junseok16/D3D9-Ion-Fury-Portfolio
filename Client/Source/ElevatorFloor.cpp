#include "pch.h"
#include "ElevatorFloor.h"

// Component
#include "CubeMeshComponent.h"
#include "CubeColliderComponent.h"

// Manager
#include "CollisionManager.h"

using namespace std;

void CElevatorFloor::Initialize()
{
	InGameSetting();

	ColliderSetting();

	SetRenderType(ERenderType::NON_ALPHA);
	CInteractiveBox::Initialize();
}

void CElevatorFloor::BeginPlay()
{
	CInteractiveBox::BeginPlay();
}

int32 CElevatorFloor::Update(const float& _fDeltaSeconds)
{
	return CInteractiveBox::Update(_fDeltaSeconds);
}

int32 CElevatorFloor::LateUpdate(const float& _fDeltaSeconds)
{
	return CInteractiveBox::LateUpdate(_fDeltaSeconds);
}

void CElevatorFloor::Render()
{
	CInteractiveBox::Render();
}

void CElevatorFloor::EndPlay()
{
	CInteractiveBox::EndPlay();
}

void CElevatorFloor::Release()
{
	CInteractiveBox::Release();
}

void CElevatorFloor::InGameSetting()
{
	m_wpElevatorFloor = CreateActorComponent<CCubeMeshComponent>(L"ElevatorFloor");
	SetRootComponent(m_wpElevatorFloor);
	m_wpElevatorFloor.lock()->SetCubeMeshInfo(L"ElevatorDoor0_0", 0, L"dds");

	CCollisionManager::GetInstance()->AddPrimitiveComponent(m_wpElevatorFloor.lock());
}

void CElevatorFloor::ColliderSetting()
{	// 육면체 콜라이더
	m_wpCubeColliderComponent = CreateActorComponent<CCubeColliderComponent>(L"CubeColliderComponent");
	m_wpCubeColliderComponent.lock()->SetOwnerComponent(m_wpElevatorFloor);
	m_wpCubeColliderComponent.lock()->SetCollisionLayerType(ECollisionLayerType::GROUND);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::PLAYER);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::MONSTER);
	CCollisionManager::GetInstance()->AddColliderComponent(m_wpCubeColliderComponent.lock());
}
