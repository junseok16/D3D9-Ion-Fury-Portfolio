#pragma once
#include "ActorComponent.h"

class CBTNode;
class CBlackBoardComponent;

class CBehaviorTreeComponent : public CActorComponent
{
public:
	explicit CBehaviorTreeComponent() = default;
	virtual ~CBehaviorTreeComponent() = default;

/*****************
	Framework
*****************/
public:
	virtual void Initialize() override;
	virtual void BeginPlay() override;
	virtual int32 Update(const float& _fDeltaSeconds) override;
	virtual int32 LateUpdate(const float& _fDeltaSeconds) override;
	virtual void EndPlay() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	/*
	* @brief 블랙보드 컴포넌트를 저장합니다. 비헤이비어 트리 컴포넌트는 블랙보드 컴포넌트를 참조하고 있어야 합니다.
	*/
	void SetBlackBoardComponent(std::shared_ptr<CBlackBoardComponent> _spBlackBoardComponent) { m_wpBlackBoardComponent = _spBlackBoardComponent; }
	std::shared_ptr<CBlackBoardComponent> GetBlackBoardComponent() const { CHECK(!m_wpBlackBoardComponent.expired()); return m_wpBlackBoardComponent.lock(); }

	void StartBehaviorTree();

	void StopBehaviorTree();

public:
	template<typename T>
	std::shared_ptr<T> CreateBTNode(EBTNodeType _eBTNodeType)
	{
		std::shared_ptr<T> spBTNode = std::make_shared<T>();
		spBTNode->SetOwnerBehaviorTreeComponent(std::dynamic_pointer_cast<CBehaviorTreeComponent>(shared_from_this()));
		spBTNode->SetBTNodeType(_eBTNodeType);
		return spBTNode;
	}

	void AddBTNodeToRoot(std::shared_ptr<CBTNode> _spBTNode) { m_vecBTNodes.push_back(_spBTNode); }

private:
	std::vector<std::shared_ptr<CBTNode>> m_vecBTNodes;

	std::weak_ptr<CBlackBoardComponent> m_wpBlackBoardComponent;

	bool m_bBehaveBehaviorTree = false;
};

