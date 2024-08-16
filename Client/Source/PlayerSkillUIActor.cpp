#include "pch.h"
#include "PlayerSkillUIActor.h"

#include "DeviceManager.h"
#include "RenderManager.h"

#include "EffectComponent.h"
#include <CameraComponent.h>

void CPlayerSkillUIActor::Initialize()
{
	EffectComponentSetting(); // ÀÌÆåÆ® ÄÄÆ÷³ÍÆ® ¼¼ÆÃ

#pragma region Á¤½Ü ÄÚµå

	// UI Å©±â
	m_fSizeX = CFWINCX;
	m_fSizeY = CFWINCY;

	// UI À§Ä¡(ºäÆ÷Æ®)
	m_fX = CFWINCX * 0.5f;
	m_fY = CFWINCY - m_fSizeY * 0.5f;

	SetActorScale({ m_fSizeX,
					m_fSizeY,
					1.f });

	SetActorPosition({ m_fX - CFWINCX * 0.5f, -m_fY + CFWINCY * 0.5f, 1.f });
	//
#pragma endregion

	SetRenderType(ERenderType::ALPHA_BLEND_ORTHOGONAL);
	SetMobility(EMobilityType::DYNAMIC);

	CActor::Initialize();
}

void CPlayerSkillUIActor::BeginPlay()
{
	m_wpEffectComponent.lock()->SetFrameTime(L"Num0", 0, 0, 1000.0f);
	m_wpEffectComponent.lock()->SetFrameTime(L"Num1", 1, 1, 1000.0f);
	m_wpEffectComponent.lock()->SetFrameTime(L"Num2", 2, 2, 1000.0f);
	m_wpEffectComponent.lock()->SetFrameTime(L"Num3", 3, 3, 1000.0f);

	CActor::BeginPlay();
}

int32 CPlayerSkillUIActor::Update(const float& _fDeltaSeconds)
{

	return CActor::Update(_fDeltaSeconds);
}

int32 CPlayerSkillUIActor::LateUpdate(const float& _fDeltaSeconds)
{
	return CActor::LateUpdate(_fDeltaSeconds);
}

void CPlayerSkillUIActor::Render()
{
	CActor::Render();
}

void CPlayerSkillUIActor::EndPlay()
{
	CActor::EndPlay();
}

void CPlayerSkillUIActor::Release()
{
	CActor::Release();
}

void CPlayerSkillUIActor::EffectComponentSetting()
{
	// ÀÌÆåÆ® ÄÄÆ÷³ÍÆ®
	m_wpEffectComponent = CreateActorComponent<CEffectComponent>(L"EffectComponent");
	SetRootComponent(m_wpEffectComponent);
	m_wpEffectComponent.lock()->SettingAnimationInfo(L"Blink0_", 0, 3, L"Num_0", EAnimationType::DESIGNATED_TIME, 0.0f);
	m_wpEffectComponent.lock()->AddState(L"Num_0", 0, 0);
	m_wpEffectComponent.lock()->AddState(L"Num_1", 1, 1);
	m_wpEffectComponent.lock()->AddState(L"Num_2", 2, 2);
	m_wpEffectComponent.lock()->AddState(L"Num_3", 3, 3);
	m_wpEffectComponent.lock()->SetIsAnimate(false);
	m_wpEffectComponent.lock()->SetIsRender(false);
	m_wpEffectComponent.lock()->SetAnimationCount(1);
	m_wpEffectComponent.lock()->SetCurrentAnimationCount(0);
}