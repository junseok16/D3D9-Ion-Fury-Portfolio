#include "pch.h"
#include "RainParticleActor.h"

#include "ParticleComponent.h"

void CRainParticleActor::Initialize()
{
	ParticleComponentSetting();

	SetRenderType(ERenderType::ALPHA_TEST);
	SetMobility(EMobilityType::DYNAMIC);

	CActor::Initialize();
}

void CRainParticleActor::BeginPlay()
{

	CActor::BeginPlay();
}

int32 CRainParticleActor::Update(const float& _fDeltaSeconds)
{
	return CActor::Update(_fDeltaSeconds);
}

int32 CRainParticleActor::LateUpdate(const float& _fDeltaSeconds)
{
	return CActor::LateUpdate(_fDeltaSeconds);
}

void CRainParticleActor::Render()
{
	CActor::Render();
}

void CRainParticleActor::EndPlay()
{
	CActor::EndPlay();
}

void CRainParticleActor::Release()
{
	CActor::Release();
}

void CRainParticleActor::ParticleComponentSetting()
{
	// 파티클 컴포넌트
	m_wpParticleComponent = CreateActorComponent<CParticleComponent>(L"ParticleComponent");
	SetRootComponent(m_wpParticleComponent);
	m_wpParticleComponent.lock()->SetOwnerActor(dynamic_pointer_cast<CActor>(shared_from_this()));
	m_wpParticleComponent.lock()->SetParticleMeshInfo(L"Snow1_", 0, 0);
	m_wpParticleComponent.lock()->SetIsRemove(false);
	m_wpParticleComponent.lock()->SetIsActive(true);
	m_wpParticleComponent.lock()->SetParticleInfo(EParticleType::RAIN, 512);
	m_wpParticleComponent.lock()->SetParticleSize(2.0f);
	m_wpParticleComponent.lock()->SetParticleLifeTime(1000.0f);
	m_wpParticleComponent.lock()->SetParticleSpeed(200.0f);
	m_wpParticleComponent.lock()->AddParticle();
}