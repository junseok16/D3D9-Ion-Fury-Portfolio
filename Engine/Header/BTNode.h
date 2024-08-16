#pragma once
#include "Object.h"

class CBehaviorTreeComponent;
class CBTDecorator;

class CBTNode : public CObject
{
public:
	explicit CBTNode() = default;
	virtual ~CBTNode() = default;

/*****************
	Framework
*****************/
public:
	virtual void Initialize();
	virtual EBTNodeResult Update();
	virtual void Release();

/*****************
	Methods
*****************/
	template<typename T>
	std::shared_ptr<T> CreateBTDecorator()
	{
		std::shared_ptr<T> spBTDecorator = std::make_shared<T>();
		spBTDecorator->SetOwnerBTNode(std::dynamic_pointer_cast<CBTNode>(shared_from_this()));
		AddBTDecorator(spBTDecorator);
		return spBTDecorator;
	}

/*****************
	Getter/Setter
*****************/
public:
	void SetOwnerBehaviorTreeComponent(std::shared_ptr<CBehaviorTreeComponent> _spBehaviorTreeComponent) { m_wpBehaviorTreeComponent = _spBehaviorTreeComponent; }
	std::weak_ptr<CBehaviorTreeComponent> GetBehaviorTreeComponent() const { CHECK(!m_wpBehaviorTreeComponent.expired()); return m_wpBehaviorTreeComponent; }

	void SetBTNodeType(EBTNodeType _eBTNodeType) { m_eBTNodeType = _eBTNodeType; }
	EBTNodeType GetBTNodeType() const { return m_eBTNodeType; }

	void AddBTDecorator(std::shared_ptr<CBTDecorator> _spBTDecorator) { m_vecBTDecorators.push_back(_spBTDecorator); }

/*****************
	Data Members
*****************/
protected:
	// 이 노드를 소유한 비헤이비어 트리
	std::weak_ptr<CBehaviorTreeComponent> m_wpBehaviorTreeComponent;

	// 비헤이비어 트리 노드 타입
	EBTNodeType m_eBTNodeType = EBTNodeType::ENUM_END;

	// 컴포지트나 태스크에 붙일 수 있는 데코레이터
	std::vector<std::shared_ptr<CBTDecorator>> m_vecBTDecorators;
};

