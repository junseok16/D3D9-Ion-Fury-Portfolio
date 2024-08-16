#pragma once
#include "BTTaskNode.h"

class CMoveToTask : public CBTTaskNode
{
public:
	explicit CMoveToTask() = default;
	virtual ~CMoveToTask() = default;

public:
	void SetRadius(float _fRadius) { m_fRadius = _fRadius; }

	void SetDstKey(std::wstring _wstrDstKey) { m_wstrDstKey = _wstrDstKey; }

	void SetSrcKey(std::wstring _wstrSrcKey) { m_wstrSrcKey = _wstrSrcKey; }

	void SetDirKey(std::wstring _wstrDirKey) { m_wstrDirKey = _wstrDirKey; }

	void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }

private:
	virtual void Initialize() override;
	virtual EBTNodeResult UpdateTask() override;
	virtual void Release() override;

private:
	std::wstring m_wstrDstKey = L"";

	std::wstring m_wstrSrcKey = L"";

	std::wstring m_wstrDirKey = L"";

	float m_fRadius = 1.0f;

	float m_fSpeed = 10.0f;
};

