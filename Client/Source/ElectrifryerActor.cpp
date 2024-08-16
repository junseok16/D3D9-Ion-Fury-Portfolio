#include "pch.h"
#include "ElectrifryerActor.h"

#include "RenderManager.h"
#include "TimerManager.h"
#include "InputManager.h"

#include "AnimationComponent.h"

using namespace std;

void CElectrifryerActor::Initialize()
{
	m_eWeaponType = EWeaponType::ELECTRIFRYER;

	m_vBasePosition = { 50.0f, -150.0f, 5.0f };

	m_iDamage = 0;
	m_iBulletLoaded = 0;
	m_iBulletHolding = 0;
	m_iMagazine = 0;
	m_iBulletMaximum = 0;

	m_wpAnimationComponent = CreateActorComponent<CAnimationComponent>(L"AnimationComponent");
	m_wpAnimationComponent.lock()->SetIsRootComponent(true);
	m_wpAnimationComponent.lock()->SettingAnimationInfo(L"Electrifryer_", 0, 23, L"Idle", EAnimationType::LOOP, 1.0f);
	
	m_wpAnimationComponent.lock()->SetComponentScale({ 9.0f, 9.0f, 9.0f });

	CWeaponActor::Initialize();
}

void CElectrifryerActor::BeginPlay()
{
	m_wpAnimationComponent.lock()->AddState(L"Idle", 0, 7);
	m_wpAnimationComponent.lock()->AddState(L"Attack1", 8, 19);
	m_wpAnimationComponent.lock()->AddState(L"Attack2", 20, 23);

	m_wpAnimationComponent.lock()->SetFrameTime(L"Idle", 0, 1, 1.f);
	m_wpAnimationComponent.lock()->SetFrameTime(L"Idle", 1, 7, 0.05f);
	m_wpAnimationComponent.lock()->SetFrameTime(L"Attack1", 8, 19, 0.05f);
	m_wpAnimationComponent.lock()->SetFrameTime(L"Attack1", 15, 16, 0.1f);
	m_wpAnimationComponent.lock()->SetFrameTime(L"Attack2", 20, 23, 0.06f);

	CWeaponActor::BeginPlay();
}

int32 CElectrifryerActor::Update(const float& _fDeltaSeconds)
{
	if (m_bEnable)
	{
		Input();
	}

	return CWeaponActor::Update(_fDeltaSeconds);
}

int32 CElectrifryerActor::LateUpdate(const float& _fDeltaSeconds)
{
	UpdateFSM();
	return CWeaponActor::LateUpdate(_fDeltaSeconds);
}

void CElectrifryerActor::Render()
{
	CWeaponActor::Render();
}

void CElectrifryerActor::EndPlay()
{
	CWeaponActor::EndPlay();
}

void CElectrifryerActor::Release()
{
	CWeaponActor::Release();
}

void CElectrifryerActor::Input()
{
	if (m_wpAnimationComponent.lock()->GetCurrentState() == L"Attack1")			// 사격
	{
		m_wpAnimationComponent.lock()->SetAnimationType(EAnimationType::DESIGNATED_TIME);
		m_wpAnimationComponent.lock()->SetAnimationCount(1);
	}
	if (m_wpAnimationComponent.lock()->GetCurrentState() == L"Attack2")			// 보조사격
	{
		m_wpAnimationComponent.lock()->SetAnimationType(EAnimationType::LOOP);
	}

	if (CInputManager::GetInstance()->IsMouseReleased(EMouseButtonType::RIGHT_BUTTON) && m_wpAnimationComponent.lock()->GetCurFrame() == 23)
	{
		m_wpAnimationComponent.lock()->SetCurrentState(L"Idle");
	}
}

void CElectrifryerActor::UpdateFSM()
{
	std::shared_ptr<CAnimationComponent> wpAnimation = m_wpAnimationComponent.lock();

	if (0 < wpAnimation->GetCurrentAnimationCount())
	{
		if (0 < wpAnimation->GetCurrentAnimationCount() && wpAnimation->GetCurrentState() == L"Attack1")	// 어택과 리로드는 루프이더라도 아이들로 초기화
		{
			wpAnimation->SetCurrentState(L"Idle");
			wpAnimation->SetAnimationType(EAnimationType::LOOP);
			wpAnimation->SetCurrentAnimationCount(0);
			wpAnimation->SetCurFrame(wpAnimation->GetStateFrame(L"Idle").first);
			wpAnimation->SetIsAnimate(true);
			SetActivate(true);
		}
	}
}