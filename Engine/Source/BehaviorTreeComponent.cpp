#include "pch.h"
#include "BehaviorTreeComponent.h"
#include "BTCompositeNode.h"
using namespace std;

void CBehaviorTreeComponent::Initialize()
{
	CActorComponent::Initialize();
}

void CBehaviorTreeComponent::BeginPlay()
{
	CActorComponent::BeginPlay();
}

int32 CBehaviorTreeComponent::Update(const float& _fDeltaSeconds)
{
	// 블랙 보드가 설정되어 있어야 합니다.
	CHECK(!m_wpBlackBoardComponent.expired());

	if (!m_bBehaveBehaviorTree) { return 0; }

	for (const auto& spBTNode : m_vecBTNodes)
	{
		EBTNodeResult eBTNodeResult = spBTNode->Update();
	}
	return CActorComponent::Update(_fDeltaSeconds);
}

int32 CBehaviorTreeComponent::LateUpdate(const float& _fDeltaSeconds)
{
	return CActorComponent::LateUpdate(_fDeltaSeconds);
}

void CBehaviorTreeComponent::EndPlay()
{
	CActorComponent::EndPlay();
}

void CBehaviorTreeComponent::Render()
{
	CActorComponent::Render();
}

void CBehaviorTreeComponent::Release()
{
	// 모든 컴포지트를 해제합니다.
	for (auto& spBTNode : m_vecBTNodes)
	{
		if (spBTNode)
		{
			spBTNode->Release();
			spBTNode.reset();
		}
	}
	CActorComponent::Release();
}

void CBehaviorTreeComponent::StartBehaviorTree()
{
	m_bBehaveBehaviorTree = true;
}

void CBehaviorTreeComponent::StopBehaviorTree()
{
	m_bBehaveBehaviorTree = false;
}
