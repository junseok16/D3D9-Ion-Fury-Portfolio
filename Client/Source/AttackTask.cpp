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
	// ������ ������Ʈ�� �ҷ��ɴϴ�.
	shared_ptr<CBlackBoardComponent> spBlackBoardComponent = m_wpBehaviorTreeComponent.lock()->GetBlackBoardComponent();

	// �÷��̾� ��ġ�� �����ɴϴ�.
	FVector3 vDst = spBlackBoardComponent->GetValueAsFVector3(L"Player");
	vDst.y -= vDst.y;

	// �����̺�� Ʈ���� ������ ���� ���͸� �ҷ��ɴϴ�.
	shared_ptr<CActor> spActor = m_wpBehaviorTreeComponent.lock()->GetOwnerActor().lock();

	// ���Ϳ� �÷��̾� ������ ������ ���մϴ�.
	FVector3 vSrc = spActor->GetActorWorldPosition();
	vSrc.y -= vSrc.y;

	FVector3 vDir = vDst - vSrc;
	vDir.y -= vDir.y;
	D3DXVec3Normalize(&vDir, &vDir);

	// ���Ͱ� �ٶ󺸴� ������ �����մϴ�.
	spBlackBoardComponent->SetValueAsFVector3(L"MonsterDirection", vDir);

	// ����ó��
	if (spActor->GetActorLayer().find(L"Monster") != spActor->GetActorLayer().end())
	{
		// ������ ���� ���� ��Ÿ���� �����ɴϴ�.
		std::shared_ptr<CMonster> spMonster = dynamic_pointer_cast<CMonster>(spActor);
		float fMonsterAttackTime = spMonster->GetAttackTerm();

		// �ð����� ���°� �ƴϰ�, ���� ���� ��Ÿ���� ������ ��� �÷��̾ �����մϴ�.
		float fAttackTerm = spBlackBoardComponent->GetValueAsFloat(L"AttackTerm");

		if (fMonsterAttackTime > fAttackTerm && !spMonster->GetIsTimeSlipped())
		{
			// ���� ��Ÿ���� �ٽ� 0���� ���������ϴ�.
			spMonster->SetAttackTerm(0.0f);

			// �����մϴ�.
			std::shared_ptr<CCreature> spCreature = dynamic_pointer_cast<CCreature>(m_wpBehaviorTreeComponent.lock()->GetOwnerActor().lock()->GetLevel().lock()->FindActor(L"Player"));
			float fDamage = spBlackBoardComponent->GetValueAsFloat(L"Damage");
			spCreature->GetDamaged(fDamage);
		}
	}
	else
	{
		// ������ ������Ʈ�� ��ü�� ���Ͱ� �ƴ϶�� ���������ʰ� �Լ��� �������ɴϴ�.
	}

	return EBTNodeResult::SUCCEEDED;
}
