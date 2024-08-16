#include "pch.h"
#include "PlayerEffectActor.h"

#include "DeviceManager.h"
#include "RenderManager.h"

#include "Level.h"
#include "PlayerActor.h"

#include "EffectComponent.h"
#include <CameraComponent.h>

void CPlayerEffectActor::Initialize()
{
	EffectComponentSetting();

#pragma region 정쌤 코드
	// 
	// D3DXMatrixIdentity(&m_ViewMatrix);
	// D3DXMatrixOrthoLH(&m_ProjMatrix, WINCX, WINCY, 0, 1.0f);

	// UI 크기
	m_fSizeX = CFWINCX;
	m_fSizeY = CFWINCY;

	// UI 위치(뷰포트)
	m_fX = CFWINCX * 0.5f;
	m_fY = CFWINCY - m_fSizeY * 0.5f;

	SetActorScale({ m_fSizeX, m_fSizeY, 1.f });

	SetActorPosition({ m_fX - CFWINCX * 0.5f, -m_fY + CFWINCY * 0.5f, 1.f });
	//
#pragma endregion

	SetOwnerActor(GetLevel().lock()->FindActor(L"Player"));
	SetRenderType(ERenderType::ALPHA_BLEND_ORTHOGONAL);
	SetMobility(EMobilityType::DYNAMIC);

	CActor::Initialize();
}

void CPlayerEffectActor::BeginPlay()
{
	m_wpFullScreenEffectComponent.lock()->SetFrameTime(L"PlayerHitted", 11, 12, 0.5f);
	m_wpFullScreenEffectComponent.lock()->SetFrameTime(L"LockOn", 13, 13, 1000.0f);
	m_wpFullScreenEffectComponent.lock()->SetFrameTime(L"Sandevistan", 16, 16, 1000.0f);

	CActor::BeginPlay();
}

int32 CPlayerEffectActor::Update(const float& _fDeltaSeconds)
{
	if (m_bIsHitted || m_bIsRecall || m_bIsBlink || m_bIsLockOn || m_bIsSandevistan)
	{
		m_wpFullScreenEffectComponent.lock()->SetIsAnimate(true);
		m_wpFullScreenEffectComponent.lock()->SetIsRender(true);
	}
	else
	{
		m_wpFullScreenEffectComponent.lock()->SetIsAnimate(false);
		m_wpFullScreenEffectComponent.lock()->SetIsRender(false);
	}

	if (m_bIsRecall)
	{
		RecallCheck();
	}
	if (m_bIsHitted)
	{
		HittedCheck(_fDeltaSeconds);
	}
	if (m_bIsBlink)
	{
		BlinkCheck();
	}
	if (m_bIsLockOn)
	{
		LockOnCheck();
	}
	if (m_bIsSandevistan)
	{
		SandevistanCheck();
	}

	CheckBlinkCount();
	CheckSkillCoolTime();

	return CActor::Update(_fDeltaSeconds);
}

int32 CPlayerEffectActor::LateUpdate(const float& _fDeltaSeconds)
{
	return CActor::LateUpdate(_fDeltaSeconds);
}

void CPlayerEffectActor::Render()
{
	CActor::Render();
}

void CPlayerEffectActor::EndPlay()
{
	CActor::EndPlay();
}

void CPlayerEffectActor::Release()
{
	CActor::Release();
}

void CPlayerEffectActor::HittedCheck(const float& _fDeltaSeconds)
{
	m_wpFullScreenEffectComponent.lock()->SetCurrentState(L"PlayerHitted");
	m_fHittedEffectTime += _fDeltaSeconds;

	// 피격이펙트 지속시간이 1초가 지나면 꺼줍니다.
	if (1.0f < m_fHittedEffectTime)
	{
		m_bIsHitted = false;
		m_fHittedEffectTime = 0.0f;
		m_wpFullScreenEffectComponent.lock()->SetIsAnimate(false);
		m_wpFullScreenEffectComponent.lock()->SetIsRender(false);
	}
}

void CPlayerEffectActor::RecallCheck()
{
	// 리콜 이펙트 on
	m_wpFullScreenEffectComponent.lock()->SetAnimationCount(1);
	m_wpFullScreenEffectComponent.lock()->SetCurrentAnimationCount(0);
	m_wpFullScreenEffectComponent.lock()->SetCurrentState(L"Recall");
}

void CPlayerEffectActor::BlinkCheck()
{
	// 블링크 이펙트 on
	m_wpFullScreenEffectComponent.lock()->SetAnimationCount(1);
	m_wpFullScreenEffectComponent.lock()->SetCurrentAnimationCount(0);
	m_wpFullScreenEffectComponent.lock()->SetCurrentState(L"Blink");
}

