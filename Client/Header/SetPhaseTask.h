#pragma once
#include "BTTaskNode.h"

class CSetPhaseTask : public CBTTaskNode
{
public:
	explicit CSetPhaseTask() = default;
	virtual ~CSetPhaseTask() = default;

private:
	virtual void Initialize() override;
	virtual void Release() override;

private:
	virtual EBTNodeResult UpdateTask() override;

public:
	void SetPhase(int32 _iPhase);

	void SetPhaseKey(const std::wstring& _wstrPhaseKey) { m_wstrPhaseKey = _wstrPhaseKey; }

private:
	int32 m_iPhase = 0;

	std::wstring m_wstrPhaseKey = L"";
};

