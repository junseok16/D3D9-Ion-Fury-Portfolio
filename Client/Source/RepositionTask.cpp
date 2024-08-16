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
	// 블랙보드 컴포넌트를 불러옵니다.
	shared_ptr<CBlackBoardComponent> spBlackBoardComponent = m_wpBehaviorTreeComponent.lock()->GetBlackBoardComponent();
	
	// 비헤이비어 트리를 소유한 주인 액터를 불러옵니다.
	shared_ptr<CActor> spActor = m_wpBehaviorTreeComponent.lock()->GetOwnerActor().lock();

	// 대기하면서 출발지와 도착지를 업데이트합니다. - 동연 -
	FVector3 vRandomFinish;
	FVector3 vSpawnPos = spBlackBoardComponent->GetValueAsFVector3(L"Spawn");

	// 출발지를 구합니다.
	FVector3 vSrc = spActor->GetActorWorldPosition();

	// 랜덤한 지점으로 도착지를 설정합니다.
	vRandomFinish.x = vSpawnPos.x + (10.0f * GetRandomFloat(-1.0f, 1.0f));
	vRandomFinish.y = 0.0f;
	vRandomFinish.z = vSpawnPos.z + (10.0f * GetRandomFloat(-1.0f, 1.0f));

	spBlackBoardComponent->SetValueAsFVector3(L"Finish", vRandomFinish);

	// 몬스터의 이동이 끝나면 상태를 IDLE로 업데이트합니다.
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

	// [ 0, 1 ] 범위의 임의 float을 얻는다.
	float fResult = (rand() % 10000) * 0.0001f;

	// [ fLowBound, fHighBound ] 범위의 float을 리턴한다.
	return (fResult * (_fHighBound - _fLowBound)) + _fLowBound;
}

void CRepositionTask::GetRandomVector(FVector3* _vOut, FVector3* _vMin, FVector3* _vMax)
{
	_vOut->x = GetRandomFloat(_vMin->x, _vMax->x);
	_vOut->y = GetRandomFloat(_vMin->y, _vMax->y);
	_vOut->z = GetRandomFloat(_vMin->z, _vMax->z);
}