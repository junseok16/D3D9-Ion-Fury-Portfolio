#include "pch.h"
#include "WarmechCharge.h"

#include "RectangleMeshComponent.h"
using namespace std;

void CWarmechCharge::Initialize()
{
	InitializeRectMeshComponent();

	SetRenderType(ERenderType::ALPHA_BLEND);
	SetMobility(EMobilityType::DYNAMIC);
	CCubeColliderActor::Initialize();
}

void CWarmechCharge::BeginPlay()
{
	SetActorScale({ 30.0f, 1.0f, 102.0f });
	CCubeColliderActor::BeginPlay();
}

int32 CWarmechCharge::Update(const float& _fDeltaSeconds)
{
	UpdateChargePosition();
	return CCubeColliderActor::Update(_fDeltaSeconds);
}

int32 CWarmechCharge::LateUpdate(const float& _fDeltaSeconds)
{
	return CCubeColliderActor::LateUpdate(_fDeltaSeconds);
}

void CWarmechCharge::Render()
{
	CCubeColliderActor::Render();
}

void CWarmechCharge::EndPlay()
{
	CCubeColliderActor::EndPlay();
}

void CWarmechCharge::Release()
{
	CCubeColliderActor::Release();
}

void CWarmechCharge::InitializeRectMeshComponent()
{
	m_wpRectMeshComponent = CreateActorComponent<CRectangleMeshComponent>(L"RecteMeshComponent");
	m_wpRectMeshComponent.lock()->SetRectangleMeshInfo(L"Warmech_Charge0_0", 0, 0);
	m_wpRectMeshComponent.lock()->SetComponentRotation({ 90.0f, 180.0f, 0.0f });
	SetRootComponent(m_wpRectMeshComponent);
}

void CWarmechCharge::UpdateChargePosition()
{
}
