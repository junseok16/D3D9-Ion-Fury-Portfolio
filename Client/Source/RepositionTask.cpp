#include "pch.h"
#include "RepositionTask.h"

#include "BlackBoardComponent.h"
#include "BehaviorTreeComponent.h"
#include "Actor.h"
#include "Monster.h"
using namespace std;

void CRepositionTask::Initialize()
{
	CBTTaskNode::Initialize();
}

void CRepositionTask::Release()
{
	CBTTaskNode::Release();
}

EBTNodeResult CRepositionTask::UpdateTask()
{
	// ������ ������Ʈ�� �ҷ��ɴϴ�.
	shared_ptr<CBlackBoardComponent> spBlackBoardComponent = m_wpBehaviorTreeComponent.lock()->GetBlackBoardComponent();
	
	// �����̺�� Ʈ���� ������ ���� ���͸� �ҷ��ɴϴ�.
	shared_ptr<CActor> spActor = m_wpBehaviorTreeComponent.lock()->GetOwnerActor().lock();

	// ����ϸ鼭 ������� �������� ������Ʈ�մϴ�. - ���� -
	FVector3 vRandomFinish;
	FVector3 vSpawnPos = spBlackBoardComponent->GetValueAsFVector3(L"Spawn");

	// ������� ���մϴ�.
	FVector3 vSrc = spActor->GetActorWorldPosition();

	// ������ �������� �������� �����մϴ�.
	vRandomFinish.x = vSpawnPos.x + (10.0f * GetRandomFloat(-1.0f, 1.0f));
	vRandomFinish.y = 0.0f;
	vRandomFinish.z = vSpawnPos.z + (10.0f * GetRandomFloat(-1.0f, 1.0f));

	spBlackBoardComponent->SetValueAsFVector3(L"Finish", vRandomFinish);

	// ������ �̵��� ������ ���¸� IDLE�� ������Ʈ�մϴ�.
	if (spActor->GetActorLayer().find(L"Monster") != spActor->GetActorLayer().end())
		dynamic_pointer_cast<CMonster>(spActor)->SetMonsterState((int32)EMonsterState::WALK);

	if (m_bReposition)
	{
		m_bReposition = !m_bReposition;
	}
	else
	{
		m_bReposition = !m_bReposition;
	}

	return EBTNodeResult::SUCCEEDED;
}

float CRepositionTask::GetRandomFloat(float _fLowBound, float _fHighBound)
{
	if (_fLowBound >= _fHighBound)
		return _fLowBound;

	// [ 0, 1 ] ������ ���� float�� ��´�.
	float fResult = (rand() % 10000) * 0.0001f;

	// [ fLowBound, fHighBound ] ������ float�� �����Ѵ�.
	return (fResult * (_fHighBound - _fLowBound)) + _fLowBound;
}

void CRepositionTask::GetRandomVector(FVector3* _vOut, FVector3* _vMin, FVector3* _vMax)
{
	_vOut->x = GetRandomFloat(_vMin->x, _vMax->x);
	_vOut->y = GetRandomFloat(_vMin->y, _vMax->y);
	_vOut->z = GetRandomFloat(_vMin->z, _vMax->z);
}