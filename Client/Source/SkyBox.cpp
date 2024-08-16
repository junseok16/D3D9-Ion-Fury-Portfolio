#include "pch.h"
#include "SkyBox.h"

#include "Level.h"

#include "PlayerActor.h"
#include "SkyboxComponent.h"

using namespace std;

void CSkyBox::Initialize()
{
	InitializeSkyboxComponent();

	SetRenderType(ERenderType::NON_ALPHA);
	CActor::Initialize();
}

void CSkyBox::BeginPlay()
{
	m_wpPlayerActor = dynamic_pointer_cast<CPlayerActor>(GetLevel().lock()->FindActor(L"Player"));
	CActor::BeginPlay();
}

int32 CSkyBox::Update(const float& _fDeltaSeconds)
{
	m_wpSkyboxComponent.lock()->GetOwnerActor().lock()->SetActorPosition({
		m_wpPlayerActor.lock()->GetActorPosition().x,
		m_wpPlayerActor.lock()->GetActorPosition().y,
		m_wpPlayerActor.lock()->GetActorPosition().z
		});

	return CActor::Update(_fDeltaSeconds);
}

int32 CSkyBox::LateUpdate(const float& _fDeltaSeconds)
{
	return CActor::LateUpdate(_fDeltaSeconds);
}

void CSkyBox::Render()
{
	CActor::Render();
}

void CSkyBox::EndPlay()
{
	CActor::EndPlay();
}

void CSkyBox::Release()
{
	CActor::Release();
}

void CSkyBox::InitializeSkyboxComponent()
{
	m_wpSkyboxComponent = CreateActorComponent<CSkyboxComponent>(L"SkyBoxComponent");
	SetRootComponent(m_wpSkyboxComponent);
	m_wpSkyboxComponent.lock()->SetSkyboxInfo(m_wstrSkyboxFileName, 0, 0);
}