void CPlayerEffectActor::LockOnCheck()
{
	// 자동조준 이펙트 on
	m_wpFullScreenEffectComponent.lock()->SetAnimationCount(1);
	m_wpFullScreenEffectComponent.lock()->SetCurrentAnimationCount(0);
	m_wpFullScreenEffectComponent.lock()->SetCurrentState(L"LockOn");
}

void CPlayerEffectActor::SandevistanCheck()
{
	// 싼데비스탄 이펙트 on
	m_wpFullScreenEffectComponent.lock()->SetAnimationCount(1);
	m_wpFullScreenEffectComponent.lock()->SetCurrentAnimationCount(0);
	m_wpFullScreenEffectComponent.lock()->SetCurrentState(L"Sandevistan");
}

void CPlayerEffectActor::EffectComponentSetting()
{
	// 전체화면 이펙트 컴포넌트
	m_wpFullScreenEffectComponent = CreateActorComponent<CEffectComponent>(L"FullScreenEffectComponent");
	SetRootComponent(m_wpFullScreenEffectComponent);
	m_wpFullScreenEffectComponent.lock()->SettingAnimationInfo(L"SkillEffect0_0", 0, 16, L"PlayerHitted", EAnimationType::DESIGNATED_TIME, 2.0f);
	m_wpFullScreenEffectComponent.lock()->AddState(L"Idle", 9, 9);
	m_wpFullScreenEffectComponent.lock()->AddState(L"Recall", 0, 7);
	m_wpFullScreenEffectComponent.lock()->AddState(L"PlayerHitted", 11, 12);
	m_wpFullScreenEffectComponent.lock()->AddState(L"Blink", 8, 10);
	m_wpFullScreenEffectComponent.lock()->AddState(L"LockOn", 13, 13);
	m_wpFullScreenEffectComponent.lock()->AddState(L"Sandevistan", 16, 16);
	m_wpFullScreenEffectComponent.lock()->SetIsAnimate(false);
	m_wpFullScreenEffectComponent.lock()->SetIsRender(false);

	// 점멸 개수 이펙트 컴포넌트
	m_wpBlinkCountEffectComponent = CreateActorComponent<CEffectComponent>(L"BlinkCountEffectComponent");
	m_wpBlinkCountEffectComponent.lock()->SetIsRootComponent(true);
	m_wpBlinkCountEffectComponent.lock()->SettingAnimationInfo(L"Blink0_0", 0, 3, L"Count_0", EAnimationType::DESIGNATED_TIME, 0.0f);
	m_wpBlinkCountEffectComponent.lock()->AddState(L"Count_0", 0, 0);
	m_wpBlinkCountEffectComponent.lock()->AddState(L"Count_1", 1, 1);
	m_wpBlinkCountEffectComponent.lock()->AddState(L"Count_2", 2, 2);
	m_wpBlinkCountEffectComponent.lock()->AddState(L"Count_3", 3, 3);
	m_wpBlinkCountEffectComponent.lock()->SetComponentLocalPosition({ 0.0f, -0.072f, 0.0f });
	m_wpBlinkCountEffectComponent.lock()->SetIsAnimate(false);
	m_wpBlinkCountEffectComponent.lock()->SetIsRender(true);

	// 점멸 아이콘 컴포넌트
	m_wpBlinkIconEffectComponent = CreateActorComponent<CEffectComponent>(L"BlinkIconEffectComponent");
	m_wpBlinkIconEffectComponent.lock()->SetIsRootComponent(true);
	m_wpBlinkIconEffectComponent.lock()->SettingAnimationInfo(L"BlinkIcon0_0", 0, 0, L"BlinkIcon", EAnimationType::DESIGNATED_TIME, 0.0f);
	m_wpBlinkIconEffectComponent.lock()->AddState(L"BlinkIcon", 0, 0);
	m_wpBlinkIconEffectComponent.lock()->SetComponentLocalPosition({ 0.30f, -0.32f, 0.0f });
	m_wpBlinkIconEffectComponent.lock()->SetComponentScale({ 64.0f / CFWINCX, 64.0f / CFWINCY, -10.0f });
	m_wpBlinkIconEffectComponent.lock()->SetIsAnimate(false);
	m_wpBlinkIconEffectComponent.lock()->SetIsRender(true);

	// 점멸 아이콘 쿨타임 컴포넌트
	m_wpBlinkCoolTimeIconEffectComponent = CreateActorComponent<CEffectComponent>(L"BlinkCoolTimeIconEffectComponent");
	m_wpBlinkCoolTimeIconEffectComponent.lock()->SetIsRootComponent(true);
	m_wpBlinkCoolTimeIconEffectComponent.lock()->SettingAnimationInfo(L"BlinkIcon1_0", 0, 0, L"BlinkCoolTimeIcon", EAnimationType::DESIGNATED_TIME, 0.0f);
	m_wpBlinkCoolTimeIconEffectComponent.lock()->AddState(L"BlinkCoolTimeIcon", 0, 0);
	m_wpBlinkCoolTimeIconEffectComponent.lock()->SetComponentLocalPosition({ 0.30f, -0.32f, 0.0f });
	m_wpBlinkCoolTimeIconEffectComponent.lock()->SetComponentScale({ 64.0f / CFWINCX, 64.0f / CFWINCY, 0.0f });
	m_wpBlinkCoolTimeIconEffectComponent.lock()->SetIsAnimate(false);
	m_wpBlinkCoolTimeIconEffectComponent.lock()->SetIsRender(true);

	// 시간역행 아이콘 컴포넌트
	m_wpRecallIconEffectComponent = CreateActorComponent<CEffectComponent>(L"RecallIconEffectComponent");
	m_wpRecallIconEffectComponent.lock()->SetIsRootComponent(true);
	m_wpRecallIconEffectComponent.lock()->SettingAnimationInfo(L"Recall0_0", 0, 0, L"RecallIcon", EAnimationType::DESIGNATED_TIME, 0.0f);
	m_wpRecallIconEffectComponent.lock()->AddState(L"RecallIcon", 0, 0);
	m_wpRecallIconEffectComponent.lock()->SetComponentLocalPosition({ 0.36f, -0.32f, 0.0f });
	m_wpRecallIconEffectComponent.lock()->SetComponentScale({ 64.0f / CFWINCX, 64.0f / CFWINCY, 10.0f });
	m_wpRecallIconEffectComponent.lock()->SetIsAnimate(false);
	m_wpRecallIconEffectComponent.lock()->SetIsRender(true);

	// 시간역행 아이콘 쿨타임 컴포넌트
	m_wpRecallCoolTimeIconEffectComponent = CreateActorComponent<CEffectComponent>(L"RecallCoolTimeIconEffectComponent");
	m_wpRecallCoolTimeIconEffectComponent.lock()->SetIsRootComponent(true);
	m_wpRecallCoolTimeIconEffectComponent.lock()->SettingAnimationInfo(L"Recall1_0", 0, 0, L"RecallCoolTimeIcon", EAnimationType::DESIGNATED_TIME, 0.0f);
	m_wpRecallCoolTimeIconEffectComponent.lock()->AddState(L"RecallCoolTimeIcon", 0, 0);
	m_wpRecallCoolTimeIconEffectComponent.lock()->SetComponentLocalPosition({ 0.36f, -0.32f, 0.0f });
	m_wpRecallCoolTimeIconEffectComponent.lock()->SetComponentScale({ 64.0f / CFWINCX, 64.0f / CFWINCY, 0.0f });
	m_wpRecallCoolTimeIconEffectComponent.lock()->SetIsAnimate(false);
	m_wpRecallCoolTimeIconEffectComponent.lock()->SetIsRender(true);
}

