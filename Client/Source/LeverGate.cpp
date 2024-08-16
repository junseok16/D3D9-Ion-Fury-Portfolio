#include "pch.h"
#include "LeverGate.h"

#include "CollisionManager.h"

#include "CubeMeshComponent.h"

#include "CubeColliderComponent.h"

using namespace std;
void CLeverGate::Initialize()
{
	InGameSetting();

	ColliderSetting();

	SetRenderType(ERenderType::NON_ALPHA);
	CInteractiveBox::Initialize();
}

void CLeverGate::BeginPlay()
{
	CInteractiveBox::BeginPlay();
}

int32 CLeverGate::Update(const float& _fDeltaSeconds)
{
	return CInteractiveBox::Update(_fDeltaSeconds);
}

int32 CLeverGate::LateUpdate(const float& _fDeltaSeconds)
{
	return CInteractiveBox::LateUpdate(_fDeltaSeconds);
}

void CLeverGate::Render()
{
	CInteractiveBox::Render();
}

void CLeverGate::EndPlay()
{
	CInteractiveBox::EndPlay();
}

void CLeverGate::Release()
{
	CInteractiveBox::Release();
}

void CLeverGate::InGameSetting()
{
	m_wpLeverGate = CreateActorComponent<CCubeMeshComponent>(L"LeverGate");
	SetRootComponent(m_wpLeverGate);
	m_wpLeverGate.lock()->SetCubeMeshInfo(L"MetalStair0_", 0, L"dds");
		
	CCollisionManager::GetInstance()->AddPrimitiveComponent(m_wpLeverGate.lock());
}

void CLeverGate::ColliderSetting()
{	// 육면체 콜라이더
	m_wpCubeColliderComponent = CreateActorComponent<CCubeColliderComponent>(L"CubeColliderComponent");
	m_wpCubeColliderComponent.lock()->SetOwnerComponent(m_wpLeverGate);
	m_wpCubeColliderComponent.lock()->SetCollisionLayerType(ECollisionLayerType::WALL);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::PLAYER);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::MONSTER);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::ITEMOBJECT);
	CCollisionManager::GetInstance()->AddColliderComponent(m_wpCubeColliderComponent.lock());
}

