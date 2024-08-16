#include "pch.h"
#include "SetStateTask.h"

#include "BlackBoardComponent.h"
#include "BehaviorTreeComponent.h"
#include "Monster.h"
using namespace std;

void CSetStateTask::Initialize()
{
	CBTTaskNode::Initialize();
}

void CSetStateTask::Release()
{
	CBTTaskNode::Release();
}

EBTNodeResult CSetStateTask::UpdateTask()
{
	// 블랙보드 컴포넌트를 불러옵니다.
	shared_ptr<CBlackBoardComponent> spBlackBoardComponent = m_wpBehaviorTreeComponent.lock()->GetBlackBoardComponent();
	spBlackBoardComponent->SetValueAsInt(m_wstrStateKey, m_iState);

	shared_ptr<CMonster> spMonster = dynamic_pointer_cast<CMonster>(m_wpBehaviorTreeComponent.lock()->GetOwnerActor().lock());
	spMonster->SetMonsterState(m_iState);
	return EBTNodeResult::SUCCEEDED;
}

void CSetStateTask::SetState(int32 _iState)
{
	m_iState = _iState;
}
