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
	// ������ ������Ʈ�� �ҷ��ɴϴ�.
	shared_ptr<CBlackBoardComponent> spBlackBoardComponent = m_wpBehaviorTreeComponent.lock()->GetBlackBoardComponent();
	FVector3 m_vDst = spBlackBoardComponent->GetValueAsFVector3(m_wstrKey);
	m_vDst.y -= m_vDst.y;

	// �����̺�� Ʈ���� ������ ���� ���͸� �ҷ��ɴϴ�.
	shared_ptr<CActor> spActor = m_wpBehaviorTreeComponent.lock()->GetOwnerActor().lock();

	m_fSumFireInterval += CTimerManager::GetInstance()->GetDeltaSeconds(L"TimerInner");
	if (m_fSumFireInterval >= m_fFireInterval)
	{
		m_fSumFireInterval = 0.0f;

		// TODO: BOSS BULLET�� �����մϴ�.
		// spActor->GetLevel().lock()->CreateActor<CBossBullet>(L"BossBullet", L"Projectile", L"Actor");
		++m_iSumBullets;
	}

	// �߻��� ����ü�� ������ �߻��ؾ��� �������� ���� ���
	if (m_iSumBullets < m_iBullets)
	{
		return EBTNodeResult::IN_PROGRESS;
	}
	m_iSumBullets = 0;
	return EBTNodeResult::SUCCEEDED;
}
