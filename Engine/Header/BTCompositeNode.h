#pragma once
#include "BTNode.h"

class CBTTaskNode;
class CBehaviorTreeComponent;

/*****************
	Composite
*****************/
class CBTCompositeNode : public CBTNode
{
public:
	explicit CBTCompositeNode() = default;
	virtual ~CBTCompositeNode() = default;

public:
	virtual void Initialize() override;
	virtual EBTNodeResult Update() override;
	virtual void Release() override;

public:
	const std::vector<std::shared_ptr<CBTNode>>& GetBTNodes() const { return m_vecBTNodes; }

public:
	void AddBTNodeToComposite(std::shared_ptr<CBTNode> _spBTNode) { m_vecBTNodes.push_back(_spBTNode); }

protected:
	std::vector<std::shared_ptr<CBTNode>> m_vecBTNodes;

	uint32 m_iIndex = 0;
};

/*****************
	Selector
*****************/
class CSelector : public CBTCompositeNode
{
public:
	explicit CSelector() = default;
	virtual ~CSelector() = default;

public:
	virtual void Initialize() override;
	virtual EBTNodeResult Update() override;
	virtual void Release() override;
};

/*****************
	Sequence
*****************/
class CSequence : public CBTCompositeNode
{
public:
	explicit CSequence() = default;
	virtual ~CSequence() = default;

public:
	virtual void Initialize() override;
	virtual EBTNodeResult Update() override;
	virtual void Release() override;
};

/*****************
	Parallel
*****************/
class CParallel : public CBTCompositeNode
{
public:
	explicit CParallel() = default;
	virtual ~CParallel() = default;

public:
	virtual void Initialize() override;
	virtual EBTNodeResult Update() override;
	virtual void Release() override;

public:
	void SetBTTaskNode(std::shared_ptr<CBTTaskNode> _spBTTaskNode) { m_spBTTaskNode = _spBTTaskNode; }
	const std::shared_ptr<CBTTaskNode>& GetBTTaskNode() { return m_spBTTaskNode; }

private:
	std::shared_ptr<CBTTaskNode> m_spBTTaskNode = nullptr;
};