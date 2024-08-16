#pragma once
#include "BTTaskNode.h"

class CWaitTask : public CBTTaskNode
{
public:
	explicit CWaitTask() = default;
	virtual ~CWaitTask() = default;

public:
	void SetWaitTime(float _fWaitTime) { m_fWaitTime = _fWaitTime; }
	float GetWaitTime() const { return m_fWaitTime; }

private:
	virtual void Initialize() override;
	virtual void Release() override;

private:
	virtual EBTNodeResult UpdateTask() override;

private:
	float m_fSumWaitTime = 0.0f;
	float m_fWaitTime = 0.0f;
};

