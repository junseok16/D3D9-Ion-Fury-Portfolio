#include "pch.h"
#include "LoverboyLHActor.h"

#include "AnimationComponent.h"

#include "ResourceManager.h"
#include "InputManager.h"
#include "TimerManager.h"
using namespace std;

void CLoverboyLHActor::Initialize()
{
	m_wpAnimationComponent = CreateActorComponent<CAnimationComponent>(L"AnimationComponent");
	m_wpAnimationComponent.lock()->SetIsRootComponent(true);

	m_wpAnimationComponent.lock()->SetComponentScale({ 5.0f, 5.0f, 5.0f });

	CWeaponLHActor::Initialize();
}

void CLoverboyLHActor::BeginPlay()
{
	CWeaponLHActor::BeginPlay();
}

int32 CLoverboyLHActor::Update(const float& _fDeltaSeconds)
{
	Aiming();

	return CWeaponLHActor::Update(_fDeltaSeconds);
}

int32 CLoverboyLHActor::LateUpdate(const float& _fDeltaSeconds)
{
	return CWeaponLHActor::LateUpdate(_fDeltaSeconds);
}

void CLoverboyLHActor::Render()
{
	CWeaponLHActor::Render();
}

void CLoverboyLHActor::EndPlay()
{
	CWeaponLHActor::EndPlay();
}

void CLoverboyLHActor::Release()
{
	CWeaponLHActor::Release();
}

void CLoverboyLHActor::InputSetting()
{
}

void CLoverboyLHActor::Aiming()
{
	if (CInputManager::GetInstance()->IsMousePressed(EMouseButtonType::RIGHT_BUTTON))
	{
		float fInnerDeltaSeconds = CTimerManager::GetInstance()->GetDeltaSeconds(L"TimerInner");
		FVector3 vRight = GetRightVector();
		FVector3 vUp = GetUpVector();

		if (m_vTranslate.x < 200.f)
		{
			D3DXVec3Normalize(&vRight, &vRight);
			vRight.y -= vRight.y;
			SetActorPosition(GetActorPosition() + vRight * m_fSpeed * fInnerDeltaSeconds * 10.f);

		}
		if (m_vTranslate.y < -350.f)
		{
			D3DXVec3Normalize(&vUp, &vUp);
			SetActorPosition(GetActorPosition() + vUp * m_fSpeed * fInnerDeltaSeconds * 7.f);
		}
	};

	if (CInputManager::GetInstance()->IsMouseReleased(EMouseButtonType::RIGHT_BUTTON))
	{
		float fInnerDeltaSeconds = CTimerManager::GetInstance()->GetDeltaSeconds(L"TimerInner");
		FVector3 vRight = GetRightVector();
		FVector3 vUp = GetUpVector();

		if (m_vTranslate.x > -300.f)
		{
			D3DXVec3Normalize(&vRight, &vRight);
			vRight.y -= vRight.y;
			SetActorPosition(GetActorPosition() - vRight * m_fSpeed * fInnerDeltaSeconds * 10.f);

		}
		if (m_vTranslate.y > -700.f)
		{
			D3DXVec3Normalize(&vUp, &vUp);
			SetActorPosition(GetActorPosition() - vUp * m_fSpeed * fInnerDeltaSeconds * 7.f);
		}
	};
}



