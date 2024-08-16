// default
#include "pch.h"
#include "WallLaser.h"

// actor
#include "PlayerActor.h"

// manager
#include "CollisionManager.h"
#include "TimerManager.h"

// component
#include "CubeColliderComponent.h"
#include "AnimationComponent.h"
using namespace std;

void CWallLaser::Initialize()
{
	// 애니메이션 컴포넌트
	m_wpAnimationComponent = CreateActorComponent<CAnimationComponent>(L"AnimationComponent");
	m_wpAnimationComponent.lock()->SettingAnimationInfo(L"Laser1_0", 0, 7, L"Idle", EAnimationType::LOOP, 1.0f);
	SetRootComponent(m_wpAnimationComponent);

	// 큐브 콜라이더 컴포넌트
	m_wpCubeColliderComponent = CreateActorComponent<CCubeColliderComponent>(L"CubeColliderComponent");
	m_wpCubeColliderComponent.lock()->SetCollisionLayerType(ECollisionLayerType::MONSTER);
	m_wpCubeColliderComponent.lock()->AddCollisionLayer(ECollisionLayerType::PLAYER);
	m_wpCubeColliderComponent.lock()->SetOwnerComponent(m_wpAnimationComponent);
	CCollisionManager::GetInstance()->AddColliderComponent(m_wpCubeColliderComponent.lock());

	SetRenderType(ERenderType::ALPHA_TEST);

	if (m_eLaserMovementType == ELaserMovementType::STATIC) { SetMobility(EMobilityType::STATIC); }
	else { SetMobility(EMobilityType::DYNAMIC); }
	CCubeColliderActor::Initialize();
}

void CWallLaser::BeginPlay()
{
	m_wpAnimationComponent.lock()->AddState(L"Idle", 0, 7);
	m_wpAnimationComponent.lock()->SetCurrentState(L"Idle");
	CCubeColliderActor::BeginPlay();
}

int32 CWallLaser::Update(const float& _fDeltaSeconds)
{
	float fDeltaSeconds = CTimerManager::GetInstance()->GetDeltaSeconds(L"TimerInner");
	m_fSumMovementTime += fDeltaSeconds;

	if (m_fSumMovementTime >= m_fMovementTime)
	{
		m_vUp *= -1;
		m_vRight *= -1;
		m_fSumMovementTime = 0.0f;
	}

	// 이동하는 레이저인 경우
	switch (m_eLaserMovementType)
	{
	case ELaserMovementType::VERTICAL: m_vTranslate += m_vUp * m_fSpeed * fDeltaSeconds; break;
	case ELaserMovementType::HORIZONTAL: m_vTranslate += m_vRight * m_fSpeed * fDeltaSeconds; break;
	default: break;
	}

	return CCubeColliderActor::Update(_fDeltaSeconds);
}

int32 CWallLaser::LateUpdate(const float& _fDeltaSeconds)
{
	return CCubeColliderActor::LateUpdate(_fDeltaSeconds);
}

void CWallLaser::Render()
{
	CCubeColliderActor::Render();
}

void CWallLaser::EndPlay()
{
	CCubeColliderActor::EndPlay();
}

void CWallLaser::Release()
{
	CCubeColliderActor::Release();
}

int32 CWallLaser::OnCollisionEnter(std::weak_ptr<CColliderComponent> _wpSrcCollider, std::weak_ptr<CColliderComponent> _wpDstCollider)
{
	// 플레이어와 충돌한 경우, 체력을 감소시킵니다.
	if (_wpDstCollider.lock()->GetCollisionLayerType() == ECollisionLayerType::PLAYER)
	{
		dynamic_pointer_cast<CPlayerActor>(_wpDstCollider.lock()->GetOwnerActor().lock())->GetDamaged(m_fDamage);
	}

	return 0;
}
