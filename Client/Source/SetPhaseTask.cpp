#include "pch.h"
#include "SetPhaseTask.h"

#include "BlackBoardComponent.h"
#include "BehaviorTreeComponent.h"
#include "WarmechLeg.h"
using namespace std;

void CSetPhaseTask::Initialize()
{
	CBTTaskNode::Initialize();
}

void CSetPhaseTask::Release()
{
	CBTTaskNode::Release();
}

EBTNodeResult CSetPhaseTask::UpdateTask()
{
	// 블랙보드 컴포넌트를 불러옵니다.
	shared_ptr<CBlackBoardComponent> spBlackBoardComponent = m_wpBehaviorTreeComponent.lock()->GetBlackBoardComponent();
	spBlackBoardComponent->SetValueAsInt(m_wstrPhaseKey, m_iPhase);

	shared_ptr<CMonster> spMonster = dynamic_pointer_cast<CMonster>(m_wpBehaviorTreeComponent.lock()->GetOwnerActor().lock());
	spMonster->SetMonsterPhase(m_iPhase);
	return EBTNodeResult::SUCCEEDED;
}

void CSetPhaseTask::SetPhase(int32 _iPhase)
{
	m_iPhase = _iPhase;
}
