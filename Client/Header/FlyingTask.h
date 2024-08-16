#pragma once
#include "BTTaskNode.h"
class CFlyingTask :
    public CBTTaskNode
{
public:
	explicit CFlyingTask() = default;
	virtual ~CFlyingTask() = default;

public:
	void SetRadius(float _fRadius) { m_fRadius = _fRadius; }

	void MoveTo(std::wstring _wstrKey) { m_wstrKey = _wstrKey; }

private:
	virtual void Initialize() override;
	virtual void Release() override;

private:
	virtual EBTNodeResult UpdateTask() override;

private:
	std::wstring m_wstrKey = L"";

	float m_fRadius = 1.0f;
};
