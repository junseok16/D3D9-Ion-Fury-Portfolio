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
	// ������ ������Ʈ�� �ҷ��ɴϴ�.
	shared_ptr<CBlackBoardComponent> spBlackBoardComponent = m_wpBehaviorTreeComponent.lock()->GetBlackBoardComponent();
	FVector3 vDst = spBlackBoardComponent->GetValueAsFVector3(L"Player");
	vDst.y -= vDst.y;

	// �����̺�� Ʈ���� ������ ���� ���͸� �ҷ��ɴϴ�.
	shared_ptr<CActor> spActor = m_wpBehaviorTreeComponent.lock()->GetOwnerActor().lock();

	// ������� ������ ������ �Ÿ��� ������ ���մϴ�.
	FVector3 vSrc = spActor->GetActorWorldPosition();
	vSrc.y -= vSrc.y;

	FVector3 vDir = vDst - vSrc;

	spBlackBoardComponent->SetValueAsFVector3(m_wstrPosKey, vDst);

	vDir.y -= vDir.y;
	D3DXVec3Normalize(&vDir, &vDir);
	spBlackBoardComponent->SetValueAsFVector3(m_wstrDirKey, vDir);

	// ��ǥ�� ���� ���� ���
	m_fSumTargetingTime += CTimerManager::GetInstance()->GetDeltaSeconds(L"TimerInner");
	if (m_fSumTargetingTime < m_fTargetingTime)
	{
		return EBTNodeResult::IN_PROGRESS;
	}

	// ������ ���� ���
	m_fSumTargetingTime = 0.0f;
	return EBTNodeResult::SUCCEEDED;
}

void CSetTargetTask::Release()
{
	CBTTaskNode::Release();
}
