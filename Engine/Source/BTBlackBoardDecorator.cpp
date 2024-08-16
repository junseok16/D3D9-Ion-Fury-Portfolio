#include "pch.h"
#include "BTBlackBoardDecorator.h"
#include "BlackBoardComponent.h"
#include "BehaviorTreeComponent.h"
using namespace std;

const bool CBTBlackBoardDecorator::EvaluateOnBlackboard()
{
	CHECK(m_eDecoratorValue != EDecoratorValue::ENUM_END);
	CHECK(m_eDecoratorQuery != EDecoratorQuery::ENUM_END);
	CHECK(!m_wpOwnerBTNode.expired());

	// 블랙보드 컴포넌트를 불러옵니다.
	shared_ptr<CBlackBoardComponent> spBlackBoardComponent = m_wpOwnerBTNode.lock()->GetBehaviorTreeComponent().lock()->GetBlackBoardComponent();

 	switch (m_eDecoratorValue)
	{
	case EDecoratorValue::BOOL:
	{
		switch (m_eDecoratorQuery)
		{
		case EDecoratorQuery::IS_EQUAL_TO:
		{
			if (spBlackBoardComponent->GetValueAsBool(m_wstrBlackBoardKey) == m_bValue) { return true; }
			return false;
		}

		case EDecoratorQuery::IS_NOT_EQUAL_TO:
		{
			if (spBlackBoardComponent->GetValueAsBool(m_wstrBlackBoardKey) != m_bValue) { return true; }
			return false;
		}

		default: return false;
		}
	}
	break;

	case EDecoratorValue::INT:
	{
		switch (m_eDecoratorQuery)
		{
		case EDecoratorQuery::IS_EQUAL_TO:
		{
			if (spBlackBoardComponent->GetValueAsInt(m_wstrBlackBoardKey) == m_iValue)
			{
				return true;
			}
			return false;
		}

		case EDecoratorQuery::IS_NOT_EQUAL_TO:
		{
			if (spBlackBoardComponent->GetValueAsInt(m_wstrBlackBoardKey) != m_iValue) { return true; }
			return false;
		}

		case EDecoratorQuery::IS_GREATER_THAN:
		{
			if (spBlackBoardComponent->GetValueAsInt(m_wstrBlackBoardKey) > m_iValue) { return true; }
			return false;
		}

		case EDecoratorQuery::IS_LESS_THAN:
		{
			if (spBlackBoardComponent->GetValueAsInt(m_wstrBlackBoardKey) < m_iValue) { return true; }
			return false;
		}

		default: return false;
		}
	}
	break;

	case EDecoratorValue::FLOAT:
	{
		switch (m_eDecoratorQuery)
		{
		case EDecoratorQuery::IS_EQUAL_TO:
		{
			if (spBlackBoardComponent->GetValueAsFloat(m_wstrBlackBoardKey) == m_fValue) { return true; }
			return false;
		}

		case EDecoratorQuery::IS_NOT_EQUAL_TO:
		{
			if (spBlackBoardComponent->GetValueAsFloat(m_wstrBlackBoardKey) != m_fValue) { return true; }
			return false;
		}

		case EDecoratorQuery::IS_GREATER_THAN:
		{
			if (spBlackBoardComponent->GetValueAsFloat(m_wstrBlackBoardKey) > m_fValue) { return true; }
			return false;
		}

		case EDecoratorQuery::IS_LESS_THAN:
		{
			if (spBlackBoardComponent->GetValueAsFloat(m_wstrBlackBoardKey) < m_fValue) { return true; }
			return false;
		}

		default: return false;
		}
	}
	break;

	case EDecoratorValue::WSTRING:
	{
		switch (m_eDecoratorQuery)
		{
		case EDecoratorQuery::IS_SET:
		{
			if (spBlackBoardComponent->GetValueAsWstring(m_wstrBlackBoardKey) != L"") { return true; }
			return false;
		}
			
		case EDecoratorQuery::IS_NOT_SET:
		{
			if (spBlackBoardComponent->GetValueAsWstring(m_wstrBlackBoardKey) == L"") { return true; }
			return false;
		}

		case EDecoratorQuery::IS_EQUAL_TO:
		{
			if (spBlackBoardComponent->GetValueAsWstring(m_wstrBlackBoardKey) == m_wstrValue) { return true; }
			return false;
		}

		case EDecoratorQuery::IS_NOT_EQUAL_TO:
		{
			if (spBlackBoardComponent->GetValueAsWstring(m_wstrBlackBoardKey) != m_wstrValue) { return true; }
			return false;
		}

		default: return false;
		}
	}
	break;

	case EDecoratorValue::FVECTOR3:
	{
		switch (m_eDecoratorQuery)
		{
		case EDecoratorQuery::IS_SET:
		{
			if (spBlackBoardComponent->GetValueAsFVector3(m_wstrBlackBoardKey) != FVector3(0.0f, 0.0f, 0.0f)) { return true; }
			return false;
		}
		
		case EDecoratorQuery::IS_NOT_SET:
		{
			if (spBlackBoardComponent->GetValueAsFVector3(m_wstrBlackBoardKey) == FVector3(0.0f, 0.0f, 0.0f)) { return true; }
			return false;
		}
		
		case EDecoratorQuery::IS_EQUAL_TO:
		{
			if (spBlackBoardComponent->GetValueAsFVector3(m_wstrBlackBoardKey) == m_vValue) { return true; }
			return false;
		}
		
		case EDecoratorQuery::IS_NOT_EQUAL_TO:
		{
			if (spBlackBoardComponent->GetValueAsFVector3(m_wstrBlackBoardKey) != m_vValue) { return true; }
			return false;
		}

		default: return false;
		}
	}
	break;

	/*
	case EDecoratorValue::ACTOR:
	{
		switch (m_eDecoratorQuery)
		{
		case EDecoratorQuery::IS_SET:
			break;

		case EDecoratorQuery::IS_NOT_SET:
			break;

		default: return false;
		}
	}
	break;
	*/
	}
	return false;
}

