#include "pch.h"
#include "FireStraightGunTask.h"

#include "TimerManager.h"
#include "BlackBoardComponent.h"
#include "BehaviorTreeComponent.h"
#include "Actor.h"

#include "BossBullet.h"
#include "Level.h"
using namespace std;

void CFireStraightGunTask::Initialize()
{
	CBTTaskNode::Initialize();
}

void CFireStraightGunTask::Release()
{
	CBTTaskNode::Release();
}

EBTNodeResult CFireStraightGunTask::UpdateTask()
{
	// 블랙보드 컴포넌트를 불러옵니다.
	shared_ptr<CBlackBoardComponent> spBlackBoardComponent = m_wpBehaviorTreeComponent.lock()->GetBlackBoardComponent();
	FVector3 m_vDst = spBlackBoardComponent->GetValueAsFVector3(m_wstrKey);
	m_vDst.y -= m_vDst.y;

	// 비헤이비어 트리를 소유한 주인 액터를 불러옵니다.
	shared_ptr<CActor> spActor = m_wpBehaviorTreeComponent.lock()->GetOwnerActor().lock();

	m_fSumFireInterval += CTimerManager::GetInstance()->GetDeltaSeconds(L"TimerInner");
	if (m_fSumFireInterval >= m_fFireInterval)
	{
		m_fSumFireInterval = 0.0f;

		// TODO: BOSS BULLET을 생성합니다.
		// spActor->GetLevel().lock()->CreateActor<CBossBullet>(L"BossBullet", L"Projectile", L"Actor");
		++m_iSumBullets;
	}

	// 발사한 투사체의 개수가 발사해야할 개수보다 적은 경우
	if (m_iSumBullets < m_iBullets)
	{
		return EBTNodeResult::IN_PROGRESS;
	}
	m_iSumBullets = 0;
	return EBTNodeResult::SUCCEEDED;
}
