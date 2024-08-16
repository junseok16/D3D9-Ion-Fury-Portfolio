#include "pch.h"
#include "ParticleTestActor.h"

#include "ParticleComponent.h"

void CParticleTestActor::Initialize()
{
	m_wpParticleComponent = CreateActorComponent<CParticleComponent>(L"ParticleComponent");
	SetRootComponent(m_wpParticleComponent);
	m_wpParticleComponent.lock()->SetOwnerActor(dynamic_pointer_cast<CActor>(shared_from_this()));
	m_wpParticleComponent.lock()->SetParticleMeshInfo(L"Sidewalk0_", 0, 0); // (임시) 빈 텍스처 하나를 넣어줘야 함
	m_wpParticleComponent.lock()->SetParticleInfo(EParticleType::FALLEN, 128, 3.0f, 1.0f, 5.0f);
	m_wpParticleComponent.lock()->SetParticleInterval(0.001f);
	m_wpParticleComponent.lock()->SetIsRemove(false);
	m_wpParticleComponent.lock()->SetIsActive(true);
	m_wpParticleComponent.lock()->AddParticle();

	CActor::Initialize();
}

void CParticleTestActor::BeginPlay()
{

	CActor::BeginPlay();
}

int32 CParticleTestActor::Update(const float& _fDeltaSeconds)
{
	return CActor::Update(_fDeltaSeconds);
}

int32 CParticleTestActor::LateUpdate(const float& _fDeltaSeconds)
{
	return CActor::LateUpdate(_fDeltaSeconds);
}

void CParticleTestActor::Render()
{
	CActor::Render();
}

void CParticleTestActor::EndPlay()
{
	CActor::EndPlay();
}

void CParticleTestActor::Release()
{
	CActor::Release();
}
