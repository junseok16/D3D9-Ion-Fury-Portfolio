// Default
#include "pch.h"
#include "BossSpawnMonsterTask.h"

// Framework
#include "Level.h"

// Monster
#include "Mechsect.h"
#include "Deacon.h"

// Component
#include "BlackBoardComponent.h"
#include "BehaviorTreeComponent.h"
using namespace std;

int32 CBossSpawnMonsterTask::s_iMonsterCounter = 0;

void CBossSpawnMonsterTask::Initialize()
{
	CBTTaskNode::Initialize();
}

EBTNodeResult CBossSpawnMonsterTask::UpdateTask()
{
	// ������ ������Ʈ�� �ҷ��ɴϴ�.
	shared_ptr<CBlackBoardComponent> spBlackBoardComponent = m_wpBehaviorTreeComponent.lock()->GetBlackBoardComponent();
	
	// �����̺�� Ʈ���� ������ ���� ���͸� �ҷ��ɴϴ�.
	shared_ptr<CActor> spActor = m_wpBehaviorTreeComponent.lock()->GetOwnerActor().lock();

	// ������ ��ǥ�� ���մϴ�.
	random_device randDev;
	mt19937 gen(randDev());

	switch (m_eSpawnMonsterType)
	{
	// ��ġ��Ʈ�� �����մϴ�.
	case ESpawnMonsterType::MECHSECT:
	{
		for (uint32 iNumMonster = 0; iNumMonster < m_iNumMonster; ++iNumMonster)
		{
			uniform_real_distribution<float> disWidth(-1.0f, 1.0f);
			uniform_real_distribution<float> disHeight(-1.0f, 1.0f);
			FVector3 vPosition = FVector3(150.0f * 0.5f * disWidth(gen), 10.0f, 150.0f * 0.5f * disHeight(gen));

			shared_ptr<CMechsect> spMechsect = spActor->GetLevel().lock()->CreateActor<CMechsect>(L"Mechsect" + to_wstring(s_iMonsterCounter++), L"Monster", L"Actor");
			spMechsect->SetActorPosition(vPosition);
			spMechsect->SetActorScale({ 10.0f, 10.0f, 10.0f });
			spMechsect->Initialize();
			spMechsect->BeginPlay();
		}

		return EBTNodeResult::SUCCEEDED;
	}
	break;

	// ������ �����մϴ�.
	case ESpawnMonsterType::DEACON:
	{
		for (uint32 iNumMonster = 0; iNumMonster < m_iNumMonster; ++iNumMonster)
		{
			uniform_real_distribution<float> disWidth(-1.0f, 1.0f);
			uniform_real_distribution<float> disHeight(-1.0f, 1.0f);
			FVector3 vPosition = FVector3(150.0f * 0.5f * disWidth(gen), 10.0f, 150.0f * 0.5f * disHeight(gen));

			shared_ptr<CDeacon> spDeacon = spActor->GetLevel().lock()->CreateActor<CDeacon>(L"Deacon" + to_wstring(s_iMonsterCounter++), L"Monster", L"Actor");
			spDeacon->SetActorPosition(vPosition);
			spDeacon->SetActorScale({ 8.0f, 8.0f, 8.0f });
			spDeacon->Initialize();
			spDeacon->BeginPlay();
		}
		
		return EBTNodeResult::SUCCEEDED;
	}
	break;

	default: break;
	}
}

void CBossSpawnMonsterTask::Release()
{
	CBTTaskNode::Release();
}
