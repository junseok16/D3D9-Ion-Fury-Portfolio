#include "pch.h"
#include "FlyingTask.h"

#include "TimerManager.h"
#include "BlackBoardComponent.h"
#include "BehaviorTreeComponent.h"
#include "Actor.h"
#include "Monster.h"
using namespace std;

void CFlyingTask::Initialize()
{
	CBTTaskNode::Initialize();
}

void CFlyingTask::Release()
{
	CBTTaskNode::Release();
}

EBTNodeResult CFlyingTask::UpdateTask()
{
	// ������ ������Ʈ�� �ҷ��ɴϴ�.
	shared_ptr<CBlackBoardComponent> spBlackBoardComponent = m_wpBehaviorTreeComponent.lock()->GetBlackBoardComponent();
	FVector3 m_vDst = spBlackBoardComponent->GetValueAsFVector3(m_wstrKey);
	m_vDst.y -= m_vDst.y;

	// �����̺�� Ʈ���� ������ ���� ���͸� �ҷ��ɴϴ�.
	shared_ptr<CActor> spActor = m_wpBehaviorTreeComponent.lock()->GetOwnerActor().lock();

	// ������� ������ ������ �Ÿ��� ������ ���մϴ�.
	FVector3 vSrc = spActor->GetActorWorldPosition();
	vSrc.y -= vSrc.y;

	FVector3 vLength = m_vDst - vSrc;
	FVector3 vDir = m_vDst - vSrc;

	// ������� ������ ������ �Ÿ��� ���������� ���� ���
	if (D3DXVec3Length(&vLength) <= m_fRadius)
	{
		spBlackBoardComponent->SetValueAsFVector3(L"Start", spActor->GetActorWorldPosition());

		return EBTNodeResult::SUCCEEDED;
	}

	// ���͸� �̵��մϴ�.
	float fDeltaSeconds = CTimerManager::GetInstance()->GetDeltaSeconds(L"TimerInner");
	vDir.y -= vDir.y;
	D3DXVec3Normalize(&vDir, &vDir);
	spBlackBoardComponent->SetValueAsFVector3(L"MonsterDirection", vDir); // ���� ������ ������� �߰� - �ڵ��� -

	spActor->SetActorPosition(spActor->GetActorPosition() + vDir * 10.0f * fDeltaSeconds);

	return EBTNodeResult::IN_PROGRESS;
}
