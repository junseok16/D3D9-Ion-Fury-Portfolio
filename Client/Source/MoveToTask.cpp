#include "pch.h"
#include "MoveToTask.h"

#include "TimerManager.h"
#include "BlackBoardComponent.h"
#include "BehaviorTreeComponent.h"
#include "Actor.h"
#include "Monster.h"
using namespace std;

void CMoveToTask::Initialize()
{
	CBTTaskNode::Initialize();
}

void CMoveToTask::Release()
{
	CBTTaskNode::Release();
}

EBTNodeResult CMoveToTask::UpdateTask()
{
	// 블랙보드 컴포넌트를 불러옵니다.
	shared_ptr<CBlackBoardComponent> spBlackBoardComponent = m_wpBehaviorTreeComponent.lock()->GetBlackBoardComponent();
	FVector3 vDst = spBlackBoardComponent->GetValueAsFVector3(m_wstrDstKey);
	vDst.y -= vDst.y;

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
		spBlackBoardComponent->SetValueAsFVector3(m_wstrSrcKey, spActor->GetActorWorldPosition());

		// 몬스터의 이동이 끝나면 상태를 IDLE로 업데이트합니다.
		if (spActor->GetActorLayer().find(L"Monster") != spActor->GetActorLayer().end())
			dynamic_pointer_cast<CMonster>(spActor)->SetMonsterState((int32)EMonsterState::ATTACK);

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
