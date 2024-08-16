#include "pch.h"
#include "EffectActor.h"

#include "TimerManager.h"
#include "CollisionManager.h"
#include "RenderManager.h"

#include "Level.h"

#include "EffectComponent.h"
using namespace std;

void CEffectActor::Initialize()
{
	// 사각형 컴포넌트
	m_wpEffectComponent = CreateActorComponent<CEffectComponent>(L"EffectComponent");
	SetRootComponent(m_wpEffectComponent.lock());
	m_wpEffectComponent.lock()->SettingAnimationInfo(L"Explosion0_0", 0, 64, L"Idle", EAnimationType::DESIGNATED_TIME, 1.0f);
	m_wpEffectComponent.lock()->SetIsRootComponent(true);
	m_wpEffectComponent.lock()->AddState(L"Idle", 0, 64);

	CActor::Initialize();
}

void CEffectActor::BeginPlay()
{
	CActor::BeginPlay();
}

int32 CEffectActor::Update(const float& _fDeltaSeconds)
{
	return CActor::Update(_fDeltaSeconds);
}

int32 CEffectActor::LateUpdate(const float& _fDeltaSeconds)
{
	return CActor::LateUpdate(_fDeltaSeconds);
}

void CEffectActor::Render()
{
	CActor::Render();
}

void CEffectActor::EndPlay()
{
	CActor::EndPlay();
}

void CEffectActor::Release()
{
	CActor::Release();
}

void CEffectActor::RemoveSelf()
{
	/*if (m_wpEffectComponent.lock()->GetDeadTime() <= m_wpEffectComponent.lock()->GetLifeTime())
	{
		CRenderManager::GetInstance()->RemoveActor(m_eRenderType, dynamic_pointer_cast<CActor>(shared_from_this()));
		GetLevel().lock()->RemoveActor(m_wstrActorName);
	}*/
}
