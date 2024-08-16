#include "pch.h"
#include "BTCompositeNode.h"
#include "BTTaskNode.h"
#include "BTDecorator.h"
using namespace std;

/***************
	Selector
***************/
void CSelector::Initialize()
{
}

EBTNodeResult CSelector::Update()
{
	// 데코레이터가 있는 경우
	for (const auto& spBTDecorator : m_vecBTDecorators)
	{
		if (!spBTDecorator->EvaluateOnBlackboard())
		{
			return EBTNodeResult::FAILED;
		}
	}

	// 예외를 처리합니다.
	if (m_iIndex >= m_vecBTNodes.size())
	{
		m_iIndex = 0;
		// return EBTNodeResult::FAILED;
	}

	switch (m_vecBTNodes[m_iIndex]->Update())
	{
	case EBTNodeResult::IN_PROGRESS:
		return EBTNodeResult::IN_PROGRESS;

	case EBTNodeResult::SUCCEEDED:
		m_iIndex = 0;
		return EBTNodeResult::SUCCEEDED;

	case EBTNodeResult::FAILED:
		++m_iIndex;
		return EBTNodeResult::FAILED;
	}
	return EBTNodeResult::FAILED;
}

void CSelector::Release()
{
}

/***************
	Sequence
***************/
void CSequence::Initialize()
{
}

EBTNodeResult CSequence::Update()
{
	// 데코레이터가 있는 경우
	for (const auto& spBTDecorator : m_vecBTDecorators)
	{
		if (!spBTDecorator->EvaluateOnBlackboard())
		{
			return EBTNodeResult::FAILED;
		}
	}

	// 예외를 처리합니다.
	if (m_iIndex >= m_vecBTNodes.size())
	{
		m_iIndex = 0;
		// return EBTNodeResult::FAILED;
	}

	// 시퀀스는 항상 성공합니다.
	switch (m_vecBTNodes[m_iIndex]->Update())
	{
	case EBTNodeResult::IN_PROGRESS:
		return EBTNodeResult::IN_PROGRESS;

	case EBTNodeResult::SUCCEEDED:
		++m_iIndex;
		return EBTNodeResult::SUCCEEDED;

	case EBTNodeResult::FAILED:
		m_iIndex = 0;
		return EBTNodeResult::FAILED;
	}
	return EBTNodeResult::FAILED;
}

void CSequence::Release()
{
}

/***************
	Parallel
***************/
void CParallel::Initialize()
{
}

EBTNodeResult CParallel::Update()
{
	// 데코레이터가 있는 경우
	for (const auto& spBTDecorator : m_vecBTDecorators)
	{
		if (!spBTDecorator->EvaluateOnBlackboard())
		{
			return EBTNodeResult::FAILED;
		}
	}

	// 예외를 처리합니다.
	if (m_iIndex >= m_vecBTNodes.size())
	{
		m_iIndex = 0;
	}

	// 주 태스크를 실행합니다.
	switch (m_spBTTaskNode->Update())
	{
	// 주 태스크가 진행 중인 경우
	case EBTNodeResult::IN_PROGRESS:
	{
		switch (m_vecBTNodes[m_iIndex]->Update())
		{
		case EBTNodeResult::IN_PROGRESS:
			return EBTNodeResult::IN_PROGRESS;

		case EBTNodeResult::SUCCEEDED:
			++m_iIndex;
			return EBTNodeResult::IN_PROGRESS;

		case EBTNodeResult::FAILED:
			++m_iIndex;
			return EBTNodeResult::IN_PROGRESS;
		}
	}
	break;

	// 주 태스크가 성공하거나 실패한 경우
	case EBTNodeResult::SUCCEEDED:
	{
		m_iIndex = 0;
		return EBTNodeResult::SUCCEEDED;
	}
	case EBTNodeResult::FAILED:
	{
		m_iIndex = 0;
		return EBTNodeResult::FAILED;
	}
	}
	return EBTNodeResult::FAILED;
}

void CParallel::Release()
{
}

/***************
	Composite
***************/
void CBTCompositeNode::Initialize()
{
	CBTNode::Initialize();
}

EBTNodeResult CBTCompositeNode::Update()
{
	return CBTNode::Update();
}

void CBTCompositeNode::Release()
{
	// 모든 노드를 해제합니다.
	for (auto& spNode : m_vecBTNodes)
	{
		if (spNode)
		{
			spNode.reset();
			spNode = nullptr;
		}
	}

	CBTNode::Release();
}