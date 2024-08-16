#include "pch.h"
#include "WaitTask.h"

#include "Actor.h"
#include "Monster.h"

#include "TimerManager.h"
#include "BlackBoardComponent.h"
#include "BehaviorTreeComponent.h"
using namespace std;

void CWaitTask::Initialize()
{
	CBTTaskNode::Initialize();
}

void CWaitTask::Release()
{
	CBTTaskNode::Release();
}

EBTNodeResult CWaitTask::UpdateTask()
{
	// 블랙보드 컴포넌트를 불러옵니다.
	shared_ptr<CBlackBoardComponent> spBlackBoardComponent = m_wpBehaviorTreeComponent.lock()->GetBlackBoardComponent();

	// 비헤이비어 트리를 소유한 주인 액터를 불러옵니다.
	shared_ptr<CActor> spActor = m_wpBehaviorTreeComponent.lock()->GetOwnerActor().lock();

	m_fSumWaitTime += CTimerManager::GetInstance()->GetDeltaSeconds(L"TimerInner");
	if (m_fSumWaitTime >= m_fWaitTime)
	{
		m_fSumWaitTime = 0.0f;
		return EBTNodeResult::SUCCEEDED;
	}

	return EBTNodeResult::IN_PROGRESS;
}