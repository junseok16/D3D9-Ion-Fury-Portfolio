#pragma once
#include "BTTaskNode.h"

class CRushToTask : public CBTTaskNode
{
public:
	explicit CRushToTask() = default;
	virtual ~CRushToTask() = default;

public:
	void SetRadius(float _fRadius) { m_fRadius = _fRadius; }

	void SetPosKey(std::wstring _wstrPosKey) { m_wstrPosKey = _wstrPosKey; }

	void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }

	void SetDirKey(std::wstring _wstrDirKey) { m_wstrDirKey = _wstrDirKey; }

private:
	virtual void Initialize() override;
	virtual EBTNodeResult UpdateTask() override;
	virtual void Release() override;

private:
	std::wstring m_wstrPosKey = L"";

	std::wstring m_wstrDirKey = L"";

	float m_fSpeed = 10.0f;

	float m_fRadius = 1.0f;
};

