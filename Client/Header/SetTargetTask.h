#pragma once
#include "BTTaskNode.h"

class CSetTargetTask : public CBTTaskNode
{
public:
	explicit CSetTargetTask() = default;
	virtual ~CSetTargetTask() = default;

public:
	void SetPosKey(std::wstring _wstrPosKey) { m_wstrPosKey = _wstrPosKey; }

	void SetDirKey(std::wstring _wstrDirKey) { m_wstrDirKey = _wstrDirKey; }

	void SetTargetingTime(float _fTargetingTime) { m_fTargetingTime = _fTargetingTime; }

private:
	virtual void Initialize() override;
	virtual EBTNodeResult UpdateTask() override;
	virtual void Release() override;

private:
	std::wstring m_wstrPosKey = L"";

	std::wstring m_wstrDirKey = L"";

	float m_fSumTargetingTime = 0.0f;

	float m_fTargetingTime = 3.0f;
};

