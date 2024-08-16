#include "pch.h"
#include "PlayerParticleActor.h"

#include "DeviceManager.h"
#include "RenderManager.h"

#include "ParticleComponent.h"

void CPlayerParticleActor::Initialize()
{
	ParticleComponentSetting(); // 파티클 컴포넌트 세팅

	SetRenderType(ERenderType::ALPHA_TEST);
	SetMobility(EMobilityType::DYNAMIC);

	CActor::Initialize();
}

void CPlayerParticleActor::BeginPlay()
{
	CActor::BeginPlay();
}

int32 CPlayerParticleActor::Update(const float& _fDeltaSeconds)
{
	

	return CActor::Update(_fDeltaSeconds);
}

int32 CPlayerParticleActor::LateUpdate(const float& _fDeltaSeconds)
{
	return CActor::LateUpdate(_fDeltaSeconds);
}

void CPlayerParticleActor::Render()
{
	CActor::Render();
}

void CPlayerParticleActor::EndPlay()
{
	CActor::EndPlay();
}

void CPlayerParticleActor::Release()
{
	CActor::Release();
}

void CPlayerParticleActor::ParticleComponentSetting()
{
	// 파티클 컴포넌트
	m_wpParticleComponent = CreateActorComponent<CParticleComponent>(L"ParticleComponent");
	SetRootComponent(m_wpParticleComponent);
	m_wpParticleComponent.lock()->SetOwnerActor(dynamic_pointer_cast<CActor>(shared_from_this()));
	m_wpParticleComponent.lock()->SetParticleMeshInfo(L"Explosion0_", 0, 0);
	m_wpParticleComponent.lock()->SetParticleInfo(EParticleType::ERUPTION, 64, 15.0f, 5.0f, 5.0f);
	m_wpParticleComponent.lock()->SetParticleInterval(2.0f);
	m_wpParticleComponent.lock()->SetIsRemove(false);
	m_wpParticleComponent.lock()->SetIsActive(true);
	m_wpParticleComponent.lock()->AddParticle();
}