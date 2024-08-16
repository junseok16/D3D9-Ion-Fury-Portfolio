#pragma once
#include "BTTaskNode.h"
class CWaitFlyingTask :
    public CBTTaskNode
{
public:
	explicit CWaitFlyingTask() = default;
	virtual ~CWaitFlyingTask() = default;

public:
	void SetWaitTime(float _fWaitTime) { m_fWaitTime = _fWaitTime; }
	float GetWaitTime() const { return m_fWaitTime; }

	void SetRadius(float _fRadius) { m_fRadius = _fRadius; }

	void FlyingTo(std::wstring _wstrKey) { m_wstrKey = _wstrKey; }

private:
	virtual void Initialize() override;
	virtual void Release() override;

private:
	virtual EBTNodeResult UpdateTask() override;

private:
	std::wstring m_wstrKey = L"";

	float m_fRadius = 1.0f;

	float m_fFlyingTime = 0.0f;

	// (임시) 나는 방향을 결정하기 위함임 [ Right, Up, Look ]
	FVector3 m_vFlyingDir = { 1.0f, 1.0f, 1.0f };
	float m_fRightFliped = false;
	float m_fUpFliped = false;

	float m_fSumWaitTime = 0.0f;
	float m_fWaitTime = 0.0f;
};

