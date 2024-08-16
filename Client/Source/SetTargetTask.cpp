#include "pch.h"
#include "SetTargetTask.h"

#include "TimerManager.h"
#include "BlackBoardComponent.h"
#include "BehaviorTreeComponent.h"
#include "Actor.h"
using namespace std;

void CSetTargetTask::Initialize()
{
	CBTTaskNode::Initialize();
}

EBTNodeResult CSetTargetTask::UpdateTask()
{
	// 블랙보드 컴포넌트를 불러옵니다.
	shared_ptr<CBlackBoardComponent> spBlackBoardComponent = m_wpBehaviorTreeComponent.lock()->GetBlackBoardComponent();
	FVector3 vDst = spBlackBoardComponent->GetValueAsFVector3(L"Player");
	vDst.y -= vDst.y;

	// 비헤이비어 트리를 소유한 주인 액터를 불러옵니다.
	shared_ptr<CActor> spActor = m_wpBehaviorTreeComponent.lock()->GetOwnerActor().lock();

	// 출발지와 도착지 사이의 거리와 방향을 구합니다.
	FVector3 vSrc = spActor->GetActorWorldPosition();
	vSrc.y -= vSrc.y;

	FVector3 vDir = vDst - vSrc;

	spBlackBoardComponent->SetValueAsFVector3(m_wstrPosKey, vDst);

	vDir.y -= vDir.y;
	D3DXVec3Normalize(&vDir, &vDir);
	spBlackBoardComponent->SetValueAsFVector3(m_wstrDirKey, vDir);

	// 목표를 조준 중인 경우
	m_fSumTargetingTime += CTimerManager::GetInstance()->GetDeltaSeconds(L"TimerInner");
	if (m_fSumTargetingTime < m_fTargetingTime)
	{
		return EBTNodeResult::IN_PROGRESS;
	}

	// 조준이 끝난 경우
	m_fSumTargetingTime = 0.0f;
	return EBTNodeResult::SUCCEEDED;
}

void CSetTargetTask::Release()
{
	CBTTaskNode::Release();
}
