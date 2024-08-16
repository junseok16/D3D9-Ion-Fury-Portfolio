#include "pch.h"
#include "WaitFlyingTask.h"

#include "TimerManager.h"
#include "BlackBoardComponent.h"
#include "BehaviorTreeComponent.h"
#include "Actor.h"
#include "Monster.h"
using namespace std;

void CWaitFlyingTask::Initialize()
{
	CBTTaskNode::Initialize();
}

void CWaitFlyingTask::Release()
{
	CBTTaskNode::Release();
}

EBTNodeResult CWaitFlyingTask::UpdateTask()
{
	// 블랙보드 컴포넌트를 불러옵니다.
	shared_ptr<CBlackBoardComponent> spBlackBoardComponent = m_wpBehaviorTreeComponent.lock()->GetBlackBoardComponent();

	// 목적지를 불러옵니다.
	FVector3 m_vDst = spBlackBoardComponent->GetValueAsFVector3(m_wstrKey);
	m_vDst.y -= m_vDst.y;

	// 비헤이비어 트리를 소유한 주인 액터를 불러옵니다.
	shared_ptr<CActor> spActor = m_wpBehaviorTreeComponent.lock()->GetOwnerActor().lock();

	m_fSumWaitTime += CTimerManager::GetInstance()->GetDeltaSeconds(L"TimerInner");
	// 출발지와 도착지 사이의 거리가 반지름보다 작은 경우
	if (m_fSumWaitTime >= m_fWaitTime)
	{
		spBlackBoardComponent->SetValueAsFVector3(L"Start", spActor->GetActorWorldPosition());

		m_vFlyingDir = { 1.0f, 1.0f, 1.0f };
		m_fUpFliped = false;
		m_fRightFliped = false;
		m_fFlyingTime = 0.0f;
		m_fSumWaitTime = 0.0f;

		return EBTNodeResult::SUCCEEDED;
	}

	// 출발지와 도착지 사이의 방향을 구합니다.
	FVector3 vSrc = spActor->GetActorWorldPosition();
	vSrc.y -= vSrc.y;

	FVector3 vDir = m_vDst - vSrc;
	D3DXVec3Normalize(&vDir, &vDir);

	// vUp
	FVector3 vUp = { 0.0f, 1.0f, 0.0f };

	// vDir과 vUp을 외적한 몬스터의 vRight
	FVector3 vRight;
	D3DXVec3Cross(&vRight, &vDir, &vUp);

	float fDeltaSeconds = CTimerManager::GetInstance()->GetDeltaSeconds(L"TimerInner");
	
	D3DXVec3Normalize(&vDir, &vDir);
	D3DXVec3Normalize(&vUp, &vUp);
	D3DXVec3Normalize(&vRight, &vRight);

	spBlackBoardComponent->SetValueAsFVector3(L"MonsterDirection", vDir); // 몬스터 방향을 얻기위해 추가 - 박동연 -

	// spActor->SetActorPosition(spActor->GetActorPosition() + vDir * 10.0f * fDeltaSeconds);
	spActor->SetActorPosition(spActor->GetActorPosition() + vRight * m_vFlyingDir.x * fDeltaSeconds);
	spActor->SetActorPosition(spActor->GetActorPosition() + vUp * m_vFlyingDir.y * fDeltaSeconds);

	m_fFlyingTime += fDeltaSeconds;

	if (1.0f < m_fFlyingTime && !m_fUpFliped)
	{
		m_vFlyingDir.y *= -1.0f;
		m_fUpFliped = !m_fUpFliped;
	}
	if (2.0f < m_fFlyingTime)
	{
		// m_vFlyingDir.y *= -1.0f;
		m_vFlyingDir.x *= -1.0f;

		m_fUpFliped = !m_fUpFliped;
		// m_fRightFliped = !m_fRightFliped;

		m_fFlyingTime = 0.0f;
	}

	return EBTNodeResult::IN_PROGRESS;
}
