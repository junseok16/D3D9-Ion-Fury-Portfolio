// Default
#include "pch.h"
#include "BossFireGunTask.h"

// Manager
#include "TimerManager.h"

// Component
#include "BlackBoardComponent.h"
#include "BehaviorTreeComponent.h"

// Framework
#include "Level.h"
#include "Actor.h"

// Client
#include "WarmechBullet.h"
using namespace std;

int32 CBossFireGunTask::s_iBulletCounter = 0;

void CBossFireGunTask::Initialize()
{
	CBTTaskNode::Initialize();
}

void CBossFireGunTask::Release()
{
	CBTTaskNode::Release();
}

EBTNodeResult CBossFireGunTask::UpdateTask()
{
	// 블랙보드 컴포넌트를 불러옵니다.
	shared_ptr<CBlackBoardComponent> spBlackBoardComponent = m_wpBehaviorTreeComponent.lock()->GetBlackBoardComponent();

	// 플레이어 위치를 구합니다.
	FVector3 vDst = spBlackBoardComponent->GetValueAsFVector3(m_wstrTargetKey);
	vDst.y -= vDst.y;

	// 비헤이비어 트리를 소유한 주인 액터를 불러옵니다.
	shared_ptr<CActor> spActor = m_wpBehaviorTreeComponent.lock()->GetOwnerActor().lock();

	// 보스에서 플레이어로 향하는 방향 벡터를 구합니다.
	FVector3 vDir = vDst - spActor->GetActorWorldPosition();
	D3DXVec3Normalize(&vDir, &vDir);

	FVector3 vUp = { 0.0f, 1.0f, 0.0f };
	FVector3 vBulletPos;
	D3DXVec3Cross(&vBulletPos, &vDir, &vUp);

	switch (m_eGunFireType)
	{
	// 직선 탄을 생성합니다.
	case EGunFireType::STRAIGHT:
	{
		m_fSumFireInterval += CTimerManager::GetInstance()->GetDeltaSeconds(L"TimerInner");
		if (m_fSumFireInterval >= m_fFireInterval)
		{
			shared_ptr<CWarmechBullet> spBossBullet = spActor->GetLevel().lock()->CreateActor<CWarmechBullet>(L"BossBullet" + to_wstring(s_iBulletCounter++), L"Projectile", L"Actor");
			spBossBullet->SetActorPosition(spActor->GetActorPosition() + 20.0f * vBulletPos);
			spBossBullet->SetTarget(nullptr);
			spBossBullet->SetDamage(m_fDamage);
			spBossBullet->SetSpeed(m_fSpeed);
			spBossBullet->Initialize();
			spBossBullet->BeginPlay();

			m_fSumFireInterval = 0.0f;
			++m_iSumBullets;
		}

		// 발사한 투사체의 개수가 발사해야할 개수보다 적은 경우
		if (m_iSumBullets < m_iBullets)
		{
			return EBTNodeResult::IN_PROGRESS;
		}

		m_fSumFireInterval = 0.0f;
		m_iSumBullets = 0;
		return EBTNodeResult::SUCCEEDED;
	}
	break;

	// 방사 탄을 생성합니다.
	case EGunFireType::ROUND:
	{
		
	}
	break;

	default: break;
	}
}
