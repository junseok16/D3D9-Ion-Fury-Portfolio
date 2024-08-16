#include "pch.h"
#include "RushToTask.h"

#include "TimerManager.h"
#include "BlackBoardComponent.h"
#include "BehaviorTreeComponent.h"
#include "Actor.h"
using namespace std;

void CRushToTask::Initialize()
{
	CBTTaskNode::Initialize();
}

EBTNodeResult CRushToTask::UpdateTask()
{
	// 블랙보드 컴포넌트를 불러옵니다.
	shared_ptr<CBlackBoardComponent> spBlackBoardComponent = m_wpBehaviorTreeComponent.lock()->GetBlackBoardComponent();
	FVector3 vDst = spBlackBoardComponent->GetValueAsFVector3(m_wstrPosKey);

	// 비헤이비어 트리를 소유한 주인 액터를 불러옵니다.
	shared_ptr<CActor> spActor = m_wpBehaviorTreeComponent.lock()->GetOwnerActor().lock();

	// 출발지와 도착지 사이의 거리와 방향을 구합니다.
	FVector3 vSrc = spActor->GetActorWorldPosition();
	vSrc.y -= vSrc.y;

	FVector3 vLength = vDst - vSrc;
	FVector3 vDir = vDst - vSrc;

	// 출발지와 도착지 사이의 거리가 반지름보다 작은 경우
	if (D3DXVec3Length(&vLength) <= m_fRadius)
	{
		return EBTNodeResult::SUCCEEDED;
	}

	vDir.y -= vDir.y;
	D3DXVec3Normalize(&vDir, &vDir);
	spBlackBoardComponent->SetValueAsFVector3(m_wstrDirKey, vDir);

	// 액터를 이동합니다.
	float fDeltaSeconds = CTimerManager::GetInstance()->GetDeltaSeconds(L"TimerInner");
	spActor->SetActorPosition(spActor->GetActorPosition() + vDir * m_fSpeed * fDeltaSeconds);

	return EBTNodeResult::IN_PROGRESS;
}

void CRushToTask::Release()
{
	CBTTaskNode::Release();
}
