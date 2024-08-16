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
	// ������ ������Ʈ�� �ҷ��ɴϴ�.
	shared_ptr<CBlackBoardComponent> spBlackBoardComponent = m_wpBehaviorTreeComponent.lock()->GetBlackBoardComponent();
	FVector3 vDst = spBlackBoardComponent->GetValueAsFVector3(m_wstrDstKey);
	vDst.y -= vDst.y;

	// �����̺�� Ʈ���� ������ ���� ���͸� �ҷ��ɴϴ�.
	shared_ptr<CActor> spActor = m_wpBehaviorTreeComponent.lock()->GetOwnerActor().lock();

	// ������� ������ ������ �Ÿ��� ������ ���մϴ�.
	FVector3 vSrc = spActor->GetActorWorldPosition();
	vSrc.y -= vSrc.y;

	FVector3 vLength = vDst - vSrc;
	FVector3 vDir = vDst - vSrc;

	// ������� ������ ������ �Ÿ��� ���������� ���� ���
	if (D3DXVec3Length(&vLength) <= m_fRadius)
	{
		spBlackBoardComponent->SetValueAsFVector3(m_wstrSrcKey, spActor->GetActorWorldPosition());

		// ������ �̵��� ������ ���¸� IDLE�� ������Ʈ�մϴ�.
		if (spActor->GetActorLayer().find(L"Monster") != spActor->GetActorLayer().end())
			dynamic_pointer_cast<CMonster>(spActor)->SetMonsterState((int32)EMonsterState::ATTACK);

		return EBTNodeResult::SUCCEEDED;
	}

	vDir.y -= vDir.y;
	D3DXVec3Normalize(&vDir, &vDir);
	spBlackBoardComponent->SetValueAsFVector3(m_wstrDirKey, vDir);

	// ���͸� �̵��մϴ�.
	float fDeltaSeconds = CTimerManager::GetInstance()->GetDeltaSeconds(L"TimerInner");
	spActor->SetActorPosition(spActor->GetActorPosition() + vDir * m_fSpeed * fDeltaSeconds);

	return EBTNodeResult::IN_PROGRESS;
}
