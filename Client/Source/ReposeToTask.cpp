#include "pch.h"
#include "ReposeToTask.h"

#include "BlackBoardComponent.h"
#include "BehaviorTreeComponent.h"
#include "Actor.h"
using namespace std;

void CReposeToTask::Initialize()
{
	CBTTaskNode::Initialize();
}

void CReposeToTask::Release()
{
	CBTTaskNode::Release();
}

EBTNodeResult CReposeToTask::UpdateTask()
{
	// ������ ������Ʈ�� �ҷ��ɴϴ�.
	shared_ptr<CBlackBoardComponent> spBlackBoardComponent = m_wpBehaviorTreeComponent.lock()->GetBlackBoardComponent();

	// �����̺�� Ʈ���� ������ ���� ���͸� �ҷ��ɴϴ�.
	shared_ptr<CActor> spActor = m_wpBehaviorTreeComponent.lock()->GetOwnerActor().lock();

	random_device randDev;
	mt19937 gen(randDev());
	uniform_real_distribution<float> disWidth(-1.0f, 1.0f);
	uniform_real_distribution<float> disHeight(-1.0f, 1.0f);
	float fRandomWidth = disWidth(gen);
	float fRandomHeight = disHeight(gen);

	FVector3 vDst = m_vCenter + FVector3(m_fWidth * 0.5f * fRandomWidth, 0.0f, m_fHeight * 0.5f * fRandomHeight);
	
	spBlackBoardComponent->SetValueAsFVector3(m_wstrDstKey, vDst);
	return EBTNodeResult::SUCCEEDED;
}
