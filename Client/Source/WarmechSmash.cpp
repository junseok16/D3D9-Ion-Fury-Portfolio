#include "pch.h"
#include "WarmechSmash.h"

#include "RectangleMeshComponent.h"
using namespace std;

void CWarmechSmash::Initialize()
{
	InitializeRectMeshComponent();

	SetRenderType(ERenderType::ALPHA_BLEND);
	SetMobility(EMobilityType::DYNAMIC);
	CCubeColliderActor::Initialize();
}

void CWarmechSmash::BeginPlay()
{
	SetActorScale({ 150.0f, 1.0f, 150.0f });
	SetActorPosition({ 0.0f, 100.0f, 0.0f });
	CCubeColliderActor::BeginPlay();
}

int32 CWarmechSmash::Update(const float& _fDeltaSeconds)
{
	return CCubeColliderActor::Update(_fDeltaSeconds);
}

int32 CWarmechSmash::LateUpdate(const float& _fDeltaSeconds)
{
	return CCubeColliderActor::LateUpdate(_fDeltaSeconds);
}

void CWarmechSmash::Render()
{
	CCubeColliderActor::Render();
}

void CWarmechSmash::EndPlay()
{
	CCubeColliderActor::EndPlay();
}

void CWarmechSmash::Release()
{
	CCubeColliderActor::Release();
}

void CWarmechSmash::InitializeRectMeshComponent()
{
	m_wpRectMeshComponent = CreateActorComponent<CRectangleMeshComponent>(L"RecteMeshComponent");
	m_wpRectMeshComponent.lock()->SetRectangleMeshInfo(L"Warmech_Smash0_0", 0, 0);
	m_wpRectMeshComponent.lock()->SetComponentRotation({ 90.0f, 0.0f, 0.0f });
	SetRootComponent(m_wpRectMeshComponent);
}