void CBTBlackBoardDecorator::SetDecoratorByBool(const std::wstring _wstrBlackBoardKey, EDecoratorQuery _eDecoratorQuery, bool _bValue)
{
	m_wstrBlackBoardKey = _wstrBlackBoardKey;
	m_eDecoratorQuery = _eDecoratorQuery;
	m_bValue = _bValue;
	m_eDecoratorValue = EDecoratorValue::BOOL;
}

void CBTBlackBoardDecorator::SetDecoratorByInt(const std::wstring _wstrBlackBoardKey, EDecoratorQuery _eDecoratorQuery, int32 _iValue)
{
	m_wstrBlackBoardKey = _wstrBlackBoardKey;
	m_eDecoratorQuery = _eDecoratorQuery;
	m_iValue = _iValue;
	m_eDecoratorValue = EDecoratorValue::INT;
}

void CBTBlackBoardDecorator::SetDecoratorByFloat(const std::wstring _wstrBlackBoardKey, EDecoratorQuery _eDecoratorQuery, float _fValue)
{
	m_wstrBlackBoardKey = _wstrBlackBoardKey;
	m_eDecoratorQuery = _eDecoratorQuery;
	m_fValue = _fValue;
	m_eDecoratorValue = EDecoratorValue::FLOAT;
}

void CBTBlackBoardDecorator::SetDecoratorByWstring(const std::wstring _wstrBlackBoardKey, EDecoratorQuery _eDecoratorQuery, const std::wstring& _wstrValue)
{
	m_wstrBlackBoardKey = _wstrBlackBoardKey;
	m_eDecoratorQuery = _eDecoratorQuery;
	m_wstrValue = _wstrValue;
	m_eDecoratorValue = EDecoratorValue::WSTRING;
}

void CBTBlackBoardDecorator::SetDecoratorByFVector3(const std::wstring _wstrBlackBoardKey, EDecoratorQuery _eDecoratorQuery, FVector3 _vValue)
{
	m_wstrBlackBoardKey = _wstrBlackBoardKey;
	m_eDecoratorQuery = _eDecoratorQuery;
	m_vValue = _vValue;
	m_eDecoratorValue = EDecoratorValue::FVECTOR3;
}

void CBTBlackBoardDecorator::SetDecoratorByActor(const std::wstring _wstrBlackBoardKey, EDecoratorQuery _eDecoratorQuery, std::shared_ptr<CActor> _spActor)
{
	m_wstrBlackBoardKey = _wstrBlackBoardKey;
	m_eDecoratorQuery = _eDecoratorQuery;
	m_wpActor = _spActor;
	m_eDecoratorValue = EDecoratorValue::ACTOR;
}
