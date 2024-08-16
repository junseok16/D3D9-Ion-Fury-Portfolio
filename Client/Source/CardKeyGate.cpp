#include "pch.h"
#include "CardKeyGate.h"


// Component
#include "CubeMeshComponent.h"
#include "CubeColliderComponent.h"

// Manager
#include "CollisionManager.h"

using namespace std;

void CCardKeyGate::Initialize()
{
	InGameSetting();

	ColliderSetting();

	SetRenderType(ERenderType::NON_ALPHA);
	CInteractiveBox::Initialize();
}

void CCardKeyGate::BeginPlay()
{
	CInteractiveBox::BeginPlay();
}

int32 CCardKeyGate::Update(const float& _fDeltaSeconds)
{
	return CInteractiveBox::Update(_fDeltaSeconds);
}

int32 CCardKeyGate::LateUpdate(const float& _fDeltaSeconds)
{
	return CInteractiveBox::LateUpdate(_fDeltaSeconds);
}

void CCardKeyGate::Render()
{
	CInteractiveBox::Render();
}

void CCardKeyGate::EndPlay()
{
	CInteractiveBox::EndPlay();
}

void CCardKeyGate::Release()
{
	CInteractiveBox::Release();
}

void CCardKeyGate::InGameSetting()
{
	m_wpCardKeyGate = CreateActorComponent<CCubeMeshComponent>(L"LeverGate");
	SetRootComponent(m_wpCardKeyGate);
	m_wpCardKeyGate.lock()->SetCubeMeshInfo(L"IronGate0_", 0, L"dds");
}

void CCardKeyGate::ColliderSetting()
{	// 육면체 콜라이더
	m_wpCubeColliderComponent = CreateActorComponent<CCubeColliderComponent>(L"CubeColliderComponent");
	m_wpCubeColliderComponent.lock()->SetOwnerComponent(m_wpCardKeyGate);
	m_wpCubeColliderComponent.lock()->SetCollisionLayerType(ECollisionLayerType::WALL);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::PLAYER);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::MONSTER);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::ITEM);
	CCollisionManager::GetInstance()->AddColliderComponent(m_wpCubeColliderComponent.lock());
}

