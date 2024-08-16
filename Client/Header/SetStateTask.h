#pragma once
#include "BTTaskNode.h"

class CSetStateTask : public CBTTaskNode
{
public:
	explicit CSetStateTask() = default;
	virtual ~CSetStateTask() = default;

private:
	virtual void Initialize() override;
	virtual void Release() override;

private:
	virtual EBTNodeResult UpdateTask() override;

public:
	void SetState(int32 _iState);

	void SetStateKey(const std::wstring& _wstrStateKey) { m_wstrStateKey = _wstrStateKey; }

private:
	std::wstring m_wstrStateKey = L"";

	int32 m_iState = 0;
};

