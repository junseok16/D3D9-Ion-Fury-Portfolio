#include "pch.h"
#include "FluorescentLampActor.h"

#include "CollisionManager.h"

#include "ParticleComponent.h"

void CFluorescentLampActor::Initialize()
{
	SetRenderType(ERenderType::ALPHA_TEST);
	SetMobility(EMobilityType::STATIC);

	m_wpParticleComponent = CreateActorComponent<CParticleComponent>(L"ParticleComponent");
	SetRootComponent(m_wpParticleComponent);
	m_wpParticleComponent.lock()->SetParticleMeshInfo(L"BlueDoor0_0", 0, 0); // (임시) 빈 텍스처 하나를 넣어줘야 함
	m_wpParticleComponent.lock()->SetParticleInfo(EParticleType::SPRAY, 15, 3.0f, 1.0f, 1.0f);
	m_wpParticleComponent.lock()->SetParticleInterval(0.001f);
	m_wpParticleComponent.lock()->SetIsRemove(false);
	m_wpParticleComponent.lock()->SetIsActive(true);
	m_wpParticleComponent.lock()->AddParticle();

	CActor::Initialize();
}

void CFluorescentLampActor::BeginPlay()
{
	CActor::BeginPlay();
}

int32 CFluorescentLampActor::Update(const float& _fDeltaSeconds)
{
	return CActor::Update(_fDeltaSeconds);
}

int32 CFluorescentLampActor::LateUpdate(const float& _fDeltaSeconds)
{
	return CActor::LateUpdate(_fDeltaSeconds);
}

void CFluorescentLampActor::Render()
{
	CActor::Render();
}

void CFluorescentLampActor::EndPlay()
{
	CActor::EndPlay();
}

void CFluorescentLampActor::Release()
{
	CActor::Release();
}
