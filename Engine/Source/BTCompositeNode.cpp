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
	// ���ڷ����Ͱ� �ִ� ���
	for (const auto& spBTDecorator : m_vecBTDecorators)
	{
		if (!spBTDecorator->EvaluateOnBlackboard())
		{
			return EBTNodeResult::FAILED;
		}
	}

	// ���ܸ� ó���մϴ�.
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
	// ���ڷ����Ͱ� �ִ� ���
	for (const auto& spBTDecorator : m_vecBTDecorators)
	{
		if (!spBTDecorator->EvaluateOnBlackboard())
		{
			return EBTNodeResult::FAILED;
		}
	}

	// ���ܸ� ó���մϴ�.
	if (m_iIndex >= m_vecBTNodes.size())
	{
		m_iIndex = 0;
		// return EBTNodeResult::FAILED;
	}

	// �������� �׻� �����մϴ�.
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
	// ���ڷ����Ͱ� �ִ� ���
	for (const auto& spBTDecorator : m_vecBTDecorators)
	{
		if (!spBTDecorator->EvaluateOnBlackboard())
		{
			return EBTNodeResult::FAILED;
		}
	}

	// ���ܸ� ó���մϴ�.
	if (m_iIndex >= m_vecBTNodes.size())
	{
		m_iIndex = 0;
	}

	// �� �½�ũ�� �����մϴ�.
	switch (m_spBTTaskNode->Update())
	{
	// �� �½�ũ�� ���� ���� ���
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

	// �� �½�ũ�� �����ϰų� ������ ���
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
	// ��� ��带 �����մϴ�.
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