void CPlayerEffectActor::CheckBlinkCount()
{
	int32 iBlinkCount = dynamic_pointer_cast<CPlayerActor>(GetOwnerActor().lock())->GetBlinkCount();

	switch (iBlinkCount)
	{
	case 0:
	{
		m_wpBlinkCountEffectComponent.lock()->SetCurFrame(0);
		break;
	}
	case 1:
	{
		m_wpBlinkCountEffectComponent.lock()->SetCurFrame(1);
		break;
	}
	case 2:
	{
		m_wpBlinkCountEffectComponent.lock()->SetCurFrame(2);
		break;
	}
	case 3:
	{
		m_wpBlinkCountEffectComponent.lock()->SetCurFrame(3);
		break;
	}
	}
}

void CPlayerEffectActor::CheckSkillCoolTime()
{
	// 점멸
	float fBlinkCoolTime = dynamic_pointer_cast<CPlayerActor>(GetOwnerActor().lock())->GetBlinkCoolTime();
	float fBlinkCoolRecovery = dynamic_pointer_cast<CPlayerActor>(GetOwnerActor().lock())->GetBlinkCoolRecovery();

	m_wpBlinkIconEffectComponent.lock()->SetTextureUV(1.0f, fBlinkCoolRecovery / fBlinkCoolTime);

	if(fBlinkCoolRecovery >= fBlinkCoolTime)
		m_wpBlinkIconEffectComponent.lock()->SetTextureUV(1.0f, 1.0f);

	// 시간역행
	float fRecallCoolTime = dynamic_pointer_cast<CPlayerActor>(GetOwnerActor().lock())->GetRecallCoolTime();
	float fRecallCoolRecovery = dynamic_pointer_cast<CPlayerActor>(GetOwnerActor().lock())->GetRecallCoolRecovery();

	m_wpRecallIconEffectComponent.lock()->SetTextureUV(1.0f, fRecallCoolRecovery / fRecallCoolTime);

	if (fRecallCoolRecovery >= fRecallCoolTime)
		m_wpRecallIconEffectComponent.lock()->SetTextureUV(1.0f, 1.0f);
}
