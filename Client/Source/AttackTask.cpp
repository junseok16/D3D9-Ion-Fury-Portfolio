#include "pch.h"
#include "AttackTask.h"

#include "TimerManager.h"

#include "Level.h"
#include "Actor.h"
#include "Creature.h"
#include "Monster.h"

#include "BlackBoardComponent.h"
#include "BehaviorTreeComponent.h"
using namespace std;

void CAttackTask::Initialize()
{
	CBTTaskNode::Initialize();
}

void CAttackTask::Release()
{
	CBTTaskNode::Release();
}

EBTNodeResult CAttackTask::UpdateTask()
{
	// 블랙보드 컴포넌트를 불러옵니다.
	shared_ptr<CBlackBoardComponent> spBlackBoardComponent = m_wpBehaviorTreeComponent.lock()->GetBlackBoardComponent();

	// 플레이어 위치를 가져옵니다.
	FVector3 vDst = spBlackBoardComponent->GetValueAsFVector3(L"Player");
	vDst.y -= vDst.y;

	// 비헤이비어 트리를 소유한 주인 액터를 불러옵니다.
	shared_ptr<CActor> spActor = m_wpBehaviorTreeComponent.lock()->GetOwnerActor().lock();

	// 몬스터와 플레이어 사이의 방향을 구합니다.
	FVector3 vSrc = spActor->GetActorWorldPosition();
	vSrc.y -= vSrc.y;

	FVector3 vDir = vDst - vSrc;
	vDir.y -= vDir.y;
	D3DXVec3Normalize(&vDir, &vDir);

	// 몬스터가 바라보는 방향을 갱신합니다.
	spBlackBoardComponent->SetValueAsFVector3(L"MonsterDirection", vDir);

	// 예외처리
	if (spActor->GetActorLayer().find(L"Monster") != spActor->GetActorLayer().end())
	{
		// 몬스터의 공격 내부 쿨타임을 가져옵니다.
		std::shared_ptr<CMonster> spMonster = dynamic_pointer_cast<CMonster>(spActor);
		float fMonsterAttackTime = spMonster->GetAttackTerm();

		// 시간정지 상태가 아니고, 공격 내부 쿨타임이 지났을 경우 플레이어를 공격합니다.
		float fAttackTerm = spBlackBoardComponent->GetValueAsFloat(L"AttackTerm");

		if (fMonsterAttackTime > fAttackTerm && !spMonster->GetIsTimeSlipped())
		{
			// 내부 쿨타임을 다시 0으로 돌려놓습니다.
			spMonster->SetAttackTerm(0.0f);

			// 공격합니다.
			std::shared_ptr<CCreature> spCreature = dynamic_pointer_cast<CCreature>(m_wpBehaviorTreeComponent.lock()->GetOwnerActor().lock()->GetLevel().lock()->FindActor(L"Player"));
			float fDamage = spBlackBoardComponent->GetValueAsFloat(L"Damage");
			spCreature->GetDamaged(fDamage);
		}
	}
	else
	{
		// 블랙보드 컴포넌트의 주체가 몬스터가 아니라면 공격하지않고 함수를 빠져나옵니다.
	}

	return EBTNodeResult::SUCCEEDED;
}
