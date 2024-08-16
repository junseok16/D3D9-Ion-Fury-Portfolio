#pragma once
#include "BTDecorator.h"

class CActor;
class CBlackBoardComponent;

enum class EDecoratorQuery
{
	IS_SET,
	IS_NOT_SET,
	IS_EQUAL_TO,
	IS_NOT_EQUAL_TO,
	IS_GREATER_THAN,
	IS_LESS_THAN,
	ENUM_END
};

enum class EDecoratorValue
{
	BOOL,
	INT,
	FLOAT,
	WSTRING,
	FVECTOR3,
	ACTOR,
	ENUM_END
};

class CBTBlackBoardDecorator : public CBTDecorator
{
public:
	explicit CBTBlackBoardDecorator() = default;
	virtual ~CBTBlackBoardDecorator() = default;

public:
	const bool EvaluateOnBlackboard() override;

public:
	void SetOwnerBTNode(std::shared_ptr<CBTNode> _spBTNode) { m_wpOwnerBTNode = _spBTNode; }

	void SetDecoratorByBool(const std::wstring _wstrBlackBoardKey, EDecoratorQuery _eDecoratorQuery, bool _bValue = false);

	void SetDecoratorByInt(const std::wstring _wstrBlackBoardKey, EDecoratorQuery _eDecoratorQuery, int32 _iValue = 0);

	void SetDecoratorByFloat(const std::wstring _wstrBlackBoardKey, EDecoratorQuery _eDecoratorQuery, float _fValue = 0.0f);

	void SetDecoratorByWstring(const std::wstring _wstrBlackBoardKey, EDecoratorQuery _eDecoratorQuery, const std::wstring& _wstrValue = L"");

	void SetDecoratorByFVector3(const std::wstring _wstrBlackBoardKey, EDecoratorQuery _eDecoratorQuery, FVector3 _vValue = { 0.0f, 0.0f, 0.0f });

	void SetDecoratorByActor(const std::wstring _wstrBlackBoardKey, EDecoratorQuery _eDecoratorQuery, std::shared_ptr<CActor> _spActor);

private:
	void SetDecoratorValue(EDecoratorValue _eDecoratorValue) { m_eDecoratorValue = _eDecoratorValue; }

private:
	// 블랙보드에 등록된 키
	std::wstring m_wstrBlackBoardKey = L"";

	// 블랙보드에 등록된 키와 바인드된 값
	bool m_bValue = false;
	int32 m_iValue = 0;
	float m_fValue = 0.0f;
	std::wstring m_wstrValue = L"";
	FVector3 m_vValue = { 0.0f, 0.0f, 0.0f };
	std::weak_ptr<CActor> m_wpActor;

private:
	std::weak_ptr<CBTNode> m_wpOwnerBTNode;

	EDecoratorValue m_eDecoratorValue = EDecoratorValue::ENUM_END;

	EDecoratorQuery m_eDecoratorQuery = EDecoratorQuery::ENUM_END;
};

